typedef void			fontInfo_t;
typedef int				qhandle_t;

#define	ANGLE2SHORT(x)			((int)((x)*65536/360) & 65535)

#define TYPE_HUMAN				1
#define TYPE_WEAPON				3
#define TYPE_EXPLOSIVE			4
#define TYPE_TURRET				11
#define TYPE_HELICOPTER			12
#define TYPE_AIRSTRIKE			13

#define BUTTON_ATTACK		( 1 << 0 )
#define BUTTON_UNKNOWN		( 1 << 1 )	// Should be set in association with BUTTON_SPRINT
#define BUTTON_MELEE		( 1 << 2 )
#define BUTTON_USE			( 1 << 3 )
#define BUTTON_RELOAD		( 1 << 4 )
#define BUTTON_LEAN_LEFT	( 1 << 6 )
#define BUTTON_LEAN_RIGHT	( 1 << 7 )
#define BUTTON_PRONE		( 1 << 8 )
#define BUTTON_DUCK			( 1 << 9 )
#define BUTTON_JUMP			( 1 << 10 )
#define BUTTON_ZOOM			( 1 << 11 )
#define BUTTON_SPRINT		( 1 << 13 )
#define BUTTON_MENU			( 1 << 20 )

#define FL_NONE 0x0
#define FL_CROUCHED 0x4
#define FL_PRONE 0x8

typedef enum {
	TEAM_FFA,
	TEAM_ALLIES,
	TEAM_ENEMIES,
	TEAM_SPECTATOR,

	TEAM_TEAMS
} team_t;

typedef enum
{
	qfalse,
	qtrue
}qboolean;

typedef struct
{
	int			servertime;
	int			buttons;
	int			viewangles[ 3 ];
	char		weapon;
	BYTE		unknown0[ 1 ];
	char		forwardmode;
	char		rightmode;
	char		upmove;
	BYTE		unknown[ 7 ];
}usercmd_t;	// size = 0x20 (.32)

typedef struct 
{
    usercmd_t usercmds[128];
    int currentCmdNum;

    usercmd_t *GetUserCmd(int cmdNum)
    {
        int id = cmdNum & 0x7F;
        return &usercmds[id];
    }
}input_t;

typedef struct 
{
	int				x, y, Width, Height;
	float			Fovx, Fovy;
    Vector			vieworg; 
    Vector			viewaxis[3]; 
	char            unknown142[0x4050];
    vec3_t			refdefViewAngles;
}refdef_t;

typedef struct 
{
	char			szUnknown01[8]; 
	int				clientNum;
	char			Name[16];   
	int				Team;   
	char			szUnknown02[1136];
	int				zoomed;
	char			szUnknown03[56];
}clientInfo_t;

typedef struct
{
	__int32 currentValid; //0x0000 
    char _0x0004[24];
	vec3_t lerpOrigin; //0x001C 
	vec3_t lerpAngles; //0x0028 
    char _0x0034[64];
	vec3_t oldOrigin; //0x0074 
    char _0x0080[76];
	__int32 clientNum; //0x00CC 
	__int32 eType; //0x00D0 
	DWORD eFlags; //0x00D4 
    char _0x00D8[12];
	vec3_t newOrigin; //0x00E4 
    char _0x00F0[160];
	__int32 weapon; //0x0190 
    char _0x0194[44];
	__int32 isAlive; //0x01C0 
    char _0x01C4[24];
}entity_t;

typedef struct
{
    char unknown0[8]; //0x0000
    __int32 scrWidth; //0x0008  
    __int32 scrHeight; //0x000C  
    char unknown16[16]; //0x0010
    char gameType[4]; //0x0020  
    char unknown36[28]; //0x0024
    char serverName[256]; //0x0040  
    __int32 maxPlayers; //0x0140  
    char mapName[64]; //0x0144  
}cgs_t;//Size=0x0184(388)

