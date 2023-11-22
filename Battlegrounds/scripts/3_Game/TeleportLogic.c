modded class DayZGame
{
    const float MAP_MAX_X = 15350;
    const float MAP_MAX_Z = 15350;
    const float MAP_MIN_X = 0;
    const float MAP_MIN_Z = 0; 

    vector TeleportEntityToSafePosition(EntityAI entity, vector centerPos, float minRadius, float maxRadius, vector size, vector orientation, int attempt = 1)
    {
        array<vector> potentialPositions = RandomVectorArrayInRadius(20, minRadius, maxRadius, centerPos);
        array<vector> safePositions;

        SafeLandPosRock(potentialPositions, centerPos, size, orientation, safePositions);

        if (safePositions.Count() == 0)
        {
            entity.SetPosition(centerPos);
            return centerPos;
        }

        int randomIndex = Math.RandomInt(0, safePositions.Count());
        vector chosenPosition = safePositions[randomIndex];

        if (chosenPosition[0] < MAP_MIN_X || chosenPosition[2] > MAP_MAX_Z)
        { return TeleportEntityToSafePosition(entity, centerPos, minRadius, maxRadius, size, orientation, attempt + 1); }

        if (vector.Distance(chosenPosition, centerPos) <= 50.0)
        {
            if (attempt == 1)
            { return TeleportEntityToSafePosition(entity, centerPos, minRadius, 850, size, orientation, attempt + 1); }
            else
            { return TeleportEntityToSafePosition(entity, centerPos, minRadius, maxRadius, size, orientation, attempt + 1); }
        }

        entity.SetPosition(chosenPosition);
        return chosenPosition;
    }

    vector TeleportEntityToMainBase(EntityAI entity, vector centerPos, float minRadius, float maxRadius, vector size, vector orientation, int attempt = 1)
    {
        array<vector> potentialPositions = RandomVectorArrayInRadius(20, minRadius, maxRadius, centerPos);
        array<vector> safePositions;

        SafeLandPos(potentialPositions, centerPos, size, orientation, safePositions);

        if (safePositions.Count() == 0)
        {
            entity.SetPosition(centerPos);
            return centerPos;
        }

        int randomIndex = Math.RandomInt(0, safePositions.Count());
        vector chosenPosition = safePositions[randomIndex];

        if (vector.Distance(chosenPosition, centerPos) <= 2.0)
        {
            if (attempt == 1)
            {
                return TeleportEntityToMainBase(entity, centerPos, minRadius, 10, size, orientation, attempt + 1);
            }

            else
            {
                return TeleportEntityToMainBase(entity, centerPos, minRadius, maxRadius, size, orientation, attempt + 1);
            }
        }

        //entity.SetPosition(chosenPosition);
        return chosenPosition;
    }

    array<vector> RandomVectorArrayInRadius(int loops, float minRadius, float maxRadius, vector centerPos)
    {
        private float RandomX;
        private float RandomZ;
        private vector pos;
        autoptr array<vector> m_RandomPosRay = new array<vector>;

        for (int i = 0; i < loops; i++)
        {
            float randomRadius = Math.RandomFloatInclusive(minRadius, maxRadius);
            RandomX = centerPos[0] + randomRadius * Math.Cos(Math.RandomFloatInclusive(0.01, 6.28));
            RandomZ = centerPos[2] + randomRadius * Math.Sin(Math.RandomFloatInclusive(0.01, 6.28));
            pos = Vector(RandomX, centerPos[1], RandomZ);
            m_RandomPosRay.Insert(pos);
        }
        return m_RandomPosRay;
    }

    void SafeLandPos(array<vector> PosVectorArray, vector DefaultPos, vector size, vector orientation, out array<vector> SafeLandPosArray)
    {						
        private string w_Surface;
        
        SafeLandPosArray = new array<vector>;
        
        array<Object> excluded_objects = new array<Object>;
        array<Object> nearby_objects = new array<Object>;
        array<Object> objectsAtPosition = new array<Object>;
        
        for (int i = 0; i < PosVectorArray.Count(); ++i)
        {        
            GetGame().SurfaceGetType3D(PosVectorArray.Get(i)[0], PosVectorArray.Get(i)[1], PosVectorArray.Get(i)[2], w_Surface); 

            vector adjustedPosition = Vector(PosVectorArray.Get(i)[0], GetGame().SurfaceY(PosVectorArray.Get(i)[0], PosVectorArray.Get(i)[2]), PosVectorArray.Get(i)[2]);
            
            float objectRadius = 25.0;
            GetGame().GetObjectsAtPosition(adjustedPosition, objectRadius, objectsAtPosition, NULL);

            if (!GetGame().IsBoxColliding(adjustedPosition, orientation, size, excluded_objects, nearby_objects) && w_Surface != "FreshWater" && w_Surface != "sea" && !GetGame().SurfaceIsSea(PosVectorArray.Get(i)[0], PosVectorArray.Get(i)[2]))
            {
                SafeLandPosArray.Insert(adjustedPosition);
            }
                
            delete excluded_objects;    
            delete nearby_objects;
            objectsAtPosition.Clear(); 
            w_Surface = "";
        }
        
        if (SafeLandPosArray.Count() == 0)
        {        
            SafeLandPosArray.Insert(DefaultPos);
        } 
    }

    void SafeLandPosRock(array<vector> PosVectorArray, vector DefaultPos, vector size, vector orientation, out array<vector> SafeLandPosArray)
    {						
        private string w_Surface;
        
        SafeLandPosArray = new array<vector>;
        
        array<Object> excluded_objects = new array<Object>;
        array<Object> nearby_objects = new array<Object>;
        array<Object> objectsAtPosition = new array<Object>;
        
        for (int i = 0; i < PosVectorArray.Count(); ++i)
        {        
            GetGame().SurfaceGetType3D(PosVectorArray.Get(i)[0], PosVectorArray.Get(i)[1], PosVectorArray.Get(i)[2], w_Surface); 

            vector adjustedPosition = Vector(PosVectorArray.Get(i)[0], GetGame().SurfaceY(PosVectorArray.Get(i)[0], PosVectorArray.Get(i)[2]), PosVectorArray.Get(i)[2]);
            
            float objectRadius = 25.0;
            GetGame().GetObjectsAtPosition(adjustedPosition, objectRadius, objectsAtPosition, NULL);

            if (!GetGame().IsBoxColliding(adjustedPosition, orientation, size, excluded_objects, nearby_objects) && w_Surface != "FreshWater" && w_Surface != "sea" && !GetGame().SurfaceIsSea(PosVectorArray.Get(i)[0], PosVectorArray.Get(i)[2]) && !AnyObjectIsRock(objectsAtPosition))
            {
                SafeLandPosArray.Insert(adjustedPosition);
            }
                
            delete excluded_objects;    
            delete nearby_objects;
            objectsAtPosition.Clear(); 
            w_Surface = "";
        }
        
        if (SafeLandPosArray.Count() == 0)
        {        
            SafeLandPosArray.Insert(DefaultPos);
        } 
    }

    bool AnyObjectIsRock(array<Object> objects)
    {
        for (int i = 0; i < objects.Count(); i++)
        {
            if (objects[i].IsRock())
            {
                return true;
            }
        }
        return false;
    }
}

