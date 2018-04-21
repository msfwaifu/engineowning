#include "EO_Main.h"

//<<<<<<< HEAD
void GetPower(entity_t* cent, int a2, bulletTrace_t* bulletTrace, weapon_t* weapon, vec3_t vieworg, int serverTimeDelta)
{
	int v50;
	float v32;

	while(1)
	{
		//if ( v50 )
			float* Addy = (float*)0x7373B8;
			v32 = Addy[29 * weapon->penetrateType];
		//else
			//v32 = 0.0f;
	}
}
//=======
CAutowall g_Autowall;

weapon_t GetWeapon4(int iWeaponID)
{
	/*DWORD dwWeapon_t = iWeaponID * 4 + 0x736DB8;
	return (weapon_t*) *(DWORD*)dwWeapon_t;*/
	return (*(weapon_t *)*(DWORD*)(0x736DB8 + 4*iWeaponID));
}

vec3_t emptyvec = { 0,0,0 };

void CAutowall::PlayerViewPoint( vec3_t* retnPoint )
{
	DWORD dwCall = 0x456580;
	__asm
	{
		mov eax, 0x794474;
		mov edx, [ retnPoint ];
		push edx;
		call [ dwCall ];
		add esp, 0x4;
	}
}
float CAutowall::BG_GetSurfacePenetrationDepth( weapon_t* weapon, int materialType )
{
	float*m_flDamageTable = reinterpret_cast< float* >( *reinterpret_cast< PDWORD_PTR >( weapon )  + 0x600 );
	int m_iDamageIndex = ( ( materialType >> 0x14 ) & 0x1F ) + ( weapon->penetrateType * 0x1D );
	BOOL m_bDeepImpact = ( LOBYTE( *( PDWORD_PTR )( ( *( PDWORD_PTR )( 0x84F2D8 + 0x158 ) * 0x4CC ) + 0x83929C ) >> 0x5 ) == 1 );

	if( m_bDeepImpact )
		return ( m_flDamageTable[m_iDamageIndex] * *( FLOAT* )( *( PDWORD )0x736B90 + 0xC ) );
	return m_flDamageTable[m_iDamageIndex];
}
int GetSourceEntityNum( bulletTrace_t* bp )
{


	trace_t trace;
	EO_Utils.CG_Trace(bp->start, &trace, bp->end, emptyvec, bp->skipNum, 0x2806831|0x803003|0x810011);

	if(trace.fraction == 1.00f)
	{
		return true;
	}

	int iSourceEntityNum = 1023;

	if ( trace.hitType == TRACE_HITTYPE_DYNENT_MODEL || trace.hitType == TRACE_HITTYPE_DYNENT_BRUSH )
	{
		iSourceEntityNum = 1022;
	} else {
		if ( trace.hitType == TRACE_HITTYPE_ENTITY )
			iSourceEntityNum = trace.hitId;
		else
			iSourceEntityNum = 1023;
	}

	return iSourceEntityNum;
}
bool CAutowall::bCanPenetrate( entity_t*pBaseEntity,vec3_t endpos,float* Power )
{
	vec3_t endpoint,forward,dir;

	weapon_t* weapon = EO_Utils.GetWeapon( cg_entities[cg->clientNum].weapon );
	entity_t *localEnt = &cg->predictedPlayerEntity;
	bulletTrace_t bulletTrace;
	bTrace = &bulletTrace;

	if(EO_Utils.IsVisible(endpos))
	{
		*Power = 1;
		return true;
	}

	vec3_t nullvec={0,0,0};

	

	m_traceEnt = pBaseEntity;
	bHitTarget = false;

	flTmpLength = 0.0f;

	PlayerViewPoint ( &point );



	bTrace->worldEntNum = 1022;
	bTrace->skipNum = cg->clientNum;
	
	//float* WeapPowerDef = (float*)0x7373B8;
	bTrace->power = 1.7;
	bool v19 = (weapon->rifleBullet == 0);
	bTrace->bulletType = !v19 + 1;

	VectorSubtract( endpos,point,dir );

	flTmpLength = VectorLength ( dir );

	dir[0] /= flTmpLength;
	dir[1] /= flTmpLength;
	dir[2] /= flTmpLength;


	bTrace->viewDirection[0] = dir[0];
	bTrace->viewDirection[1] = dir[1];
	bTrace->viewDirection[2] = dir[2];

	endpoint[0] = point[0] + bTrace->viewDirection[0] * 8192.0f;
	endpoint[1] = point[1] + bTrace->viewDirection[1] * 8192.0f;
	endpoint[2] = point[2] + bTrace->viewDirection[2] * 8192.0f;

	VectorCopy ( point, bTrace->vieworg );
	VectorCopy ( point, bTrace->start );
	VectorCopy ( endpoint, bTrace->end );

	*reinterpret_cast<PDWORD_PTR>( 0x185C434 ) = NULL;


	*reinterpret_cast<PBYTE>( *reinterpret_cast<PDWORD_PTR>( 0x11015EC ) + 0xC ) = 0;

	DWORD_PTR pTrace = 0x455A80;

	vec3_t *pVecPoint = &point;

	__asm
	{
		PUSH 0;
		MOV EAX, pVecPoint;
		PUSH EAX;
	    PUSH weapon;
	    LEA EDX, bulletTrace;
	    PUSH EDX;
	    PUSH 0;
	    MOV EDI, localEnt;
	    CALL pTrace;
	    ADD ESP, 0x14;
	}
	*Power = bulletTrace.power;

	*reinterpret_cast<PDWORD_PTR>( 0x185C434 ) = 0xCBB5644;
    *reinterpret_cast<PBYTE>( *reinterpret_cast<PDWORD_PTR>( 0x11015EC ) + 0xC ) = 1;

	

	if(bulletTrace.skipNum == pBaseEntity->clientNum)
	{
		return bulletTrace.power > 0;
	}
	return false;
}
void CAutowall::UpdateAutowall( void )
{
	if ( dwEntNum == EO_Aimbot.iTarget )
	bHitTarget=true;

	vec3_t vTmp;
	VectorSubtract ( vTraceEndPos, point, vTmp );

	if ( VectorLength ( vTmp ) >= flTmpLength )
		bHitTarget = true;
//>>>>>>> d67738d7327bd9221fca8642a3820205e9442a3f
}