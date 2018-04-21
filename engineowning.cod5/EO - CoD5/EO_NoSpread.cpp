#include "EO_Main.h"

CNoSpread g_NoSpread;

void CNoSpread::WeaponSpread( float*Out )
{
	weapon_t*pWeapon = EO_Utils.GetWeapon( client[ cg2->clientNum ].iWeaponID );

	DWORD dwCall = 0x420620;

	float flSpreadMultiplier = 0.0f;
	float flBaseSpread = 0.0f;
	float flMaxSpread = 0.0f;

	flSpreadMultiplier = *( float* )0xA8D5F8;

	__asm
	{
		MOV ECX, [ pWeapon ];
		PUSH ECX;
		MOV ESI, [ 0x9E2AB4 ];
		LEA ECX, [ flMaxSpread ]; 
		LEA EDX, [ flBaseSpread ];
		CALL dwCall;
		ADD ESP,0x4;
	}

	*Out = flBaseSpread + ( ( flMaxSpread - flBaseSpread ) * flSpreadMultiplier / 255.0f );
}
void CNoSpread::RandomSpread( int iSeed,float*spread_x,float*spread_y )
{
	__asm
	{
		PUSH [ spread_y ];
		PUSH [ spread_x ];
		PUSH [ iSeed ];
		MOV EAX, 0x47E630;
		CALL EAX;
		ADD ESP, 0xC;
	}
}

void CNoSpread::RemoveSpread( )
{
	int *cl_cmdNumber = ( int* )0xFAC934;
	usercmd_t *cl_cmds = (usercmd_t*)0xFAB334; 
	int newCmdNum = *cl_cmdNumber & CMD_MASK;
	usercmd_t *newCmd = &cl_cmds[newCmdNum];
	(*cl_cmdNumber)++;
	int cmdNum = *cl_cmdNumber & CMD_MASK;
	usercmd_t *injectedCmd = &cl_cmds[cmdNum];
	*injectedCmd = *newCmd;

	if( EO_Aimbot.m_iTargetID != -1 )
		injectedCmd->buttons |= IN_ATTACK;

	newCmd->serverTime -= 1;

	if( newCmd->buttons & IN_ATTACK )
		newCmd->buttons &= 0xFFFFFFFEu;

	float fForward[ 3 ],fRight[ 3 ],fUp[ 3 ],fSpread[ 3 ],fSpreadDir[ 3 ],fDest[ 3 ],fSpreadAngles[ 3 ];
	float fSpreadCone = 0.0f;

	this->WeaponSpread( &fSpreadCone );

	fSpreadCone = tan( fSpreadCone * ( M_PI/180 ) ) * 8192.0f;
	
	this->RandomSpread( injectedCmd->serverTime,&fSpread[ 0 ],&fSpread[ 1 ] );

	fSpread[ 0 ] *= fSpreadCone;
	fSpread[ 1 ] *= fSpreadCone;

	EO_Utils.AngleVectors( matrix->weaponAngles,fForward,fRight,fUp );

	fSpreadDir[ 0 ] = fForward[ 0 ] * 8192.0f + fRight[ 0 ] * fSpread[ 0 ] + fUp[ 0 ] * fSpread[ 1 ];
	fSpreadDir[ 1 ] = fForward[ 1 ] * 8192.0f + fRight[ 1 ] * fSpread[ 0 ] + fUp[ 1 ] * fSpread[ 1 ];
	fSpreadDir[ 2 ] = fForward[ 2 ] * 8192.0f + fRight[ 2 ] * fSpread[ 0 ] + fUp[ 2 ] * fSpread[ 1 ];

	VectorNormalize( fSpreadDir );

	EO_Utils.VectorAngles( fSpreadDir,fDest );

	VectorSubtract( matrix->weaponAngles,fDest,fSpreadAngles );

	newCmd->viewangles[ 0 ] += ( signed int )( fSpreadAngles[ 0 ] * 182.0444488525391 + 0.5 ) & 0xFFFF;
	newCmd->viewangles[ 1 ] += ( signed int )( fSpreadAngles[ 1 ] * 182.0444488525391 + 0.5 ) & 0xFFFF;
	newCmd->viewangles[ 2 ] = 0;
}
