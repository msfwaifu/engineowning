#include "EO_Main.h"

EO_CClient EO_Client;

vec4_t				colWhite			= { 1.0f, 1.0f, 1.0f, 1.0f };

extern void Pickups();

void EO_CClient::R_EndFrame( )
{
	if(cg2->isInGame)
	{
		EO_Draw.InitializeDrawing();
		EO_Draw.DrawString(10,15,consoleFont,1.0,colWhite,"EngineOwning - Call of Duty: 5");
		
		float cX,cY;
		cX=refdef->Width/2;
		cY=refdef->Height/2;
		EO_Draw.DrawRect(cX-1,cY-(10)-1,3,20+2,1,colWhite);
		EO_Draw.DrawRect(cX-(10)-1,cY-1,20+2,3,1,colWhite);

		matrix->Recoil1[ 0 ] = 0.0f;
		matrix->Recoil1[ 1 ] = 0.0f;
		matrix->Recoil1[ 2 ] = 0.0f;
		matrix->Recoil2[ 0 ] = 0.0f;
		matrix->Recoil2[ 1 ] = 0.0f;
		matrix->Recoil2[ 2 ] = 0.0f;

		EO_Visuals.DrawESP();
		EO_Aimbot.InitializeAimbot();
	}
}

extern void FixSpread();

void EO_CClient::CL_WritePacket( )
{
	if(cg2->isInGame)
	{
		g_NoSpread.RemoveSpread();
	}
}