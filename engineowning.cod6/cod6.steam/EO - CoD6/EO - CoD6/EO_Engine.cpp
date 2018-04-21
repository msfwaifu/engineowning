

#include "EO_Main.h"

entity_t* Entity[2048];
client_t* Client[18];
CG_T* CG;
CGS_T* CGS;
Refdef_t* RefDef;

EO_Engine Engine;



float NullVec[6]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
bool EO_Engine::IsVisible(Vector End)
{
	trace_t tr;
	float NullVec[6]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
	tr.fraction = 0;
	CG_Trace(&tr,RefDef->vOrigin,End,NullVec,CG->clientNum,0x803003);
	if(tr.fraction > 0.97f)
		return true;
	return false;
}



void getTag(short tag, entity_t* entity, float* vOut)
{
    void* mesh = ((void* (__cdecl*)(int))0x472220)(entity->clientNum);

    if (tag <= 0 || !mesh)
    {
        vOut[0] = vOut[1] = vOut[2] = 0.0f;
        return;
    }

    ((bool (__cdecl*)(entity_t*, void*, short, float*))0x4F8990)(entity, mesh, tag, vOut);
}

bool EO_Engine::GetTagPos(entity_t* Ent,char* tag,float* out)
{
	short FTag = RegisterTag(tag);

	getTag(FTag,Ent,out);
	if(out[0] == 0 && out[1] == 0 && out[2] == 0)
		return false;
	return true;
}

typedef int (*__cdecl GetWeaponSpread_465AE0)(playerstate_t* playerdata, weapon_t* locWeapInfo, float* spreadX, float* spreadY);
GetWeaponSpread_465AE0 CG_GetWeaponSpread = (GetWeaponSpread_465AE0)0x465AE0;


void EO_Engine::GetSpreadAngle(int* out_angleX,int* out_angleY,int serverTime)
{
			//FirstBulletFix();
			
			Vector vForward, vRight, vUp;
			Vector vSpreadAngles;

			Vector vWeaponAngles;
			float* WeaponAngle = (float*)0x869794;
			vWeaponAngles[0] = WeaponAngle[0];
			vWeaponAngles[1] = WeaponAngle[1];
			vWeaponAngles[2] = 0;

			
			Math.AngleVectors(vWeaponAngles, vForward, vRight, vUp);

			int iCorrectSeed = (214013 * (214013 * (214013 * (214013 * (214013 * serverTime + 2531011) + 2531011) + 2531011) + 2531011) + 2531011);

			double dbRandom1 = (double)((unsigned int)iCorrectSeed >> 17) * 0.000030517578125 * 360.0 * 0.01745329238474369;
			double dbRandom2 = (double)((unsigned int)(214013 * iCorrectSeed + 2531011) >> 17) * 0.000030517578125;

			double dbDisplacementX = cos(dbRandom1) * dbRandom2;
			double dbDisplacementY = sin(dbRandom1) * dbRandom2;

			float fWeaponSpread = 0.0f, fBaseSpread = 0.0f;
			

			weapon_t* TempWeap = GetWeapon(Client[CG->clientNum]->weaponID2);
			CG_GetWeaponSpread((playerstate_t*)0x7F58B8,TempWeap, &fWeaponSpread, &fBaseSpread);

			double dbSpreadAngle = tan((fWeaponSpread + ((fBaseSpread - fWeaponSpread) * ((*(float*)0x8F2BBC) / 255.0 ))) * 0.01745329238474369) * 8192.0;

			dbDisplacementX *= dbSpreadAngle;
			dbDisplacementY *= dbSpreadAngle;

			Vector FinalAngle;
			FinalAngle[0] = vForward[0] * 8192.0 + vRight[0] * dbDisplacementX + vUp[0] * dbDisplacementY;
			FinalAngle[1] = vForward[1] * 8192.0 + vRight[1] * dbDisplacementX + vUp[1] * dbDisplacementY;
			FinalAngle[2] = vForward[2] * 8192.0 + vRight[2] * dbDisplacementX + vUp[2] * dbDisplacementY;
			Math.VectorAngles(FinalAngle, vSpreadAngles);

			*out_angleX = ANGLE2SHORT(RefDef->refdefViewAngles[0] - vSpreadAngles[0]); 
			*out_angleY = ANGLE2SHORT(RefDef->refdefViewAngles[1] - vSpreadAngles[1]); 

}


typedef void ( __cdecl* BulletPenetrationCheck ) (int localClientNum, bulletTrace_t* btr, int weaponID, entity_t *ent, int minus_1_param, float *tracerStart, bool drawTracer);
BulletPenetrationCheck BCHECK = ( BulletPenetrationCheck)0x5A0D10;


bool BPC( bulletTrace_t * pBulletTrace )
{
	DWORD dwAddr = 0x59E950;
    static bool ret;
    __asm   mov     eax, pBulletTrace
    __asm   call    dwAddr
    __asm   mov    ret, al

    return ret;

}

bool EO_Engine::GetRemainingIndex( Vector vieworg, entity_t* cent, Vector origin, float* remainingPower )
{

	trace_t tr;
	float NullVec[6]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
	tr.fraction = 0;
	CG_Trace(&tr,RefDef->vOrigin,origin,NullVec,CG->clientNum,0x803003);
	if(tr.fraction > 0.97f)
	{
		*remainingPower = 1.f;
		return true;
	}
	
	bulletTrace_t bulletTrace;

	ZeroMemory(&bulletTrace,sizeof(bulletTrace_t));

    bulletTrace.worldEntNum = 2047;
	bulletTrace.skipNum = CG->clientNum;
    bulletTrace.power = 1.0f;
	bulletTrace.bulletType = Engine.GetWeapon(Client[CG->clientNum]->weaponID2)->WeaponType;
	
	Math.VectorCopy( RefDef->refdefViewAngles, bulletTrace.vieworg );
	Math.VectorCopy( vieworg, bulletTrace.start );
	Math.VectorCopy( origin, bulletTrace.end );

	Vector delta;
	Math.VectorSubtract( origin, vieworg, delta );

	Vector angles;
	Math.VectorAngles( delta, angles );
	Math.AngleVectors( angles, bulletTrace.viewDirection, NULL, NULL );

	if(!BPC(&bulletTrace))
	{
		*remainingPower = -1;
		return false;

	}

	BCHECK(CG->clientNum,&bulletTrace,Client[CG->clientNum]->weaponID2,Entity[CG->clientNum],-1,RefDef->vOrigin,false);
	
	if ( bulletTrace.skipNum == cent->clientNum)
	{
		*remainingPower = bulletTrace.power;
		return true;
	}
	else
	{
		*remainingPower = -1.0f;
		return false;
	}

}
