#include "EO_Main.h"

CAutowall g_Autowall;

int  ( __cdecl* R_GetCurWeapon )( cg_t* cg ) = ( int( __cdecl* )( cg_t* ) )0x44C220;

void CAutowall::SetupBulletTrace( bulletTrace_t* btr, Vector start, Vector end, int skipNum )
{
	btr->worldEntNum = 1022;
	btr->skipNum = skipNum;
	btr->power = 1.0f;
	btr->bulletType = EO_Utils.GetWeapon(cg->WeaponID).iWeaponBulletType;
	VectorCopy( refdef->vieworg, btr->vieworg );
	VectorCopy( start, btr->start );
	VectorCopy( end, btr->end );

	vec3_t delta;
	VectorSubtract( end, start, delta );

	vec3_t angles;
	EO_Utils.vectoangles (delta, angles);
	EO_Utils.AngleVectors( angles, btr->viewDirection, NULL, NULL );
}
bool R_BulletPenetrationCheck( bulletTrace_t *MapTrace )
{
    DWORD dwCallAddr = 0x5C8990;
    static bool returnC;
    __asm   mov     eax, MapTrace
    __asm    call    dwCallAddr
    __asm   mov    returnC, al

    return returnC;
}
void R_BulletPenetration( int unk1, bulletTrace_t* bulletTrace, int WeaponNum, int unk2, centity_t * cent, int unk3, Vector vieworg, int unk4 )
{
    DWORD dwCallAddr = 0x5CB080;
    __asm    
    {
        push unk4
        push vieworg
        push unk3
        push cent
        push unk2
        push WeaponNum
        push bulletTrace
        push unk1
        call dwCallAddr
        add     esp, 0x20
    }
	
}

void CAutowall::SetBulletImpacts(weapon_t* pWeapon, bool bState)
{
	if(!bState) 
	{
		if(!pWeapon->iWeaponBulletType)
			pWeapon->iWeaponBulletType = 100;
	} else 
	{
		if(pWeapon->iWeaponBulletType == 100)
			pWeapon->iWeaponBulletType = 0;
	}
}
bool CAutowall::GetRemainingPower( Vector vieworg, centity_t* cent, Vector origin, float* remainingPower )
{
    int Weapon                = R_GetCurWeapon( cg );
	bulletTrace_t bulletTrace;
	

	//SetupBulletTrace( pBulletTrace, vieworg, origin, cg->ClientNum );
	weapon_t pWeapon = EO_Utils.GetWeapon(R_GetCurWeapon(cg));

	bulletTrace.worldEntNum = 2046;
	bulletTrace.skipNum = cg->ClientNum;
	bulletTrace.power = 1.0f;
	bulletTrace.bulletType = pWeapon.iWeaponBulletType; //Laut IDA nicht notwendig (anders als in vorherigen CoD's) DAS IST IMMERNOCH NICH RICHTIG! ENTWEDER GIBTS IN mw3 weaponType net mehr oder wird net mehr verwendet oder bin zu blöd es zu finden
	//bulletTrace.bulletType = TestCounter; //RIOT (keine impacts)
	VectorCopy( refdef->vieworg, bulletTrace.vieworg ); 
	VectorCopy( vieworg, bulletTrace.start );
	VectorCopy( origin, bulletTrace.end );

	vec3_t delta;
	VectorSubtract( origin, vieworg, delta );

	vec3_t angles;
	EO_Utils.vectoangles (delta, angles);
	EO_Utils.AngleVectors( angles, bulletTrace.viewDirection, NULL, NULL );

	//SetBulletImpacts(&pWeapon, false);

	DWORD dwOld = *(DWORD*)0x9DF6E0;
	*(DWORD*)0x9DF6E0 = 0xFFFFFFFF;

	R_BulletPenetrationCheck( &bulletTrace );
	R_BulletPenetration(0, &bulletTrace, Weapon, 0, &cg_entities[cg->ClientNum], 0xFFFFFFFF, vieworg, false); //exception: erstes arg auf 0xFFFFFFF setzen (crasht allerdings nich da wos soll

	*(DWORD*)0x9DF6E0 = dwOld;

	//SetBulletImpacts(&pWeapon, true);																			//hab deshalb das andre awall weiterbearbeitet es scheint schon fast ganz zu gehen xD

	if(bulletTrace.skipNum == cent->clientNum)
	{
		*remainingPower = bulletTrace.power;
		return (bulletTrace.power > 0);
	}
	*remainingPower = -1;
	return false;

	/*if(pBulletTrace->skipNum == cent->clientNum)
		*remainingPower = pBulletTrace->power;
	else 
		*remainingPower = 0.0f;*/
}