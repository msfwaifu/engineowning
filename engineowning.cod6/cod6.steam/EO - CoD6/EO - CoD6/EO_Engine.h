

#define ISINGAME *(byte*)0x7DE05C


typedef struct {
    char _0x0000[64];
} ScreenMatrix;

typedef bool (__cdecl* EngineW2S_416290)(int unk1, ScreenMatrix* ScreenStruct, float* Pos, float *ScreenOut);
typedef ScreenMatrix* (__cdecl* GetScreenMatrix_4B7B40)(int a1);

typedef weapon_t* (__cdecl* GetWeapon_40FA50)(int WeaponID);

typedef int (*__cdecl RegisterTag_4782B0)(char* name);

typedef int(*__cdecl SendCmdToCon_4393E0)(int def1,int def2,char* cmd);

typedef void (*__cdecl CG_TRACE_4437D0)(trace_t* Trace, Vector Origin, Vector NullVec,Vector End, int SkipNum, int Mask);

extern entity_t* Entity[2048];
extern client_t* Client[18];
extern CG_T* CG;
extern CGS_T* CGS;
extern Refdef_t* RefDef;


class EO_Engine
{
public:
	void GetSpreadAngle(int* out_angleX,int* out_angleY,int serverTime);
	
	bool GetTagPos(entity_t* Ent,char* Tag,Vector out);
	
	GetWeapon_40FA50 GetWeapon;

	CG_TRACE_4437D0 CG_Trace;

	GetScreenMatrix_4B7B40 GetScreenMatrix;
	EngineW2S_416290 WorldToScreen;
	RegisterTag_4782B0 RegisterTag;
	SendCmdToCon_4393E0 ExecCmd;

	bool IsVisible(Vector End);
	bool GetRemainingIndex( Vector vieworg, entity_t* cent, Vector origin, float* remainingPower );

	void InitEngine()
	{
		GetWeapon = (GetWeapon_40FA50)0x40FA50;
		GetScreenMatrix = (GetScreenMatrix_4B7B40)0x4B7B40;
		WorldToScreen = (EngineW2S_416290)0x416290;
		RegisterTag = (RegisterTag_4782B0)0x4782B0;
		ExecCmd = (SendCmdToCon_4393E0)0x4393E0;
		CG_Trace = (CG_TRACE_4437D0)0x4437D0;

		for(int i = 0; i < 2047; i++)
		{
			Entity[i] = (entity_t*)(OFF_ENT + i * 516);
		}
		for(int i = 0; i < 18; i++)
		{
			Client[i] = ( client_t* ) ( 0x8EC2C8 + 0x52C * i );
		}
		CG = (CG_T*)0x7F58B8;
		CGS = (CGS_T*)0x7F1CF8;
		RefDef = (Refdef_t*)0x860030;
	}

};
extern EO_Engine Engine;