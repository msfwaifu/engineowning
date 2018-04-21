class CNoSpread
{
public:

	void GetRandomSpread( float* flSpreadRight,float* flSpreadUp );
	void GetWeaponSpread( float*Spread );
	void ApplySpread(usercmd_t*cmd);
	void FirstBulletFix();
}extern gNoSpread;

extern int iSeed;
static int ( __cdecl* R_GetCurrentWeapon )( cg_t* ) = ( int ( __cdecl* )( cg_t* ) )0x44C220;

//comment