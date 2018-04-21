#include "EO_Main.h"

EO_CUtils EO_Utils;

vec3_t nullvec = { 0, 0, 0 };

int EO_CUtils::GetIndex( void )
{
	DWORD dwBase = 0x0074E338;

	_asm mov	eax, dwBase
	_asm mov	eax, [eax]
}

void EO_CUtils::CG_Trace ( vec3_t vStart, trace_t* trace, vec3_t vPoint, vec3_t vNull, int iNum, DWORD dwFlags )
{
	DWORD dwCall = 0x00459EF0;

	__asm 
	{ 
		xor	eax, eax
			push	eax
			push	eax
			push	dwFlags
			push	iNum
			push	vPoint
			push	vNull
			push	vStart
			mov	edi, trace
			mov	eax, vNull
			mov	esi, dwCall
			call	esi
			add	esp, 0x1C
	}
}

float EO_CUtils::GetDistance( vec3_t A, vec3_t B )
{
	float dx = A[0] - B[0];
	float dy = A[1] - B[1];
	float dz = A[2] - B[2];

	return (float)sqrt( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) );
}

float EO_CUtils::Get2dDistance( vec2_t A, vec2_t B )
{
	float dx = A[0] - B[0];
	float dy = A[1] - B[1];

	return (float)sqrt( ( dx * dx ) + ( dy * dy ) );
}

bool EO_CUtils::IsVisible( vec3_t point )
{
	trace_t t;

	CG_Trace( refdef->vieworg, &t, point, nullvec, GetIndex( ), 0x2806831 );

	return ( t.fraction >= 1.0f );
}

void EO_CUtils::AngleVectors( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up)
{
	float			angle;
	static float	sr, sp, sy, cr, cp, cy;

	angle = angles[YAW] * (M_PI*2 / 360);
	sy = sin(angle);
	cy = cos(angle);

	angle = angles[PITCH] * (M_PI*2 / 360);
	sp = sin(angle);
	cp = cos(angle);

	angle = angles[ROLL] * (M_PI*2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1*sr*sp*cy+-1*cr*-sy);
		right[1] = (-1*sr*sp*sy+-1*cr*cy);
		right[2] = -1*sr*cp;
	}
	if (up)
	{
		up[0] = (cr*sp*cy+-sr*-sy);
		up[1] = (cr*sp*sy+-sr*cy);
		up[2] = cr*cp;
	}
}

void EO_CUtils::vectoangles( const vec3_t value1, vec3_t angles )
{
	float	forward;
	float	yaw, pitch;

	if( value1[1] == 0 && value1[0] == 0 )
	{
		yaw = 0;
		if ( value1[2] > 0 )
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		if ( value1[0] )
			yaw = ( atan2 ( value1[1], value1[0] ) * ( 180.0f / M_PI ) );
		else if ( value1[1] > 0 )
			yaw = 90.0f;
		else
			yaw = 270.0f;

		if ( yaw < 0.0f )
			yaw += 360.0f;

		forward = sqrt ( ( value1[0] * value1[0] ) + ( value1[1] * value1[1] ) );
		pitch = ( atan2( value1[2], forward ) * ( 180.0f / M_PI ) );

		if ( pitch < 0.0f )
			pitch += 360;
	}

	angles[PITCH]	= -pitch;
	angles[YAW]		= yaw;
	angles[ROLL]	= 0;
}

bool EO_CUtils::WorldToScreen( vec3_t vWorldLocation, float * fScreenX, float * fScreenY )
{
	int iCenterX=refdef->Width/2;
	int iCenterY=refdef->Height/2;

	Vector vLocal, vTransForm;
	Vector vright = refdef->viewaxis[1], 
		vup	   = refdef->viewaxis[2], 
		vfwd   = refdef->viewaxis[0];

	VectorSubtract(vWorldLocation, refdef->vieworg, vLocal);

	vTransForm[0]  = DotProduct(vLocal,vright);
	vTransForm[1]  = DotProduct(vLocal,vup);
	vTransForm[2]  = DotProduct(vLocal,vfwd);

	if (vTransForm.z < 0.01) 
	{
		return 0;
	}

	if(fScreenX&&fScreenY)
	{
		*fScreenX = iCenterX * (1-(vTransForm.x / refdef->Fovx  / vTransForm.z));
		*fScreenY = iCenterY * (1-(vTransForm.y / refdef->Fovy / vTransForm.z));
	}

	return  vTransForm.z > 0;
}

