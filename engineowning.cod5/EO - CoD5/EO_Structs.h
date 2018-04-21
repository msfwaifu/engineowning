#pragma once

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec5_t[5];

typedef enum {
	qfalse,
	qtrue
} qboolean;

#define IsFriend(a)				( clientinfo[a].Team == clientinfo[cg->clientNum].Team )
#define	GENTITYNUM_BITS			10
#define	MAX_GENTITIES			(1<<GENTITYNUM_BITS)

#define MAX_PLAYERS				64

#define MAX_WEAPONS				28
#define Q_COLOR_ESCAPE	'^'
#define Q_IsColorString(p)		( p && *(p) == Q_COLOR_ESCAPE && *((p)+1) && *((p)+1) != Q_COLOR_ESCAPE )

#define Sound(a)				CreateThread(0,0, killSound, (void*)a, 0, 0)

#define MakeThread(a)			CreateThread(0,0, a, 0, 0, 0)
#define MakeThreadArg(a, b)		CreateThread(0,0, a, (LPVOID)b, 0, 0)

#define NullVector( Rec ) { Rec[0] = NULL; Rec[1] = NULL; Rec[2] = NULL; }
#define NoRecoil( Rec ) { NullVector( Rec[0] ); NullVector( Rec[1] ); NullVector( Rec[2] ); }

#define	SOLID			         0x1			
#define	LAVA			         0x16
#define	SLIME			         0x32

#define	QPAQUE	        ( SOLID | SLIME | LAVA )

typedef struct
{
	char			serverName[64];
	char			name[16];
	int				ping;
	char			mapName[64];
	char			gameType[4];
} game_t;

typedef enum {
	TEAM_FREE,
	TEAM_ALLIES,
	TEAM_ENEMIES,
	TEAM_SPECTATOR,

	TEAM_TEAMS
} team_t;

typedef struct{

	int		     	x; 
	int             y;
    int             Width;
    int             Height;
	float		    Fovx;
	float           Fovy;
	float           TotalFOV;
	Vector		    Vieworg;
	char            Unknown[4];
    vec3_t		    Viewaxis[3];
	char            Unknown2[17044];
	vec3_t		    refdefViewAngles;
} refdef_t;

typedef struct 
{
	char			unknown84[116]; 
	int				otherEntityNum; 
	int				otherEntityNum2;
	char			unknown124[32];
	int				EventParam; 
} entityState_t;


typedef struct
{
	int            infoValid; 
	char           Unkown[4];
	int            clientNum;
	char           Name[32]; 
	team_t         Team; 
	char           Unkown2[1324];

}clientInfo_t;



typedef struct
{
	int				snapFlags;
	int				Ping;
	int				ServerTime;
	char			unknown12[1244];
} snapshot_t;

typedef struct
{
	int				trType;
	int				trTime;
	int				trDuration;
	vec3_t			trBase;
	vec3_t			trDelta;
} trajectory_t;

typedef struct
{
	char _0x0000[40];
	Vector lerpOrigin; //0x0028 
	Vector lerpAngles; //0x0034 
   char _0x0040[172];
	Vector oldOrigin; //0x00EC 
    char _0x00F8[112];
	__int32 clientNum; //0x0168 
	__int32 eType; //0x016C 
	__int32 eFlags; //0x0170 
    char _0x0174[12];
	Vector newOrigin; //0x0180 
    char _0x018C[300];
	__int32 isAlive; //0x02B8 
}centity_t;//Size=0x02BC

typedef struct
{
	
	char            unknown1[8];  
	
	int             vidWidth;    
	int             vidHeight;    
	
	int             unknow;
	
	int             serverCommandSequence;    
	int             processedSnapshotNum;    
	qboolean        localServer;    
	
	char            unknown2[3];  
	
	char            GameMode[4];    
	
	char            unknown3[28];  
	
	char            ServerName[16];    
	
	char            unknown4[236];  
	
	int				MaxClients;
	char            MapName[64];  
	
	int             timeStartRound;  
    char            unknown392[38]; 
    int             TimeLimit;  
    int             VoteTime;  
    int             YesVote;  
    int             NoVote;  
    char            voteString[256];  
    int             levelStartTime;   

}cgs_t;

