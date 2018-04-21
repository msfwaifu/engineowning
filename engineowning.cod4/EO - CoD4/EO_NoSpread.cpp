#include "EO_Main.h"

CNoSpread g_NoSpread;

typedef struct
{
	vec3_t recoil; //0x0000 
	vec3_t recoil2; //0x000C 
    char _0x0018[12];
	vec3_t weaponAngles; //0x0024 
    char _0x0030[68];
	vec3_t origin; //0x0074 
}matrix_t;//Size=0x0080
matrix_t*				matrix			= (matrix_t *)				0x0079E700;

weapon_t* GetWeapon(int iWeaponID)
{
	DWORD dwWeapon_t = iWeaponID * 4 + 0x736DB8;
	return (weapon_t*) *(DWORD*)dwWeapon_t;
}

void CNoSpread::WeaponSpread( float*Out )
{
	DWORD dwSpreadCall = 0x416C70;

	weapon_t*pWeapon = GetWeapon( cg_entities[cg->clientNum].weapon );
	
	if( !pWeapon )
		return;

	float flSpreadMultiplier = 0.0f;
	float flBaseSpread = 0.0f;
	float flMaxSpread = 0.0f;

	__asm
	{
		MOV ECX, pWeapon;
		MOV EDX, 0x794474;
		LEA EDI, [ flBaseSpread ];
		LEA ESI, [ flMaxSpread ];
		CALL DWORD PTR DS:[ dwSpreadCall ];
		FLD DWORD PTR DS:[ 0x84CAA0 ];
		FDIV QWORD PTR DS:[ 0x70AEE0 ];
		FSTP flSpreadMultiplier;
	}
	*Out = flBaseSpread + ( ( flMaxSpread - flBaseSpread ) * flSpreadMultiplier );
}
void CNoSpread::RandomFloats( int iSeed,float*flSpreadX,float*flSpreadY )
{
	DWORD dwRandomFloat = 0x4A66E0;

	__asm
	{
		PUSH flSpreadY;
		PUSH flSpreadX;
		PUSH iSeed;
		CALL DWORD PTR DS:[ dwRandomFloat ];
		ADD ESP, 0xC;
	}
}

void CNoSpread::FirstBulletFix( )
{
  float v1,v2,v3,v4; 
 
  v4 = *(float*)0x79D6D4;

  if ( *(float*)0x79E818 != 0.0 )
  {   
      v4 = *(float*)0x79E818 * *(float*)0x79D6D4;
  }

  *(float*)0xC84F8C = v4;
  *(int*)0xC84FD0 = *(int*)0x84CA8C;
  *(int*)0xC84F84 = *(int*)0x79E6A4;
  *(int*)0xC84F88 = *(int*)0x79E6B4;
  
  v1 = *(float*)0x79E754 + *(float*)0x79E760;
  
  *(int*)0x84CA8C = 0;
  
  v2 = *(float*)0x79E764 + *(float*)0x79E758;
  v3 = *(float*)0x79E768 + *(float*)0x79E75C;
  
  *(float*)0xC84F98 = v1;
  *(float*)0xC84F9C = v2;
  *(float*)0xC84FA0 = v3;

  *(float*)0xC5B6EC = *(float*)0x797618;
  *(float*)0xC5B6F0 = *(float*)0x79761C;
  *(float*)0xC5B6F4 = *(float*)0x797620;
}


void CNoSpread::RemoveSpread(  )
{
	int *cl_cmdNumber = ( int* )0xCC5FF8;
    usercmd_t *cl_cmds = (usercmd_t*)0xCC4FF8;
    int newCmdNum = *cl_cmdNumber & CMD_MASK;
    usercmd_t *newCmd = &cl_cmds[newCmdNum];
    (*cl_cmdNumber)++;
    int cmdNum = *cl_cmdNumber & CMD_MASK;
    usercmd_t *injectedCmd = &cl_cmds[cmdNum];
    *injectedCmd = *newCmd;

    if( EO_Aimbot.iTarget != -1 )
        injectedCmd->buttons |= IN_ATTACK;

    newCmd->servertime -= 1;

   if( newCmd->buttons & IN_ATTACK )
        newCmd->buttons &= 0xFFFFFFFEu;

	Vector vForward,vRight,vUp;
	Vector vDirection,vDest;
	Vector vSpreadAngles;
	float flSpread;
	float flSpreadX,flSpreadY=0.0f;

	this->FirstBulletFix( );
	
	this->WeaponSpread( &flSpread );

	flSpread = tan( flSpread * ( M_PI/180 ) ) * 8192.0f;

	this->RandomFloats( *( int* )0x839248,&flSpreadX,&flSpreadY );

	flSpreadX *= flSpread;
	flSpreadY *= flSpread;

	EO_Utils.AngleVectors( matrix->weaponAngles,vForward,vRight,vUp );

	vDirection = vForward * 8192.0f + vRight * flSpreadX + vUp * flSpreadY;

	vDirection.Normalize( );

	EO_Utils.vectoangles( vDirection,vDest );

	VectorSubtract( matrix->weaponAngles,vDest,vSpreadAngles );

	newCmd->viewangles[0] += ANGLE2SHORT(EO_Utils.AngleNormalize180(vSpreadAngles.x));
	newCmd->viewangles[1] += ANGLE2SHORT(EO_Utils.AngleNormalize180(vSpreadAngles.y));
	newCmd->viewangles[2] = 0;


	if(EO_Aimbot.iTarget != -1 && EO_Aimbot.Type != 0)
	{
		newCmd->viewangles[0] += ANGLE2SHORT(EO_Aimbot.Angles[0]);
		newCmd->viewangles[1] += ANGLE2SHORT(EO_Aimbot.Angles[1]);
		newCmd->viewangles[2] += ANGLE2SHORT(EO_Aimbot.Angles[2]);
	}
}