typedef struct
{
	BYTE		unknown0[ 8 ];
	int			commandTime;
	int			pm_type;
	int			bobCycle;
	int			pm_flags;
	int			pm_time;
	Vector		origin;
	Vector		velocity;
	BYTE		unknown1[ 8 ];
	int			weaponTime;
	BYTE		unknown2[ 24 ];
	int			gravity;
	BYTE		unknown3[ 20 ];
	int			groundEntityNum;
	BYTE		unknown4[ 104 ];
	int			clientNum;			// 220
	BYTE		unknown5[ 8 ];
	int			weapon;
	int			weaponState;
	BYTE		unknown6[ 4 ];
	float		zoomProgress;
	BYTE		unknown7[ 16 ];
	Vector		viewangles;
	int			viewheight;
	float		viewheight_f;
	BYTE		unknown8[ 28 ];
	int			damageEvent;
	int			damageYaw;
	int			damagePitch;
	int			damageCount;
	int			health;		// 328
	BYTE		unknown9[ 16 ];
	int			reloadAmmoInfo[ 128 ];
	int			curAmmoInfo[ 128 ];
	BYTE		unknown10[ 62 ];
	int			entIndex;
	BYTE		unknown11[ 92 ];
	int			perks;
	BYTE		unknown12[ 48 ];
	int			shellshockTime;
	int			shellshockValue;
	BYTE		unknown13[ 2030 ];
}playerState_t;

typedef struct
{
	int				snapFlags;
	int				ping;
	int				serverTime;
	playerState_t	ps;
}snapshot_t;

typedef struct
{
	int				clientNum;//0
	BYTE			unknown0[ 16 ];
	bool			isInGame;
	int				latestSnapshotNum;
	int				latestSnapshotTime;
	snapshot_t*		snap;
	snapshot_t*		nextSnap;
	snapshot_t		activeSnapshots[ 2 ];
	BYTE			unknown1[ 0x44494 ];	// cgs_t is in here
	int				frametime;
	int				time;
	int				oldtime;
	BYTE			unknown2[ 12 ];
	playerState_t	predictedPlayerState;
	BYTE			unknown3[ 0x213C ];
    entity_t		predictedPlayerEntity;
	// Here is a weaponViewOffset struct (size = 0x30)
	BYTE			unknown4[ 76 ];
	refdef_t		refdef;
	// Offset till here = 0x49388(.299912)
	BYTE			unknown5[ 0x403C ];
	Vector			refdefViewAngles;
	BYTE			unknown6[ 0x2F8C ];
	int				crosshairClientNum;
	int				crosshairClientTime;//
	BYTE			unknown7[ 0x68 ];
	int				weaponSelect;
	BYTE			unknown8[ 0x74 ];
	int				damageTime;
	BYTE			unknown9[ 16 ];
	int				timeLiving;//4
	BYTE			unknown10[ 4 ];
	int				v_dmg_time;
	float			damageX;
	float			damageY;
	BYTE			unknown11[ 8 ];
	Vector			recoilAngles;
	BYTE			unknown12[ 0x18 ];
	Vector			weaponAngles;
	BYTE			unknown13[ 120 ];
	int				attackerTime;
	BYTE			unknown14[ 32 ];
	BYTE			unknown15[ 0xAE314 ];
}cg_t;

typedef struct
{
	char	_p00[60];
	Vector _p01;
	Vector	Recoil; 
	Vector	ViewAngle;
	char	unknown1[32];
	Vector	ViewAxis[3]; 
	Vector vOrigin;
}viewMatrix_t;

typedef struct
{
	int		worldEntNum;	// 00
	int		skipNum;		// 04
	float	power;			// 08
	int		bulletType;		// 12
	vec3_t	vieworg;		// 16
	vec3_t	start;			// 28
	vec3_t	end;			// 40
	vec3_t	viewDirection;	// 52
}bulletTrace_t;

