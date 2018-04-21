class EO_CUtils
{
public:
	void			CG_Trace				( vec3_t Start, trace_t* Tracer, vec3_t End, vec3_t Zero, int Index, unsigned long Flags );
	float			GetDistance				( vec3_t A, vec3_t B );
	float			Get2Distance			( vec2_t A, vec2_t B );
	bool			IsVisible				( vec3_t point );
	bool			WorldToScreen			( vec3_t vWorldLocation, float * fScreenX, float * fScreenY );
	void			GetOrigin				( vec3_t origin, vec3_t angles );
	float			Get2dDistance			( vec2_t A, vec2_t B );
	//void			AngleVectors			( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up );
	void			vectoangles				( const vec3_t value1, vec3_t angles );
	float			AngleNormalize180		( float angle );
	float			AngleNormalize360		( float angle );
	int				GetPlayerTag			( WORD TagName, centity_t * cent, float * fOrg );
	void			GetTagOrigin			( centity_t * cent, float * fOrg, short Tag );
	void			GetBoneOrigin			( centity_t * Player, vec3_t Origin );
	short			GetTagNumber			( char * TagName, int EntityType, int TagStrLen );
	unsigned short  ASM_RegisterTag			( char* TagName, int EntityType, int TagStrLen );
	void			GetAngleToOrigin		( vec3_t Origin, float &AngleX, float &AngleY );
	bool			NormalTrace				( vec3_t point, centity_t* pEntity);
	bool			isValidEnt				( centity_t *pEnt);
	int				GetTeam					( centity_t*ent );
	void			VectorViewAngles		(float *flLocation,float *flOut);
	weapon_t*		GetWeapon				(int iWeaponID);
	void AngleVectors( const float* angles, float *forward, float *right, float *up );
	void VectorAngles( const float *forward, float *angles );
};
extern EO_CUtils		EO_Utils;