class CompassWidget extends UIScriptedMenu
{
	private Widget m_CompassRootWidget;
	private Widget m_CompassFrameWidget;
	private ImageWidget m_CompassImageWidget;
    private ImageWidget m_ObjectiveIconWidget;
	private ImageWidget m_MainBaseIconWidget;
    private vector m_ObjectiveLocation;
	private vector m_MainBaseLocation;
	private bool m_CompassIsVisible;

	void~CompassWidget()
	{ GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.CompassUpdate); }

	void CompassWidget(bool visible)
	{
		m_CompassRootWidget = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/BattlegroundsCompass.layout");
		m_CompassFrameWidget = m_CompassRootWidget.FindAnyWidget("FrameCompass");
		m_CompassImageWidget = ImageWidget.Cast(m_CompassRootWidget.FindAnyWidget("ImageCompass"));
        m_ObjectiveIconWidget = ImageWidget.Cast(m_CompassRootWidget.FindAnyWidget("ObjectiveIcon"));
		m_MainBaseIconWidget = ImageWidget.Cast(m_CompassRootWidget.FindAnyWidget("MainBaseIcon"));

		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.CompassUpdate, 16, true);
		SetCompassVisible(visible);
	}

	bool IsCompassVisible()
	{ return m_CompassIsVisible; }

	void SetCompassVisible(bool visible)
	{
		m_CompassIsVisible = visible;
		if (m_CompassRootWidget)
		{ m_CompassRootWidget.Show(m_CompassIsVisible); }
	}

	void ToggleCompass()
	{
		m_CompassIsVisible = !m_CompassIsVisible;
		if (m_CompassRootWidget)
		{ m_CompassRootWidget.Show(m_CompassIsVisible); }
	}

	void SetCoords(vector loc)
    { m_ObjectiveLocation = loc; }

	void CompassUpdate()
	{
		if (IsCompassVisible(()) && m_CompassRootWidget != null && GetGame().GetPlayer())
		{
			float angle = CompassGetAngle();
			m_CompassFrameWidget.Show(true);
			CompassSetCompassPos(angle);
			m_CompassRootWidget.Update();
			m_CompassRootWidget.Show(true);
			vector eventCoords = m_ObjectiveLocation;
			float directionToObjective = GetDirectionToLocation(eventCoords);
			SetIconPos(directionToObjective, m_ObjectiveIconWidget);
			MainBaseUpdate();
		}
		else if (m_CompassRootWidget != null)
		{
			m_CompassRootWidget.Show(false);
		}
	}

	void SetMainBase(vector mainBaseLocation)
	{
		m_MainBaseLocation = mainBaseLocation;
		MainBaseUpdate();
	}

	void MainBaseUpdate()
	{
		if (m_MainBaseLocation != vector.Zero)
		{
			float angle = CompassGetAngle();
			m_CompassFrameWidget.Show(true);
			CompassSetCompassPos(angle);
			m_CompassRootWidget.Update();
			m_CompassRootWidget.Show(true);
			float directionToMainBase = GetDirectionToLocation(m_MainBaseLocation);
			SetIconPos(directionToMainBase, m_MainBaseIconWidget);
			m_MainBaseIconWidget.Show(true);
		}
		else
		{
			m_MainBaseIconWidget.Show(false);
		}
	}

	void SetIconPos(float direction, ImageWidget iconWidget)
	{
		if (!iconWidget) return;
		float compassAngle = CompassGetAngle();
		float relativeAngle = compassAngle - direction;
		while (relativeAngle < -180) relativeAngle += 360;
		while (relativeAngle > 180) relativeAngle -= 360;
		float width, height, x, y;
		iconWidget.GetPos(x, y);
		iconWidget.GetSize(width, height);
		float center_offset = width / -2.0 + 0.5;
		float offset = relativeAngle * (center_offset / 180.0) + center_offset;
		iconWidget.SetPos(offset, y);
	}

    float GetDirectionToLocation(vector objectivePos)
    {
        vector playerPos = GetGame().GetPlayer().GetPosition();
        vector dirToObjective = objectivePos - playerPos;
        dirToObjective.Normalize();
        float angle = Math.Atan2(dirToObjective[0], dirToObjective[2]) * Math.RAD2DEG;
        return angle;
    }

	void SetCompassAlpha(float alpha)
	{
		if (m_CompassRootWidget != null)
		{
			m_CompassRootWidget.SetAlpha(alpha);
		}
	}

	string CompassGetHeading(float angle)
	{
		float rounded = Math.Round(5 *Math.Round(angle / 5.0));
		return rounded.ToString();
	}

	void CompassSetCompassPos(float angle)
	{
		float width, height, x, y;
		m_CompassImageWidget.GetPos(x, y);
		m_CompassImageWidget.GetSize(width, height);

		float center_offset = width / -2.0 + 0.5;

		if (angle > 180)
		{
			angle = angle - 360;
		}

		float offset = angle *(center_offset / 180.0) + center_offset;

		m_CompassImageWidget.SetPos(offset, y);
	}

	float CompassGetAngle()
	{
		vector direction = GetGame().GetCurrentCameraDirection();
		float angle = direction.VectorToAngles()[0];
		return angle;
	}
}