/*
typedef struct
{
	float fraction;
	vec3_t endpos;
	int surfaceType;
	int surfaceFlags;
	char* surfaceName;
	int contents;
	short entNum;
	char szUnknown[8];
	Vector hitLocation;
	char szUnknown1[4];
	int lastHitSurface;
}trace_t;
*/
enum TraceHitType
{
  TRACE_HITTYPE_NONE = 0x0,
  TRACE_HITTYPE_ENTITY = 0x1,
  TRACE_HITTYPE_DYNENT_MODEL = 0x2,
  TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
};
struct trace_t
{
  float fraction;
  float normal[3];
  int surfaceFlags;
  int contents;
  const char *material;
  TraceHitType hitType;
  unsigned __int16 hitId;
  unsigned __int16 modelIndex;
  unsigned __int16 partName;
  unsigned __int16 partGroup;
  bool allsolid;
  bool startsolid;
  bool walkable;
};
struct weapon_t
{
	char _pad0[0x4]; // 0000
	char* displayName; // 0004
	char* AIOverlayDescription; // 0008
	void* gunModel; // 000C, XModel*
	void* gunModel2; // 0010, XModel*
	void* gunModel3; // 0014, XModel*
	void* gunModel4; // 0018, XModel*
	void* gunModel5; // 001C, XModel*
	void* gunModel6; // 0020, XModel*
	void* gunModel7; // 0024, XModel*
	void* gunModel8; // 0028, XModel*
	void* gunModel9; // 002C, XModel*
	void* gunModel10; // 0030, XModel*
	void* gunModel11; // 0034, XModel*
	void* gunModel12; // 0038, XModel*
	void* gunModel13; // 003C, XModel*
	void* gunModel14; // 0040, XModel*
	void* gunModel15; // 0044, XModel*
	void* gunModel16; // 0048, XModel*
	void* handModel; // 004C, XModel*
	char _pad1[0x4]; // 0050
	char* idleAnim; // 0054
	char* emptyIdleAnim; // 0058
	char* fireAnim; // 005C
	char* holdFireAnim; // 0060
	char* lastShotAnim; // 0064
	char* rechamberAnim; // 0068
	char* meleeAnim; // 006C
	char* meleeChargeAnim; // 0070
	char* reloadAnim; // 0074
	char* reloadEmptyAnim; // 0078
	char* reloadStartAnim; // 007C
	char* reloadEndAnim; // 0080
	char* raiseAnim; // 0084
	char* firstRaiseAnim; // 0088
	char* dropAnim; // 008C
	char* altRaiseAnim; // 0090
	char* altDropAnim; // 0094
	char* quickRaiseAnim; // 0098
	char* quickDropAnim; // 009C
	char* emptyRaiseAnim; // 00A0
	char* emptyDropAnim; // 00A4
	char* sprintInAnim; // 00A8
	char* sprintLoopAnim; // 00AC
	char* sprintOutAnim; // 00B0
	char* detonateAnim; // 00B4
	char* nightVisionWearAnim; // 00B8
	char* nightVisionRemoveAnim; // 00BC
	char* adsFireAnim; // 00C0
	char* adsLastShotAnim; // 00C4
	char* adsRechamberAnim; // 00C8
	char* adsUpAnim; // 00CC
	char* adsDownAnim; // 00D0
	char* modeName; // 00D4
	int hideTags; // 00D8, Type 33
	char _pad2[0xC]; // 00DC
	int notetrackSoundMap; // 00E8, Type 34
	char _pad3[0x3C]; // 00EC
	int playerAnimType; // 0128, Type 20
	int weaponType; // 012C, Type 12
	int weaponClass; // 0130, Type 13
	int penetrateType; // 0134, Type 15
	int impactType; // 0138, Type 16
	int inventoryType; // 013C, Type 26
	int fireType; // 0140, Type 27
	int offhandClass; // 0144, Type 19
	int stance; // 0148, Type 17
	int viewFlashEffect; // 014C, Type 8
	int worldFlashEffect; // 0150, Type 8
	int pickupSound; // 0154, Type 11
	int pickupSoundPlayer; // 0158, Type 11
	int ammoPickupSound; // 015C, Type 11
	int ammoPickupSoundPlayer; // 0160, Type 11
	int projectileSound; // 0164, Type 11
	int pullbackSound; // 0168, Type 11
	int pullbackSoundPlayer; // 016C, Type 11
	int fireSound; // 0170, Type 11
	int fireSoundPlayer; // 0174, Type 11
	int loopFireSound; // 0178, Type 11
	int loopFireSoundPlayer; // 017C, Type 11
	int stopFireSound; // 0180, Type 11
	int stopFireSoundPlayer; // 0184, Type 11
	int lastShotSound; // 0188, Type 11
	int lastShotSoundPlayer; // 018C, Type 11
	int emptyFireSound; // 0190, Type 11
	int emptyFireSoundPlayer; // 0194, Type 11
	int meleeSwipeSound; // 0198, Type 11
	int meleeSwipeSoundPlayer; // 019C, Type 11
	int meleeHitSound; // 01A0, Type 11
	int meleeMissSound; // 01A4, Type 11
	int rechamberSound; // 01A8, Type 11
	int rechamberSoundPlayer; // 01AC, Type 11
	int reloadSound; // 01B0, Type 11
	int reloadSoundPlayer; // 01B4, Type 11
	int reloadEmptySound; // 01B8, Type 11
	int reloadEmptySoundPlayer; // 01BC, Type 11
	int reloadStartSound; // 01C0, Type 11
	int reloadStartSoundPlayer; // 01C4, Type 11
	int reloadEndSound; // 01C8, Type 11
	int reloadEndSoundPlayer; // 01CC, Type 11
	int detonateSound; // 01D0, Type 11
	int detonateSoundPlayer; // 01D4, Type 11
	int nightVisionWearSound; // 01D8, Type 11
	int nightVisionWearSoundPlayer; // 01DC, Type 11
	int nightVisionRemoveSound; // 01E0, Type 11
	int nightVisionRemoveSoundPlayer; // 01E4, Type 11
	int altSwitchSound; // 01E8, Type 11
	int altSwitchSoundPlayer; // 01EC, Type 11
	int raiseSound; // 01F0, Type 11
	int raiseSoundPlayer; // 01F4, Type 11
	int firstRaiseSound; // 01F8, Type 11
	int firstRaiseSoundPlayer; // 01FC, Type 11
	int putawaySound; // 0200, Type 11
	int putawaySoundPlayer; // 0204, Type 11
	int bounceSound; // 0208, Type 23
	int viewShellEjectEffect; // 020C, Type 8
	int worldShellEjectEffect; // 0210, Type 8
	int viewLastShotEjectEffect; // 0214, Type 8
	int worldLastShotEjectEffect; // 0218, Type 8
	int reticleCenter; // 021C, Type 10
	int reticleSide; // 0220, Type 10
	int reticleCenterSize; // 0224
	int reticleSideSize; // 0228
	int reticleMinOfs; // 022C
	int activeReticleType; // 0230, Type 21
	float standMoveF; // 0234
	float standMoveR; // 0238
	float standMoveU; // 023C
	float standRotP; // 0240
	float standRotY; // 0244
	float standRotR; // 0248
	float duckedOfsF; // 024C
	float duckedOfsR; // 0250
	float duckedOfsU; // 0254
	float duckedMoveF; // 0258
	float duckedMoveR; // 025C
	float duckedMoveU; // 0260
	float duckedRotP; // 0264
	float duckedRotY; // 0268
	float duckedRotR; // 026C
	float proneOfsF; // 0270
	float proneOfsR; // 0274
	float proneOfsU; // 0278
	float proneMoveF; // 027C
	float proneMoveR; // 0280
	float proneMoveU; // 0284
	float proneRotP; // 0288
	float proneRotY; // 028C
	float proneRotR; // 0290
	float posMoveRate; // 0294
	float posProneMoveRate; // 0298
	float standMoveMinSpeed; // 029C
	float duckedMoveMinSpeed; // 02A0
	float proneMoveMinSpeed; // 02A4
	float posRotRate; // 02A8
	float posProneRotRate; // 02AC
	float standRotMinSpeed; // 02B0
	float duckedRotMinSpeed; // 02B4
	float proneRotMinSpeed; // 02B8
	void* worldModel; // 02BC, XModel*
	void* worldModel2; // 02C0, XModel*
	void* worldModel3; // 02C4, XModel*
	void* worldModel4; // 02C8, XModel*
	void* worldModel5; // 02CC, XModel*
	void* worldModel6; // 02D0, XModel*
	void* worldModel7; // 02D4, XModel*
	void* worldModel8; // 02D8, XModel*
	void* worldModel9; // 02DC, XModel*
	void* worldModel10; // 02E0, XModel*
	void* worldModel11; // 02E4, XModel*
	void* worldModel12; // 02E8, XModel*
	void* worldModel13; // 02EC, XModel*
	void* worldModel14; // 02F0, XModel*
	void* worldModel15; // 02F4, XModel*
	void* worldModel16; // 02F8, XModel*
	void* worldClipModel; // 02FC, XModel*
	void* rocketModel; // 0300, XModel*
	void* knifeModel; // 0304, XModel*
	void* worldKnifeModel; // 0308, XModel*
	int hudIcon; // 030C, Type 10
	int hudIconRatio; // 0310, Type 29
	int ammoCounterIcon; // 0314, Type 10
	int ammoCounterIconRatio; // 0318, Type 30
	int ammoCounterClip; // 031C, Type 28
	int startAmmo; // 0320
	char* ammoName; // 0324
	char _pad4[0x4]; // 0328
	char* clipName; // 032C
	char _pad5[0x4]; // 0330
	int maxAmmo; // 0334
	int clipSize; // 0338
	int shotCount; // 033C
	char* sharedAmmoCapName; // 0340
	char _pad6[0x4]; // 0344
	int sharedAmmoCap; // 0348
	int damage; // 034C
	int playerDamage; // 0350
	int meleeDamage; // 0354
	char _pad7[0x4]; // 0358
	int fireDelay; // 035C, Type 7
	int meleeDelay; // 0360, Type 7
	int meleeChargeDelay; // 0364, Type 7
	int detonateDelay; // 0368, Type 7
	int fireTime; // 036C, Type 7
	int rechamberTime; // 0370, Type 7
	int rechamberBoltTime; // 0374, Type 7
	int holdFireTime; // 0378, Type 7
	int detonateTime; // 037C, Type 7
	int meleeTime; // 0380, Type 7
	int meleeChargeTime; // 0384, Type 7
	int reloadTime; // 0388, Type 7
	int reloadShowRocketTime; // 038C, Type 7
	int reloadEmptyTime; // 0390, Type 7
	int reloadAddTime; // 0394, Type 7
	int reloadStartTime; // 0398, Type 7
	int reloadStartAddTime; // 039C, Type 7
	int reloadEndTime; // 03A0, Type 7
	int dropTime; // 03A4, Type 7
	int raiseTime; // 03A8, Type 7
	int altDropTime; // 03AC, Type 7
	int altRaiseTime; // 03B0, Type 7
	int quickDropTime; // 03B4, Type 7
	int quickRaiseTime; // 03B8, Type 7
	int firstRaiseTime; // 03BC, Type 7
	int emptyRaiseTime; // 03C0, Type 7
	int emptyDropTime; // 03C4, Type 7
	int sprintInTime; // 03C8, Type 7
	int sprintLoopTime; // 03CC, Type 7
	int sprintOutTime; // 03D0, Type 7
	int nightVisionWearTime; // 03D4, Type 7
	int nightVisionWearTimeFadeOutEnd; // 03D8, Type 7
	int nightVisionWearTimePowerUp; // 03DC, Type 7
	int nightVisionRemoveTime; // 03E0, Type 7
	int nightVisionRemoveTimePowerDown; // 03E4, Type 7
	int nightVisionRemoveTimeFadeInStart; // 03E8, Type 7
	int fuseTime; // 03EC, Type 7
	int aifuseTime; // 03F0, Type 7
	BOOL requireLockonToFire; // 03F4
	BOOL noAdsWhenMagEmpty; // 03F8
	BOOL avoidDropCleanup; // 03FC
	float autoAimRange; // 0400
	float aimAssistRange; // 0404
	float aimAssistRangeAds; // 0408
	float aimPadding; // 040C
	float enemyCrosshairRange; // 0410
	BOOL crosshairColorChange; // 0414
	float moveSpeedScale; // 0418
	float adsMoveSpeedScale; // 041C
	float sprintDurationScale; // 0420
	float adsZoomFov; // 0424
	float adsZoomInFrac; // 0428
	float adsZoomOutFrac; // 042C
	int adsOverlayShader; // 0430, Type 10
	int adsOverlayShaderLowRes; // 0434, Type 10
	int adsOverlayReticle; // 0438, Type 14
	int adsOverlayInterface; // 043C, Type 25
	float adsOverlayWidth; // 0440
	float adsOverlayHeight; // 0444
	float adsBobFactor; // 0448
	float adsViewBobMult; // 044C
	float hipSpreadStandMin; // 0450
	float hipSpreadDuckedMin; // 0454
	float hipSpreadProneMin; // 0458
	float hipSpreadMax; // 045C
	float hipSpreadDuckedMax; // 0460
	float hipSpreadProneMax; // 0464
	float hipSpreadDecayRate; // 0468
	float hipSpreadFireAdd; // 046C
	float hipSpreadTurnAdd; // 0470
	float hipSpreadMoveAdd; // 0474
	float hipSpreadDuckedDecay; // 0478
	float hipSpreadProneDecay; // 047C
	float hipReticleSidePos; // 0480
	int adsTransInTime; // 0484, Type 7
	int adsTransOutTime; // 0488, Type 7
	float adsIdleAmount; // 048C
	float hipIdleAmount; // 0490
	float adsIdleSpeed; // 0494
	float hipIdleSpeed; // 0498
	float idleCrouchFactor; // 049C
	float idleProneFactor; // 04A0
	float gunMaxPitch; // 04A4
	float gunMaxYaw; // 04A8
	float swayMaxAngle; // 04AC
	float swayLerpSpeed; // 04B0
	float swayPitchScale; // 04B4
	float swayYawScale; // 04B8
	float swayHorizScale; // 04BC
	float swayVertScale; // 04C0
	float swayShellShockScale; // 04C4
	float adsSwayMaxAngle; // 04C8
	float adsSwayLerpSpeed; // 04CC
	float adsSwayPitchScale; // 04D0
	float adsSwayYawScale; // 04D4
	float adsSwayHorizScale; // 04D8
	float adsSwayVertScale; // 04DC
	BOOL rifleBullet; // 04E0
	BOOL armorPiercing; // 04E4
	BOOL boltAction; // 04E8
	BOOL aimDownSight; // 04EC
	BOOL rechamberWhileAds; // 04F0
	float adsViewErrorMin; // 04F4
	float adsViewErrorMax; // 04F8
	BOOL cookOffHold; // 04FC
	BOOL clipOnly; // 0500
	BOOL adsFire; // 0504
	BOOL cancelAutoHolsterWhenEmpty; // 0508
	BOOL suppressAmmoReserveDisplay; // 050C
	BOOL enhanced; // 0510
	BOOL laserSightDuringNightvision; // 0514
	int killIcon; // 0518, Type 10
	int killIconRatio; // 051C, Type 31
	BOOL flipKillIcon; // 0520
	int dpadIcon; // 0524, Type 10
	int dpadIconRatio; // 0528, Type 32
	BOOL noPartialReload; // 052C
	BOOL segmentedReload; // 0530
	int reloadAmmoAdd; // 0534
	int reloadStartAdd; // 0538
	char* altWeapon; // 053C
	char _pad8[0x4]; // 0540
	int dropAmmoMin; // 0544
	int dropAmmoMax; // 0548
	BOOL blocksProne; // 054C
	BOOL silenced; // 0550
	int explosionRadius; // 0554
	int explosionRadiusMin; // 0558
	int explosionInnerDamage; // 055C
	int explosionOuterDamage; // 0560
	float damageConeAngle; // 0564
	int projectileSpeed; // 0568
	int projectileSpeedUp; // 056C
	int projectileSpeedForward; // 0570
	int projectileActivateDist; // 0574
	float projectileLifetime; // 0578
	float timeToAccelerate; // 057C
	float projectileCurvature; // 0580
	void* projectileModel; // 0584, XModel*
	int projExplosionType; // 0588, Type 18
	int projExplosionEffect; // 058C, Type 8
	BOOL projExplosionEffectForceNormalUp; // 0590
	int projDudEffect; // 0594, Type 8
	int projExplosionSound; // 0598, Type 11
	int projDudSound; // 059C, Type 11
	BOOL projImpactExplode; // 05A0
	int stickiness; // 05A4, Type 24
	BOOL hasDetonator; // 05A8
	BOOL timedDetonation; // 05AC
	BOOL rotate; // 05B0
	BOOL holdButtonToThrow; // 05B4
	BOOL freezeMovementWhenFiring; // 05B8
	float lowAmmoWarningThreshold; // 05BC
	float parallelDefaultBounce; // 05C0
	float parallelBarkBounce; // 05C4
	float parallelBrickBounce; // 05C8
	float parallelCarpetBounce; // 05CC
	float parallelClothBounce; // 05D0
	float parallelConcreteBounce; // 05D4
	float parallelDirtBounce; // 05D8
	float parallelFleshBounce; // 05DC
	float parallelFoliageBounce; // 05E0
	float parallelGlassBounce; // 05E4
	float parallelGrassBounce; // 05E8
	float parallelGravelBounce; // 05EC
	float parallelIceBounce; // 05F0
	float parallelMetalBounce; // 05F4
	float parallelMudBounce; // 05F8
	float parallelPaperBounce; // 05FC
	float parallelPlasterBounce; // 0600
	float parallelRockBounce; // 0604
	float parallelSandBounce; // 0608
	float parallelSnowBounce; // 060C
	float parallelWaterBounce; // 0610
	float parallelWoodBounce; // 0614
	float parallelAsphaltBounce; // 0618
	float parallelCeramicBounce; // 061C
	float perpendicularCeramicBounce; // 061C
	float parallelPlasticBounce; // 0620
	float perpendicularPlasticBounce; // 0620
	float parallelRubberBounce; // 0624
	float perpendicularRubberBounce; // 0624
	float parallelCushionBounce; // 0628
	float parallelFruitBounce; // 062C
	float parallelPaintedMetalBounce; // 0630
	float perpendicularDefaultBounce; // 0634
	float perpendicularBarkBounce; // 0638
	float perpendicularBrickBounce; // 063C
	float perpendicularCarpetBounce; // 0640
	float perpendicularClothBounce; // 0644
	float perpendicularConcreteBounce; // 0648
	float perpendicularDirtBounce; // 064C
	float perpendicularFleshBounce; // 0650
	float perpendicularFoliageBounce; // 0654
	float perpendicularGlassBounce; // 0658
	float perpendicularGrassBounce; // 065C
	float perpendicularGravelBounce; // 0660
	float perpendicularIceBounce; // 0664
	float perpendicularMetalBounce; // 0668
	float perpendicularMudBounce; // 066C
	float perpendicularPaperBounce; // 0670
	float perpendicularPlasterBounce; // 0674
	float perpendicularRockBounce; // 0678
	float perpendicularSandBounce; // 067C
	float perpendicularSnowBounce; // 0680
	float perpendicularWaterBounce; // 0684
	float perpendicularWoodBounce; // 0688
	float perpendicularAsphaltBounce; // 068C
	char _pad9[0xC]; // 0690
	float perpendicularCushionBounce; // 069C
	float perpendicularFruitBounce; // 06A0
	float perpendicularPaintedMetalBounce; // 06A4
	int projTrailEffect; // 06A8, Type 8
	float projectileRed; // 06AC
	float projectileGreen; // 06B0
	float projectileBlue; // 06B4
	int guidedMissileType; // 06B8, Type 22
	float maxSteeringAccel; // 06BC
	int projIgnitionDelay; // 06C0
	int projIgnitionEffect; // 06C4, Type 8
	int projIgnitionSound; // 06C8, Type 11
	float adsAimPitch; // 06CC
	float adsCrosshairInFrac; // 06D0
	float adsCrosshairOutFrac; // 06D4
	int adsGunKickReducedKickBullets; // 06D8
	float adsGunKickReducedKickPercent; // 06DC
	float adsGunKickPitchMin; // 06E0
	float adsGunKickPitchMax; // 06E4
	float adsGunKickYawMin; // 06E8
	float adsGunKickYawMax; // 06EC
	float adsGunKickAccel; // 06F0
	float adsGunKickSpeedMax; // 06F4
	float adsGunKickSpeedDecay; // 06F8
	float adsGunKickStaticDecay; // 06FC
	float adsViewKickPitchMin; // 0700
	float adsViewKickPitchMax; // 0704
	float adsViewKickYawMin; // 0708
	float adsViewKickYawMax; // 070C
	float adsViewKickCenterSpeed; // 0710
	char _pad10[0x8]; // 0714
	float adsSpread; // 071C
	int hipGunKickReducedKickBullets; // 0720
	float hipGunKickReducedKickPercent; // 0724
	float hipGunKickPitchMin; // 0728
	float hipGunKickPitchMax; // 072C
	float hipGunKickYawMin; // 0730
	float hipGunKickYawMax; // 0734
	float hipGunKickAccel; // 0738
	float hipGunKickSpeedMax; // 073C
	float hipGunKickSpeedDecay; // 0740
	float hipGunKickStaticDecay; // 0744
	float hipViewKickPitchMin; // 0748
	float hipViewKickPitchMax; // 074C
	float hipViewKickYawMin; // 0750
	float hipViewKickYawMax; // 0754
	float hipViewKickCenterSpeed; // 0758
	char _pad11[0x8]; // 075C
	float fightDist; // 0764
	float maxDist; // 0768
	char* aiVsAiAccuracyGraph; // 076C
	char* aiVsPlayerAccuracyGraph; // 0770
	char _pad12[0x20]; // 0774
	int adsReloadTransTime; // 0794, Type 7
	float leftArc; // 0798
	float rightArc; // 079C
	float topArc; // 07A0
	float bottomArc; // 07A4
	float accuracy; // 07A8
	float aiSpread; // 07AC
	float playerSpread; // 07B0
	float minVertTurnSpeed; // 07B4
	float minHorTurnSpeed; // 07B8
	float maxVertTurnSpeed; // 07BC
	float maxHorTurnSpeed; // 07C0
	float pitchConvergenceTime; // 07C4
	float yawConvergenceTime; // 07C8
	float suppressionTime; // 07CC
	float maxRange; // 07D0
	float animHorRotateInc; // 07D4
	float playerPositionDist; // 07D8
	char* useHintString; // 07DC
	char* dropHintString; // 07E0
	char _pad13[0x8]; // 07E4
	float horizViewJitter; // 07EC
	float vertViewJitter; // 07F0
	char* script; // 07F4
	char _pad14[0x8]; // 07F8
	int minDamage; // 0800
	int minPlayerDamage; // 0804
	float maxDamageRange; // 0808
	float minDamageRange; // 080C
	float destabilizationRateTime; // 0810
	float destabilizationCurvatureMax; // 0814
	int destabilizeDistance; // 0818
	float locNone; // 081C
	float locHelmet; // 0820
	float locHead; // 0824
	float locNeck; // 0828
	float locTorsoUpper; // 082C
	float locTorsoLower; // 0830
	float locRightArmUpper; // 0834
	float locLeftArmUpper; // 0838
	float locRightArmLower; // 083C
	float locLeftArmLower; // 0840
	float locRightHand; // 0844
	float locLeftHand; // 0848
	float locRightLegUpper; // 084C
	float locLeftLegUpper; // 0850
	float locRightLegLower; // 0854
	float locLeftLegLower; // 0858
	float locRightFoot; // 085C
	float locLeftFoot; // 0860
	float locGun; // 0864
	char* fireRumble; // 0868
	char* meleeImpactRumble; // 086C
	float adsDofStart; // 0870
	float adsDofEnd; // 0874
};

typedef struct
{
	__int32 clientNum; //0x0000 
	__int32 score; //0x0004 
	__int32 ping; //0x0008 
	__int32 deaths; //0x000C 
    char _0x0010[4];
	__int32 kills; //0x0014 
    char _0x0018[4];
	__int32 assists; //0x001C 
    char _0x0020[8];
}scoreInfo_t;//Size=0x0028

typedef struct
{
	char			unknown0[2];
	BYTE			currentValid;  
	char			unknown3[25]; 
	vec3_t			lerpOrigin; 
	vec3_t			lerpAngles; 
	char			unknown52[64]; 
	vec3_t			newOrigin; 
	char			unknown128[76]; 
	int				clientNum;   
	DWORD			eType;   
	DWORD			eFlags;   
	char			unknown216[12]; 
	vec3_t			oldOrigin; 
	char			unknown240[160]; 
	int				weapon;  
	char			unknown404[44]; 
	int				isAlive;   
	char			unknown452[24];
} centity_t;


extern refdef_t* refdef;
extern clientInfo_t* clientInfo;
extern entity_t* cg_entities;
extern cgs_t* cgs;
extern cg_t* cg;
extern viewMatrix_t* viewMatrix;
extern scoreInfo_t * cg_scores;