float EO_CUtils::AngleNormalize360 ( float angle ) 
{
	return ((float)(360.0 / 65536) * ((int)(angle * (65536 / 360.0)) & 65535));
}

float EO_CUtils::AngleNormalize180 ( float angle ) 
{
	angle = AngleNormalize360( angle );
	if ( angle > 180.0 ) {
		angle -= 360.0;
	}
	return angle;
}

short EO_CUtils::GetTagNumber( char* TagName, int EntityType, int TagStrLen )
{
	int* getTagNumber = ( int* )0x4024B0;
	short TagNumber = NULL;
	TagStrLen += 1; 

	__asm
	{
		push 	TagStrLen
			push 	EntityType
			push	TagName
			call	[getTagNumber]
		add	esp, 0xC
			mov	TagNumber, ax
	}     

	return TagNumber;
}

unsigned short EO_CUtils::ASM_RegisterTag( char* TagName, int EntityType, int TagStrLen )
{
	__asm
	{
		push    TagStrLen
			push    EntityType
			push    TagName
			mov    eax, 0x518290
			call    eax
			add    esp, 0xC
	}
}

int EO_CUtils::GetPlayerTag( WORD TagName, entity_t * cent, float * fOrg )
{
	int iReturn = 0;

	__asm 
	{
		push	fOrg
			movzx	esi, TagName
			mov		ecx, cent
			movzx	eax, byte ptr [ecx+4]
		mov		edi, 0x4024B0
			call	edi
			add		esp, 4
			mov		iReturn, eax
	}

	return iReturn;
}

void EO_CUtils::GetTagOrigin( entity_t * cent, float * fOrg, short Tag )
{
	if ( GetPlayerTag ( Tag, cent, fOrg ) )
		return;

	fOrg	= cent->lerpOrigin; 
}

void EO_CUtils::GetAngleToOrigin( vec3_t Origin, float &AngleX, float &AngleY )
{
	vec3_t entity, angle;
	VectorSubtract( Origin, refdef->vieworg, entity);
	vectoangles( entity, angle);

	if ( angle[YAW] > 180.0f)			angle[YAW] -= 360.0f;
	else if ( angle[YAW] < -180.0f)	angle[YAW] += 360.0f;
	if ( angle[PITCH] > 180.0f)		angle[PITCH] -= 360.0f;

	else if ( angle[PITCH] < -180.0f)	angle[PITCH] += 360.0f;
	angle[YAW]		-= refdef->refdefViewAngles[YAW];
	angle[PITCH]	-= refdef->refdefViewAngles[PITCH];
	if ( angle[YAW] > 180.0f)			angle[YAW] -= 360.0f;
	else if ( angle[YAW] < -180.0f)	angle[YAW] += 360.0f;
	if ( angle[PITCH] > 180.0f)		angle[PITCH] -= 360.0f;
	else if ( angle[PITCH] < -180.0f)	angle[PITCH] += 360.0f;

	AngleX = angle[YAW];
	AngleY = angle[PITCH];
}

bool EO_CUtils::NormalTrace( vec3_t point, entity_t* pEntity)
{
	trace_t t;
	CG_Trace(refdef->vieworg, &t, point, nullvec, cg->clientNum, 0x803003);
	return (t.fraction >= 1.0f);
}

void EO_CUtils::VectorViewAngles(float *flLocation,float *flOut)
{
	vec3_t vDelta,vAngles;
	VectorSubtract(flLocation,refdef->vieworg,vDelta);
	vectoangles(vDelta,vAngles);

	if(vAngles[1]>180.0f)
		vAngles[1]-=360.0f;
	else if(vAngles[1]<-180.0f)
		vAngles[1]+=360.0f;

	if(vAngles[0]>180.0f)
		vAngles[0]-=360.0f;
	else if(vAngles[0]<-180.0f)
		vAngles[0]+=360.0f;

	vAngles[1]-=refdef->refdefViewAngles[1];
	vAngles[0]-=refdef->refdefViewAngles[0];

	if(vAngles[1]>180.0f)
		vAngles[1]-=360.0f;
	else if(vAngles[1]<-180.0f)
		vAngles[1]+=360.0f;

	if(vAngles[0]>180.0f)
		vAngles[0]-=360.0f;
	else if(vAngles[0]<-180.0f)
		vAngles[0]+=360.0f;

	VectorCopy(vAngles,flOut);
}
weapon_t* EO_CUtils::GetWeapon(int iWeaponID)
{
	DWORD dwWeapon_t = iWeaponID * 4 + 0x736DB8;
	return (weapon_t*) *(DWORD*)dwWeapon_t;
}