typedef struct {
	char *szName; //0x0000 
	char _0x0004[4];
	char *szLocalizedName; //0x0008 
	char _0x000C[60];
	float flZoomedFOV; //0x0048 
	char _0x004C[8];
	__int32 iMaxClipRounds; //0x0054 
	__int32 iBulletImpactEffectType; //0x0058 
	__int32 iWeaponFireDelay; //0x005C 
	__int32 iWeaponBulletType; //0x0060 
	char _0x0064[4];
	vec3_t vWeaponWeight; //0x0068 
	char _0x0074[16]; //124
	__int32 Icon; //0x0084 136
    char _0x0088[424]; 
	int BulletType;


} weapon_t; //Size=0x0600



struct ScreenMatrix
{
	char unk[64];
};
typedef ScreenMatrix* (*__cdecl GetScreenMatrix)();
extern GetScreenMatrix GSM;

#define OFF_PING *(int*)0x1140EB8


class EO_CUtils
{
public:
	int 			SetupVectorTrace		(float *flLocation);
	float			GetDistance				( vec3_t A, vec3_t B );
	float			Get2dDistance			( vec2_t A, vec2_t B );
	bool			WorldToScreen			( vec3_t vWorldLocation,float Screen[2] );
	void			AngleVectors			( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up );
	void			vectoangles				( const vec3_t value1, vec3_t angles );
	float			AngleNormalize180		( float angle );
	float			AngleNormalize360		( float angle );
	void			VectorViewAngles		(float *flLocation,float *flOut);
	bool			GetPlayerTag			(short tag, centity_t* entity, float* vec);
	bool			NormalTrace				( vec3_t point, centity_t* pEntity);
	void			GetAngleToOrigin		(Vector vOrigin, float &flOutX, float &flOutY);
	void			GetAngleToOrigin		(Vector vOrigin,Vector ViewAngle , float &flOutX, float &flOutY);
	float			GetRemainingPower		( vec3_t vieworg, centity_t* Ent, int weapon, Vector origin );
	weapon_t		GetWeapon				(int ID);
	weapon_t        *pGetWeapon             (int ID);
	LPVOID          GetDvarValueAddress     (DWORD PtDvarAddress);

	template <class T> void
	                SetDvar(DWORD PtrAddress, T tNewValue)
	{

						memcpy(this->GetDvarValueAddress(PtrAddress), (LPVOID)&tNewValue, sizeof(T));


	}

	template <class T> T
					GetDvar(DWORD PtrAddress)
	{


						return this->GetDvarValueAddress(PtrAddress) ? *(T*)this->GetDvarValueAddress(PtrAddress) : (T)0;


	}

	template <class T> T
	                GetDvarByName(PCHAR pszName)
	{

						int nAddress = 0;
						int nCallAddress = 0x669890;

						__asm
						{

							mov edi, pszName;

							mov eax, nCallAddress;

							call eax;

							mov nAddress, eax;

						}

						return nAddress ? (T)(*(DWORD*)(nAddress + 0xC)) : 0;

	}

	template <class T> void
		           SetDvarByName(PCHAR pszName, T Value)
	{

					   int nAddress = 0;
					   int nCallAddress = 0x669890;

					   __asm
					   {

						   mov edi, pszName;

						   mov eax, nCallAddress;

						   call eax;

						   mov nAddress, eax;

					   }

					   if (!nAddress) return;

					   nAddress += 0xC;

					   memcpy((LPVOID)nAddress, &Value, sizeof(T));

					   return;

	}


};
extern EO_CUtils		EO_Utils;


//comment