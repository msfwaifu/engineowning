
class CAutowall
{
public:
	entity_t *m_traceEnt;
	bool bHitTarget;
	float flTmpLength;
	vec3_t point;
	bulletTrace_t *bTrace;
public:
	float BG_GetSurfacePenetrationDepth( weapon_t* weapon, int materialType );
	void PlayerViewPoint( vec3_t* retnPoint );
	bool bCanPenetrate( entity_t*pBaseEntity,vec3_t endpos,float* Power  );
	void UpdateAutowall( void );
	bool bCanPenetrate2( entity_t*entity,vec3_t endpos);
}extern g_Autowall;

