
#define OFF_MAGICNUMBER 0xAC7438

#define OFF_ENT 0x8F8AF8

#define VIEWANGLE_Y *(float*)0xB36A40
#define VIEWANGLE_X *(float*)0xB36A44
enum EntTypes
{
    ET_GENERAL,
    ET_PLAYER,
    ET_PLAYER_CORPSE,
    ET_ITEM,
    ET_MISSILE,
    ET_INVISIBLE,
    ET_SCRIPTMOVER,
    ET_SOUND_MOVER,
    ET_FX,
    ET_LOOP_FX,
    ET_PRIMARY_LIGHT,
    ET_TURRET,
    ET_HELICOPTER,
    ET_PLANE,
    ET_VEHICLE,
    ET_VEHICLE_COLLMAP,
    ET_VEHICLE_CORPSE,
    ET_VEHICLE_SPAWNER,
};

class client_t
{
public:
    int IsValid; //0x0000 
    int IsValid2; //0x0004 
    int clientNum; //0x0008 
    char szName[16]; //0x000C 
    int iTeam; //0x001C 
    int iTeam2; //0x0020 
    int iRank; //0x0024 rank+1 
	char _0x0028[4];
    int iPerk; //0x002C 
    int iKills; //0x0030
    int iScore; //0x0034 
char _0x0038[968];
    Vector vAngles; //0x0400 
char _0x040C[136];
    int IsShooting; //0x0494 
char _0x0498[4];
	int IsZoomed; //0x049C 
char _0x04A0[68];
    int weaponType; //0x04E4 
char _0x04E8[24];
    int weaponID2; //0x0500 
char _0x0504[40];

};//Size=0x052C

class Refdef_t
{
public:
    int x; //0x0000 
    int y; //0x0004 
    int iWidth; //0x0008 
    int iHeight; //0x000C 
    float fovX; //0x0010 
    float fovY; //0x0014 
    Vector vOrigin; //0x0018 
    Vector vViewAxis[3]; //0x0024 
char _0x0048[4];
    Vector vDunno; //0x004C 
    int iTime; //0x0058 
    int iMenu; //0x005C 
char _0x0060[16128];
    Vector refdefViewAngles; //0x3F60 
char _0x3F6C[276];

};//Size=0x4080

class CG_T
{
public:
    int servertime; 
char _0x0004[13132];
    int clientNum; 
char _0x3354[2348];

};//Size=0x3C80

class CGS_T
{
public:
char _0x0000[8];
    int iWidth; //0x0008 
    int iHeight; //0x000C 
    int iScale; //0x0010
char _0x0010[4];
    int iTime; //0x0018 
char _0x001C[4];
    char szGameType[4]; //0x0020 
char _0x0024[288];
    int iMaxPlayers; //0x0144 
char _0x0148[4];
    char szMap[64]; //0x014C 
char _0x018C[1012];

};//Size=0x0580

class trace_t
{
public:
  float fraction;
  float normal[3];
  int surfaceFlags;
  int contents;
  const char *material;
  int hitType;
  unsigned __int16 hitId;
  unsigned __int16 modelIndex;
  unsigned __int16 partName;
  unsigned __int16 partGroup;
  bool allsolid;
  bool startsolid;
  bool walkable;
};
class entity_t
{
public:
char _0x0000[24];
    Vector vOrigin; //0x0018 
char _0x0024[72];
    int IsZooming; //0x006C 
char _0x0070[12];
    Vector vOldOrigin; //0x007C 
char _0x0088[84];
    int clientNum; //0x00DC 
    int eType; //0x00E0 
    int eFlags; //0x00E4 
char _0x00E8[12];
    Vector vNewOrigin; //0x00F4 
char _0x0100[108];
    int pickupItemID; //0x016C
    int clientNum2; //0x0170 
char _0x0174[52];
    BYTE weaponID; //0x01A8 
char _0x01A9[51];
    int iAlive; //0x01DC 
char _0x01E0[32];
    int clientNum3; //0x0200 

};//Size=0x0204



class usercmd_t
{
public:
    int commandTime; //0x0000 
    int buttons; //0x0004 
    int viewangles[3]; //0x0008 
char _0x0014[20];

};//Size=0x0028

class input_t
{
public:
    usercmd_t cmds[128]; //0x0000 
    int currentCmdNum; //0x2E40
    
    usercmd_t* GetUserCmd( int cmdNum )
    {
        return &cmds[ cmdNum & 0x7F ];
    }
};//Size=0x2E44

class playerstate_t
{
public:
    int commandTime;
	char unk[113104];
	Vector Recoil;
};

class kbutton_t
{
public:
    int down[2]; //0x0000 
    unsigned int downtime; //0x0008 
    unsigned int msec; //0x000C 
    BYTE active; //0x0010 
    BYTE wasPressed; //0x0011 
char _0x0012[2];

};//Size=0x0014


typedef struct
{
    int VictimWeapon; //0000
    int KillerWeapon; //0004
                char unknown0[116];
    int VictimEntNum; //007C
    int KillerEntNum; //0080
                    char unknown5[32];
    int KillType; 
    
}entitystate_t;  




typedef struct 
{
	char unk[560];
	int WeaponType;
}weapon_t;


class bulletTrace_t
{
public:
    __int32 worldEntNum; //0x0000
    __int32 skipNum; //0x0004
    float power; //0x0008
    __int32 bulletType; //0x000C
    Vector vieworg; //0x0010
    Vector start; //0x001C
    Vector end; //0x0028
    Vector viewDirection; //0x0034
};//Size=0x0040