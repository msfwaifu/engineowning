#include "EO_Main.h"

CNoSpread gNoSpread;

void ( *R_WeaponSpread )( cg_t* cg,int weapon,float*BaseSpread,float*MaxSpread ) = ( void( __cdecl* )( cg_t*,int,float*,float* ) )0x435D90;
//comment

void CNoSpread::GetRandomSpread( float* flSpreadRight,float* flSpreadUp ) 
{ 
	DWORD dwCall = 0x5C8D00; 

	int iSeed = *( int* )0xA4758C-1;

	int iSpreadSeed = 214013 * (214013 * (214013 * (214013 * iSeed + 2531011) + 2531011) + 2531011) + 2531011;

	__asm 
	{ 
		lea eax, dword ptr ds: [ flSpreadUp ]; 
		push [ eax ];
		lea ecx, dword ptr ds: [ flSpreadRight ]; 
		push [ ecx ];
		lea esi, dword ptr ds:[ iSpreadSeed ];
		call dword ptr ds:[ dwCall ]; 
		add esp, 0x8 
	} 
} 
void CNoSpread::GetWeaponSpread( float*Spread ) 
{ 
	float SpreadMultiplier = *(float*)0xAE0CC8; 

	float MaxSpread = 0.0f; 
	float BaseSpread = 0.0f; 

	int iLocalWeapon = R_GetCurrentWeapon( cg ); 

	R_WeaponSpread( cg, iLocalWeapon, &BaseSpread, &MaxSpread ); 

	*Spread = BaseSpread + ( ( MaxSpread - BaseSpread ) * SpreadMultiplier / 255.0f ); 
}
void CNoSpread::ApplySpread(usercmd_t*cmd) 
{ 
	float spread = 0.0f; 
	float spread_x = 0.0f; 
	float spread_y = 0.0f; 
	float distance = 8192.0f; 


	vec3_t spread_view,calc_spread_view,spread_angle,forward,right,up,dest; 
	
	vec3_t weapon_angles;

	//weapon_angles[ 0 ] = *( float* )0xA44F98;
	//weapon_angles[ 1 ] = *( float* )0xA44F9C;
	weapon_angles[0] = *(float*)0xA534EC;
	weapon_angles[1] = *(float*)0xA534F0;
	weapon_angles[2] = 0;

	EO_Utils.AngleVectors( weapon_angles,forward,right,up ); 
	
	GetWeaponSpread( &spread ); 
	
	spread *= 0.01745329238474369f; 
	
	spread = tan( spread ) * 8192.0f; 
	
	GetRandomSpread( &spread_x,&spread_y ); 
	
	spread_x *= spread; 
	spread_y *= spread; 
	
	spread_view[ 0 ] = forward[ 0 ] * 8192.0f + right[ 0 ] * spread_x + up[ 0 ] * spread_y;
	spread_view[ 1 ] = forward[ 1 ] * 8192.0f + right[ 1 ] * spread_x + up[ 1 ] * spread_y;
	spread_view[ 2 ] = forward[ 2 ] * 8192.0f + right[ 2 ] * spread_x + up[ 2 ] * spread_y;

	VectorNormalize( spread_view );

	EO_Utils.vectoangles( spread_view,dest ); 

	VectorSubtract( weapon_angles,dest,spread_angle );
	
	cmd->viewangles[ 0 ] += ANGLE2SHORT( EO_Utils.AngleNormalize180( spread_angle[ 0 ] ) );
	cmd->viewangles[ 1 ] += ANGLE2SHORT( EO_Utils.AngleNormalize180( spread_angle[ 1 ] ) );
	cmd->viewangles[ 2 ] += ANGLE2SHORT( EO_Utils.AngleNormalize180( spread_angle[ 2 ] ) );

	if(Aimbot.Silent && Aimbot.BestTarget != -1)
	{
		float AimAt[2];
		EO_Utils.GetAngleToOrigin(Aimbot.vTemp,AimAt[0],AimAt[1]);

		cmd->viewangles[0] += ANGLE2SHORT(AimAt[1]);
		cmd->viewangles[1] += ANGLE2SHORT(AimAt[0]);
	}
}