typedef struct playerState_s 
{
    int				commandTime;
    vec3_t			origin;
    vec3_t			velocity;
    int				ping;
} playerState_t; 

typedef struct
{
	int				SnapFlags;
    int				ServerTime;
    int				ServerTime2;
    char			_p00[0x104];
	playerState_t   Ps;
}Snapshot_t;

typedef struct
{
	int             clientNum;
    int             _p00[0x1C];
    Snapshot_t      *pSnap;
    Snapshot_t      *pNextSnap;
    char            _p01[0x46100];
    int             Time;
    char            _p02[0x307C];
    vec3_t			RefdefViewAngles;
    char            _p03[0x114];
    refdef_t		refdef;
    char            _p04[0x2F8C];
    int             CrosshairClientNum;
    int             CrosshairClientTime;
}cg_t;

typedef struct
{
	char*			weaponName;   
	char			unknown4[64]; 
}weaponInfo_t;

typedef struct
{
	char			unknown0[72];
	vec3_t			Recoil[3]; 
	float			ViewAngleY; 
	float			ViewAngleX;
	char			unknown1[36];
	vec3_t			ViewAxis[3]; 
	vec3_t			vOrigin;
}viewMatrix_t;

typedef struct
{
	char            unknown1[16];
	float    	    fraction;	
	char            unknown2[110];
	int 	        surfaceFlags;	
} trace_t;

typedef struct
{
	vec3_t Recoil1; //0x0000 
	vec3_t Recoil2; //0x000C 
    char _0x0018[12];
	Vector weaponAngles; //0x0024 

}matrix_t;//Size=0x0030

typedef struct
{
	char _0x0000[4];
	__int16 N01711DF5; //0x0004 
	__int16 j_helmet; //0x0006 
	__int16 j_head; //0x0008 
}tags_t;//Size=0x000A

extern float *			  ViewAngleX;
extern float *			  ViewAngleY;
extern float *			  DeltaAngles;

typedef void			  fontInfo_t;
typedef int				  qhandle_t;

extern clientInfo_t *	  clientinfo;
extern cg_t         *	  cg;
extern cgs_t        *     cgs;
extern centity_t    *     cg_entities;
extern weaponInfo_t *	  cg_weapons;
extern refdef_t     *	  refdef;
extern matrix_t		*	  matrix;
extern tags_t		*	  tags;

typedef struct
{
	__int32 clientNum; //0x0000 
	char _0x0004[16];
	__int32 isInGame; //0x0014 
	char _0x0018[156];
	Vector deltaAngles; //0x00B4 
}cg2_t;//Size=0x00C0

extern cg2_t* cg2;

typedef struct
{
	char _0x0000[12];
	char Name[32]; //0x000C 
	__int32 iTeam; //0x002C 
    char _0x0030[1164];
	__int32 isZoomed; //0x04BC 
    char _0x04C0[80];
	__int32 iWeaponID; //0x0510 
    char _0x0514[72];

}client_t;//Size=0x055C
extern client_t* client;





typedef struct// clientActive : 00FAB334 : cmdNum : 0xFAC934
{
	__int32 serverTime; //0x0000 
	__int32 buttons; //0x0004 
	int viewangles[3]; //0x0008 
	char _0x0014[24];

}usercmd_t;//Size=0x002C

typedef struct
{
	char _0x0000[324];
	__int32 weaponType; //0x0144 
	__int32 weaponClass; //0x0148 
	__int32 penetrateType; //0x014C 
	__int32 impactType; //0x0150 
    char _0x0154[4];
	__int32 fireType; //0x0158 
	__int32 clipType; //0x015C 
    char _0x0160[24];
	__int32 weaponStance; //0x0178 
    char _0x017C[1104];
	BOOL rifleBullet; //0x05CC 
}weapon_t;