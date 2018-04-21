typedef void			fontInfo_t;
typedef int				qhandle_t;

#define	ANGLE2SHORT(x)			((int)((x)*65536/360) & 65535)
#define BUTTON_ATTACK		( 1 << 0 )
#define ET_GENERAL 0
#define ET_PLAYER 1
#define ET_PLAYER_CORPSE 2
#define ET_ITEM 3
#define ET_MISSILE 4
#define ET_INVISIBLE 5
#define ET_SCRIPTMOVER 6
#define ET_SOUND_BLEND 7
#define ET_FX 8
#define ET_LOOP_FX 9
#define ET_PRIMARY_LIGHT 10
#define ET_TURRET 11
#define ET_HELICOPTER 12
#define ET_PLANE 13
#define ET_VEHICLE 14
#define ET_VEHICLE_COLLMAP 15
#define ET_VEHICLE_CORPSE 16
#define CMD_BACKUP 128
#define FL_NONE 0
#define FL_CROUCH 0x4
#define FL_PRONE 0x8
#define FL_ZOOM 0x80000
#define FL_FIRE 0x800000

#define MAGICNUMBER *(int*)0x10D2830

//comment
typedef struct
{
	char unknown0[8]; //0x0000
	__int32 scrWidth; //0x0008  
	__int32 scrHeight; //0x000C  
	char unknown16[12]; //0x0010
	__int32 iSequence; //0x001C  
	__int32 iLocal; //0x0020  
	char GameType[4]; //0x0024  
	char unknown40[28]; //0x0028
	char HostName[64]; //0x0044  
	char unknown132[196]; //0x0084
	__int32 maxPlayers; //0x0148  
	char unknown332[4]; //0x014C
	char MapName[64]; //0x0150  
	char unknown400[8]; //0x0190
}cgs_t;

typedef struct
{
	__int16 N0242EA59; //0x0000 
	__int16 Valid; //0x0002 
	char _0x0004[16];
	Vector lerpOrigin; //0x0014 
	Vector lerpAngles; //0x0020 
	char _0x002C[76];
	Vector oldOrigin; //0x0078 
	char _0x0084[76];
	__int32 clientNum; //0x00D0 
	__int16 eType; //0x00D4 
	char _0x00D6[18];
	Vector newOrigin; //0x00E8 
	char _0x00F4[64];
	__int16 weapon_backup; //0x0134 
	char _0x0136[98];
	__int16 weapon; //0x0198 
	char _0x019A[54];
	__int32 isAlive; //0x01D0 
	char _0x01D4[36];
}centity_t;//Size=0x01F8

typedef struct
{
	__int32 Valid; //0x0000 
	char _0x0004[8];
	char Name[16]; //0x000C 
	__int32 Team; //0x001C 
	char _0x0020[1112];
	__int32 weapon; //0x0478 
	char _0x047C[232];
}clientInfo_t;//Size=0x0564

typedef struct {
    int servertime; //0x0000
    int playerstate; //0x0004
    int staminatimer; //0x0008
    unsigned short playerstance; //0x000C
    char _pad[10];
    int velocity; //0x0018
    float Origin[3]; //0x001C
    float Velocity[3]; //0x0028
    char _pad1[44];
    float refdefViewAngleY; //0x0060
    float refdefViewAngleX; //0x0064
    char _pad2[232];
    int ClientNum; //0x0150
	char _pad3[4];
    float viewAngleY; //0x0158
    float viewAngleX; //0x015C
    char _pad4[4];
    int   playerStanceInt; //0x0164
    float playerStanceFlt; //0x0168
    char _pad5[80];
    int MaxEntities; //0x01BC
    char _0x01C0[68];
    int AdvancedUAV;                                 
    char _0x0208[0x38];                              //0x208
    int NextAttack;                                  //0x240 (0x9D64E0)
    char _0x0244[0x12C];                             //0x244
    int WeaponID;
} cg_t; 

typedef struct
{
	char _0x0000[8];
	__int32 x; //0x0008 
	__int32 y; //0x000C 
	float fov_x; //0x0010 
	float fov_y; //0x0014 
	Vector vieworg; //0x0018 
	Vector viewaxis[3]; //0x0024 
    char _0x0030[48908];
	Vector weaponAngles;//0xBF3C 
}refdef_t;


typedef struct
{
	char unknown01[6]; //0x0000 
	WORD j_helmet; //0x0006 
	WORD j_head; //0x0008 
	char _0x000A[2];
} EngineTags_t;//Size=0x000C

//typedef struct
//{
//    Vector Recoil;                                //0x0 (0x1140FEC)
//    Vector Origin;                                //0xC (0x1140FF8)
//    char _0x0018[0x80];                           //0x18
//    float ViewAngleY;                             //0x98 (0x1141084)
//    float ViewAngleX;                             //0x9C (0x1141088)
//}ViewMatrix_t; //[Addr: 0x1140FEC] [Size: 0xA0]

typedef struct
{
	vec3_t Recoil; //0x0000 
	vec3_t Origin; //0x000C 
    char _0x0018[12];
	float WeaponAngleY; //0x0024 
	float WeaponAngleX; //0x0028 
    char _0x002C[108];
	float ViewAngleY; //0x0098 
	float ViewAngleX; //0x009C 

}ViewMatrix_t;//Size=0x00A0

typedef struct
{
    float fraction; //0x0000 
    char _0x0004[60];
    DWORD materialType; //0x0040 
}trace_t;//Size=0x0044

typedef enum {
	TEAM_FFA,
	TEAM_ALLIES,
	TEAM_ENEMIES,
	TEAM_SPECTATOR,

	TEAM_TEAMS
} team_t;
/*
typedef struct
{
    int servertime; //0x0000 
	int buttons; //0x0004 
	int viewangles[3]; //0x0008 
    __int8 weaponID; //0x0014 
    __int8 weaponType; //0x0015
    WORD Unknown4; //0x0016 
    DWORD Unknown5; //0x0018 
    __int8 ForwardMove; //0x001C 
    __int8 SideMove; //0x001D
    WORD Unknown6; //0x001E 
    DWORD Unknown7; //0x0020
    DWORD Unknown8; //0x0024 
    DWORD Unknown9; //0x0028 
}usercmd_t;//Size=0x002C
*/

typedef struct
{
    int servertime; //0x0000 
    int buttons; //0x0004 
    int viewangles[3]; //0x0008 // below here is some usefull stuffs
   char lol[0x18];
}usercmd_t;//Size=0x002C

typedef struct
{
    usercmd_t usercmds[128];
    int currentCmdNum; // 0x16E8

    usercmd_t *GetUserCmd(int cmdNum)
    {
        int id = cmdNum & 0x7F;
        return &usercmds[id];
    }
}input_t;

extern cg_t * cg;
extern cgs_t * cgs;
extern clientInfo_t * clientinfo;
extern centity_t * cg_entities;
extern refdef_t * refdef;
extern ViewMatrix_t * viewmatrix;
extern EngineTags_t * tags;


typedef struct
{
	int		worldEntNum;	// 00
	int		skipNum;		// 04
	float	power;			// 08
	int		bulletType;		// 12
	char	Buttons[4];		// 16
	vec3_t	vieworg;		// 28
	vec3_t	start;			// 40
	vec3_t	end;			// 28
	vec3_t	viewDirection;	// 32
}bulletTrace_t;

