//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Exception Addresses
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OFFS_ENDFRAME_EXCEPTION 0x43A589
#define OFFS_ENDFRAME_CONTINUE 0x43A5A0
#define OFFS_ENDFRAME_DVAR 0x98B45C


//004902F3   8B0D 5047F400    MOV ECX,DWORD PTR DS:[F44750]            ; CoDWaWmp.0F3FB664
//004902F9   2B41 10          SUB EAX,DWORD PTR DS:[ECX+10]
#define OFFS_WRITEPACKET_EXECPTION 0x4902F9
#define OFFS_WRITEPACKET_CONTINUE 0xF3FB664
#define OFFS_WRITEPACKET_DVAR 0xF44750
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Game Addresses
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OFFS_REFDEF 0x9E676C
#define OFFS_CLIENTINFO 0xA76764
#define OFFS_ENTITY 0xA90930
#define OFFS_CGS 0x98B700
#define OFFS_CG 0x98FCE0
#define OFFS_VIEWMATRIX 0x9EEBA0
#define OFFS_SCOREINFO 0x79DC14
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Drawing Addresses
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define OFFS_REGISTERFONT 0x5F1EC0
#define OFFS_DRAWSTRING 0x5F6B00