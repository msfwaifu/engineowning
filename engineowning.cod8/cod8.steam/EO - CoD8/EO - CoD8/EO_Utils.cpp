#include "EO_Main.h"

EO_CUtils EO_Utils;

vec3_t nullvec = { 0, 0, 0 };
vec3_t null_vec = { 0,0,0 };

void ( __cdecl *CG_Trace)( trace_t *result, const vec3_t start, const vec3_t end, const vec3_t mins, int clientNum, int mask ) = ( void ( __cdecl* )( trace_t*, const vec3_t, const vec3_t, const vec3_t, int, int ))0x57C950;

int EO_CUtils::SetupVectorTrace(float *flLocation)
{
	trace_t t;
	CG_Trace(&t, refdef->vieworg, flLocation, null_vec, cg->ClientNum, 0x803003);
	return (t.fraction >= 0.97f);
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
//comment
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



 GetScreenMatrix GSM = (GetScreenMatrix)0x522880;
typedef bool (*__cdecl World2Screen)(int,ScreenMatrix*,vec3_t,float*);
World2Screen WorldToScreenE = (World2Screen)0x571C20;



bool EO_CUtils::WorldToScreen( vec3_t vWorldLocation, float Screen[2])
{
	return WorldToScreenE(0,GSM(),vWorldLocation,Screen);
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

	vAngles[1]-=refdef->weaponAngles[1];
	vAngles[0]-=refdef->weaponAngles[0];

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
void EO_CUtils::GetAngleToOrigin(Vector vOrigin, float &flOutX, float &flOutY)
{
	Vector vEntity, vAngle;
	VectorSubtract(vOrigin, refdef->vieworg, vEntity);
    vectoangles(vEntity, vAngle);

    if (vAngle[1] > 180.0f)           
        vAngle[1] -= 360.0f;
    else if (vAngle[1] < -180.0f)   
        vAngle[1] += 360.0f;

    if (vAngle[0] > 180.0f)        
        vAngle[0] -= 360.0f;
    else if (vAngle[0] < -180.0f)    
        vAngle[0] += 360.0f;

	//float* RefAngles = (float*)0xA4C0DC;
	float* RefAngles = (float*)0xA534EC; //Weaponviewangles anstatt Refdef vAngles verwenden (is einfach akkurater xD)
	
	vAngle[1] -= RefAngles[1];
	vAngle[0] -= RefAngles[0];

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
void EO_CUtils::GetAngleToOrigin(Vector vOrigin,Vector ViewAngle , float &flOutX, float &flOutY)
{
	Vector vEntity, vAngle;
	VectorSubtract(vOrigin, refdef->vieworg, vEntity);
	EO_Utils.vectoangles(vEntity, vAngle);

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

bool EO_CUtils::GetPlayerTag(short tag, centity_t* entity, float* vec)
{
	void* mesh = ((void* (__cdecl*)(int))0x40C050)(entity->clientNum);

	if (!mesh) 
	{
		return false;
	}

	return ((bool (__cdecl*)(centity_t*, void*, short, float*))0x445D00)(entity, mesh, tag, vec);
}


bool EO_CUtils::NormalTrace( vec3_t point, centity_t* pEntity)
{
	trace_t t;

	CG_Trace(&t, refdef->vieworg, point, null_vec, cg->ClientNum, 0x803003);


	return (t.fraction > 0.97f);
}

LPVOID EO_CUtils::GetDvarValueAddress(DWORD PtrAddress)
{

	return (PtrAddress > 0) ? (LPVOID)((*(DWORD*)PtrAddress) + 0xC) : 0;

}

