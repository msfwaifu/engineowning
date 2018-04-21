#include "EO_Main.h"

//comment

typedef struct {
    int MaxEntNum;
    int SkipNum;
    float power;
    int impactType;
    char button[4];
    float viewOrigin[3];
    float start[3];
    float end[3];
    float viewAngle[3];
} BulletTrace_T;

typedef struct {
 float fraction;  //4 correct
 float normal[3];   //16   correct?
 char *material;  // 20   correct
 char unk1[8]; // 28
 int hitType; //32 probably wrong
 WORD hitId; // 34  not sure 
 char unk[7]; //41
 bool startsolid;  //42   not sure
 bool allsolid; //43
 char unk5; // 44
 vec3_t EndPos; //56 correct
 char unk6[4]; //60
 DWORD unk7; //64
 char unk8[8]; //72
} Trace_T; //Size=72 OR 64 
typedef struct
{
	//float Fraction; //4
	//float Normal[3]; //16
	//int Unk; //20
	//bool Unk1; //21
	//char unk2[3]; //24
	//int Unk3; //28
	//int Unk4; //32
	//int Unk5; //36
	//int Unk6; //40
	//int Unk7; //44
	//bool AllSolid; //45
	//char Unk[3]; //48
	//int Unk9; //52
	//int Unk10; //56
	//int Unk11; //60
	//bool unk
	//int Unk12; //64
	//
	//unsigned short hitID; //62

}NewTrace_t;



weapon_t EO_CUtils :: GetWeapon(int ID)
{
	return (*(weapon_t*)(*(DWORD*)(0x9BADD0 + (ID & 0xFF)*4)));
}

weapon_t *EO_CUtils::pGetWeapon(int ID)
{

	return ((weapon_t*)(*(DWORD*)(0x9BADD0 + (ID & 0xFF) * 4)));

}

BOOL Match ( const BYTE* pData, const BYTE* bMask, const char* szMask ) {
    for ( ; *szMask; ++szMask, ++pData, ++bMask )
        if ( *szMask == 'x' && *pData != *bMask )
            return false;
    return ( *szMask ) == NULL;
}
inline MODULEINFO GetModuleInfo ( LPCSTR szModule ) {
        MODULEINFO modinfo = {0};
        HMODULE hModule = GetModuleHandleA ( szModule );
        if ( hModule == 0 ) return modinfo;
        GetModuleInformation ( GetCurrentProcess(), hModule, &modinfo, sizeof ( MODULEINFO ) );
        return modinfo;
    }
DWORD FindPattern ( char* szSig, char* szMask ) {
    DWORD dwAddress = ( DWORD ) GetModuleHandleA ( NULL );
    DWORD dwLen = GetModuleInfo ( NULL ).SizeOfImage;

    for ( DWORD i = 0; i < dwLen; i++ )
        if ( Match ( ( BYTE* ) ( dwAddress + i ), ( BYTE* ) szSig, szMask ) )
            return ( DWORD ) ( dwAddress + i );

    return 0;
}


DWORD m_addr_GetPenetrationPower = FindPattern( "\x83\xEC\x0C\x55\x8B\x6C\x24\x1C\x85\xED\x75\x07\xD9\xEE\x5D\x83", "xxxxxxxxxxxxxxxx" );
DWORD m_addr_TraceBullet = FindPattern( "\x51\x53\x55\x8B\x6C\x24\x14\x57\x8D\x58\x2C\x8D\x78\x20\x8B\x40", "xxxxxxxxxxxxxxxx" );
DWORD m_addr_CopyTrace = FindPattern( "\x55\x8B\xEC\x53\x56\x57\x8B\x5D\x0C\x8B\x4D\x10\x81\xF9\x00\x10", "xxxxxxxxxxxxxxxx" );
DWORD m_addr_StepForward = FindPattern( "\x56\x8B\x74\x24\x0C\x56\xE8\x00\x00\x00\x00\x8B\x4C\x24\x0C\x0F", "xxxxxxx????xxxxx" );


float GetPenetrationPower( int weapon, int material )
{
    float result = 0.0f;
	unsigned long address =  m_addr_GetPenetrationPower ;
    __asm
    {
        push    [ material ];
        xor eax, eax;
        push    eax;
        push    [ weapon ];
        call    [ address ];
        add esp, 0xC;
        fstp    [ result ];
    }
 
     
   /* if ( *(float*)(0x9BABC0 + 12) > 1.0f )
    {
		if ( *(int*)(&clientinfo[ cg->ClientNum] + 0x38) & 0x4000000 )
        {
            result *= *(float*)(0x9BABC0 + 12);
        }
    }*/
 
    return result;
}
 

bool TraceBullet( BulletTrace_T* bulletTrace, Trace_T* trace, centity_t* cent, int material )
{
    int result = 0;
    unsigned long address =  m_addr_TraceBullet ;
    __asm
    {
        push    [ material ];
        push    [ cent ];
        mov esi, [ trace ];
        mov eax, [ bulletTrace ];
        call    [ address ];
        add esp, 8;
        mov [ result ], eax;
    }
 
    return ( result == 1 );
}
 

bool CopyTrace( void* output, void* input, int len )
{
    char result = 0;
    unsigned long address = m_addr_CopyTrace ;
    __asm
    {
        push    [ len ];
        push    [ input ];
        push    [ output ];
        call    [ address ];
        add esp, 0xC;
        mov [ result ], al;
    }
 
    return ( result == 1 );
}
 

