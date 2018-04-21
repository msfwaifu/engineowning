#include "EO_Main.h"


EO_Aimbot Aimbot;


void EO_Aimbot::CalculateBestTarget(int EntityNum)
{
	trace_t Trace;

	Vector BonePos;


	if(Engine.GetWeapon(Client[EntityNum]->weaponID2)->WeaponType == 0 ) //RIOT
	{
		float Distance[2];
		Vector EyePos;
		if(Engine.GetTagPos(Entity[EntityNum],"tag_eye",EyePos)) //Get head pos from enemy
		{
			GetAngleToOrigin(EyePos,Client[EntityNum]->vAngles,Distance[0],Distance[1]); 
			if(!(Distance[0] < 100.f && Distance[0] > -100.f))
				return;
		}
	}

	Engine.GetTagPos(Entity[EntityNum],"j_head",BonePos);

	if(Engine.IsVisible(BonePos))
	{
		float NewDist = Math.GetDistance(RefDef->vOrigin,BonePos);
		//float NewDist = 0; //POWER
		Engine.GetRemainingIndex(RefDef->vOrigin,Entity[EntityNum],BonePos,&NewDist);

		if(NewDist < LastDifference)
		{
			FoundEnemy = true;
			LastDifference = NewDist;
			BestTarget = EntityNum;
		}

	}
}






void EO_Aimbot::GetAngleToOrigin(Vector vOrigin, float &flOutX, float &flOutY)
{
	Vector vEntity, vAngle;
	Math.VectorSubtract(vOrigin, RefDef->vOrigin, vEntity);
    Math.VectorAngles(vEntity, vAngle);

    if (vAngle[1] > 180.0f)           
        vAngle[1] -= 360.0f;
    else if (vAngle[1] < -180.0f)   
        vAngle[1] += 360.0f;

    if (vAngle[0] > 180.0f)        
        vAngle[0] -= 360.0f;
    else if (vAngle[0] < -180.0f)    
        vAngle[0] += 360.0f;

	vAngle[1] -= RefDef->refdefViewAngles[1];
	vAngle[0] -= RefDef->refdefViewAngles[0];

    if (vAngle[0] > 180.0f)          
        vAngle[0] -= 360.0f;
    else if (vAngle[0] < -180.0f)   
        vAngle[0] += 360.0f;

    if (vAngle[1] > 180.0f)      
        vAngle[1] -= 360.0f;
    else if (vAngle[1] < -180.0f)   
        vAngle[1] += 360.0f;

    flOutX = vAngle[1];
    flOutY = vAngle[0];
}  
void EO_Aimbot::GetAngleToOrigin(Vector vOrigin,Vector vMyOrigin,Vector ViewAngle, float &flOutX, float &flOutY)
{
	Vector vEntity, vAngle;
	Math.VectorSubtract(vOrigin, vMyOrigin, vEntity);
    Math.VectorAngles(vEntity, vAngle);

    if (vAngle[1] > 180.0f)           
        vAngle[1] -= 360.0f;
    else if (vAngle[1] < -180.0f)   
        vAngle[1] += 360.0f;

    if (vAngle[0] > 180.0f)        
        vAngle[0] -= 360.0f;
    else if (vAngle[0] < -180.0f)    
        vAngle[0] += 360.0f;

	vAngle[1] -= ViewAngle[1];
	vAngle[0] -= ViewAngle[0];

    if (vAngle[0] > 180.0f)          
        vAngle[0] -= 360.0f;
    else if (vAngle[0] < -180.0f)   
        vAngle[0] += 360.0f;

    if (vAngle[1] > 180.0f)      
        vAngle[1] -= 360.0f;
    else if (vAngle[1] < -180.0f)   
        vAngle[1] += 360.0f;

    flOutX = vAngle[1];
    flOutY = vAngle[0];
}  
void EO_Aimbot::GetAngleToOrigin(Vector vOrigin,Vector ViewAngle , float &flOutX, float &flOutY)
{
	Vector vEntity, vAngle;
	Math.VectorSubtract(vOrigin, RefDef->vOrigin, vEntity);
    Math.VectorAngles(vEntity, vAngle);

    if (vAngle[1] > 180.0f)           
        vAngle[1] -= 360.0f;
    else if (vAngle[1] < -180.0f)   
        vAngle[1] += 360.0f;

    if (vAngle[0] > 180.0f)        
        vAngle[0] -= 360.0f;
    else if (vAngle[0] < -180.0f)    
        vAngle[0] += 360.0f;

	vAngle[1] -= ViewAngle[1];
	vAngle[0] -= ViewAngle[0];

    if (vAngle[0] > 180.0f)          
        vAngle[0] -= 360.0f;
    else if (vAngle[0] < -180.0f)   
        vAngle[0] += 360.0f;

    if (vAngle[1] > 180.0f)      
        vAngle[1] -= 360.0f;
    else if (vAngle[1] < -180.0f)   
        vAngle[1] += 360.0f;

    flOutX = vAngle[1];
    flOutY = vAngle[0];
}  