bool StepForward( BulletTrace_T* bulletTrace, Trace_T* trace, float factor )
{
    char result = 0;
    unsigned long address =  m_addr_StepForward ;
    __asm
    {
        push    [ factor ];
        push    [ trace ];
        push    [ bulletTrace ];
        call    [ address ];
        add esp, 0xC;
        mov [ result ], al;
    }
 
    return ( result == 1 );
}

float EO_CUtils::GetRemainingPower( vec3_t vieworg, centity_t* Ent, int weapon, Vector origin )
{

    BulletTrace_T   bulletTrace;
    BulletTrace_T   bulletTrace_2;
	Trace_T     trace_2;
    Trace_T     trace;
	vec3_t      traceEndpos;
    bool hit = false;
    bool hit2 = false;
    bool v12 = false;
    int hitCount = 0;
 
    // Initialize the bullet trace.
	bulletTrace.MaxEntNum = 2048;
	bulletTrace.SkipNum = cg->ClientNum;
    bulletTrace.power = 1.0f;
	int index = cg->WeaponID;
	weapon_t info = GetWeapon(index);
	bulletTrace.impactType = info.iWeaponBulletType;
	VectorCopy( vieworg, bulletTrace.viewOrigin );
	VectorCopy( vieworg, bulletTrace.start );
	VectorCopy( origin, bulletTrace.end );
 
    Vector delta;
    VectorSubtract( bulletTrace.end, bulletTrace.start, delta );
 
    Vector angles;
	EO_Utils.vectoangles( delta, angles );
	EO_Utils.AngleVectors( angles, bulletTrace.viewAngle, NULL, NULL );




	hit = TraceBullet( &bulletTrace, &trace, &cg_entities[cg->ClientNum], 0 ); 
	


    if ( !hit )
    {
        return 1.0f;
    }
   
	if ( trace.allsolid )
    {
        return -1.0f;
    }
 
    while ( bulletTrace.power > 0.0f )
    {
       
		float penetrationPower1 = GetPenetrationPower( weapon, trace.hitType );
 
        if ( penetrationPower1 <= 0.0f )
        {
			break;
        }
 
       
		VectorCopy( trace.EndPos, traceEndpos ); 

        
        if ( !StepForward( &bulletTrace, &trace, 0.135f ) )
        {
            break;
        }
 
        
		hit = TraceBullet( &bulletTrace, &trace, &cg_entities[cg->ClientNum], trace.hitType ); 
 

		CopyTrace( &bulletTrace_2, &bulletTrace, sizeof( BulletTrace_T ) );
 
        
		VectorScale( bulletTrace.viewAngle, -1.0f, bulletTrace_2.viewAngle );       
		VectorCopy( bulletTrace.end, bulletTrace_2.start );                                
		VectorMA( traceEndpos, 0.01f, bulletTrace_2.viewAngle, bulletTrace_2.end );    
 
        
        CopyTrace( &trace_2, &trace, sizeof( Trace_T ) );
 
      
		VectorScale( trace_2.normal, -1.0f, trace_2.normal );
 
       
        if ( hit )
        {
            StepForward( &bulletTrace_2, &trace_2, 0.01f );
        }
 
       
		hit2 = TraceBullet( &bulletTrace_2, &trace_2,&cg_entities[cg->ClientNum], trace_2.hitType );
 
        v12 = ( hit2 && trace_2.startsolid || trace.allsolid && trace_2.allsolid );
		
	

        if ( !hit2 && !v12 )
        {
            if ( !hit )
            {  
                break;
            }
            else
            {
                goto LABEL_1;
            }
 
            continue;
        }
 
       
        float wallDepth = 0.0f;
        if ( v12 )
        {
			wallDepth = EO_Utils.GetDistance( bulletTrace_2.start, bulletTrace_2.end );
        }
        else
        {
			wallDepth = EO_Utils.GetDistance( traceEndpos, trace_2.normal ); 
        }
 
       
        if ( wallDepth < 1.0f )
        {
            wallDepth = 1.0f;
        }
 
       
        float penetrationPower2 = GetPenetrationPower( weapon, trace_2.hitType );
 
       
        float penetrationPower = 0.0f;
        if ( hit2 )
        {
            penetrationPower = min( penetrationPower1, penetrationPower2 );
        }
        else
        {
            penetrationPower = penetrationPower1;
        }
 
        if ( penetrationPower <= 0.0f )
        {
           
            return -1.0f;
        }
 
        
        bulletTrace.power -= wallDepth / penetrationPower;
 
LABEL_1:
        if ( !hit )
        {  
            break;
        }
        else
        {
           
			if ( trace.hitId != 1022 && trace.hitId != 1023 )
            {
                return bulletTrace.power;
            }
 
            if ( ++hitCount >= 5 )
            {
                break;
            }
        }
    }
 
    if ( !hit )
    {
        return bulletTrace.power;
    }
    else
    {
        return -1.0f;
    }
}



/*
bool cMW3Engine::IsVisible( CEntity* pEnt, Vector3 vWorldPos )
{
    bool bResult = false;
    trace_t mTrace;    

    Trace_(&mTrace, refDef->vOrigin, vWorldPos, vec3_origin, cg->clientNum, 0x803003 ); 
    if( mTrace.Fraction >= 0.97f )
        return true;

    if( gCvar.bAutoWall )
    {
        bResult = GetRemainingIndex( refDef->vOrigin, pEnt, vWorldPos );

        return( bResult );
    }
    return false;
}*/