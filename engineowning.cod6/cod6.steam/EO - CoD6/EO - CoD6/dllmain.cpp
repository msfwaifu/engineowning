// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "EO_Main.h"


bool Silent = false;
bool Init = false;
void DoHackStuff()
{
	if(!Init)
	{
		Draw.Init();
		Engine.InitEngine();
		Init = true;
	}

	if(GetAsyncKeyState(VK_F1) & 0x1)
		Engine.ExecCmd(0,0,"openscriptmenu owned endround");
	if(GetAsyncKeyState(VK_F2) & 0x1)
		Silent = !Silent;

	Aimbot.FoundEnemy = false;
	Aimbot.LastDifference = 99999999999;

	for(int i = 0; i < 2047; i++)
	{
		if ( Entity[i]->eType == ET_PLAYER && i < 18 && Entity[i]->iAlive & 1 && Client[i]->IsValid && CG->clientNum != Client[i]->clientNum) 
		{
			bool enemy = ! ( ( ( Client[i]->iTeam == 1 ) || ( Client[i]->iTeam == 2 ) ) && ( Client[i]->iTeam == Client[CG->clientNum]->iTeam ) );
			
			
			
			if(enemy)
			{
				ESP.DrawBox(i,BOX,false);
				ESP.DrawName(i,RED,false);
				Aimbot.CalculateBestTarget(i);
			}
			else
			{
				ESP.DrawBox(i,BOX_VIS,false);
				ESP.DrawName(i,GREEN,false);
			}
		
		}
	}
	if(Aimbot.FoundEnemy && !Silent)
	{
		float Vec[2];
		Vector BonePos;

		Engine.GetTagPos(Entity[Aimbot.BestTarget],"j_head",BonePos);

		Aimbot.GetAngleToOrigin(BonePos,Vec[0],Vec[1]);
		VIEWANGLE_X += Vec[0];
		VIEWANGLE_Y += Vec[1];
	}
}


bool InitDVARS = false;
void Post_EndFrame()
{


	Draw.DrawString(20,30,Draw.ConsoleFont,WHITE,"engineowning - CoD 6");
	
	//Draw.DrawString(20,45,Draw.ConsoleFont,RED,(char*)ServerBuffer.c_str());

	DoHackStuff();
}

input_t* Input = (input_t*)0xB36A4C;

void CL_WritePacket()
{
	if(!ISINGAME)
		return;
	if(!(Entity[CG->clientNum]->iAlive & 1))
		return;


	usercmd_t* oldcmd = Input->GetUserCmd( Input->currentCmdNum );
	usercmd_t* next = Input->GetUserCmd( Input->currentCmdNum + 1 );

	*next = *oldcmd;
	oldcmd->commandTime--;
	Input->currentCmdNum++;

	if(*(float*)0x7F5B78 != 1.0f)
	{
		int vSpread[2];			
		Engine.GetSpreadAngle(&vSpread[0],&vSpread[1],oldcmd->commandTime);
		oldcmd->viewangles[0] += vSpread[0];
		oldcmd->viewangles[1] += vSpread[1];
	}
	if(Aimbot.FoundEnemy)
	{
		oldcmd->buttons |= (1 << 0 );
		if( next->buttons & (1 << 0 ) )
			next->buttons &= 0xFFFFFFFEu;
		if(Silent)
		{
			float Vec[2];
			Vector BonePos;

			Engine.GetTagPos(Entity[Aimbot.BestTarget],"j_head",BonePos);

			Aimbot.GetAngleToOrigin(BonePos,Vec[0],Vec[1]);
			oldcmd->viewangles[0] += ANGLE2SHORT(Vec[1]);
			oldcmd->viewangles[1] += ANGLE2SHORT(Vec[0]);
		}
	}
}


LONG CALLBACK pVectoredExceptionHandler( PEXCEPTION_POINTERS pInfo )
{
	if( pInfo->ContextRecord->Eip == 0x0058178A )
	{
		Post_EndFrame( );
		pInfo->ContextRecord->Eip = 0x005817A5;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	if( pInfo->ContextRecord->Eip == 0x0044399A )
    {
        CL_WritePacket();
        pInfo->ContextRecord->Edx = 0x0645D090;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
	return EXCEPTION_CONTINUE_SEARCH;
}
void HookCOD6( )
{
	//CreateThread(0,0,(LPTHREAD_START_ROUTINE)TrackerThread,0,0,0);
	
	while(*(int*)0xA86858 != 1)
	{
		Sleep(1000);
	}

	

	AddVectoredExceptionHandler( TRUE,pVectoredExceptionHandler );

	

	while( TRUE )
	{
		//Engine.ExecCmd(0,0,"cg_fov 90");
		*reinterpret_cast< PDWORD_PTR >( 0xB32B44 ) = 0; //Crasht noch
		*reinterpret_cast< PDWORD_PTR >( 0x7F1C54 ) = 0;
		Sleep( 2000 );
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	DisableThreadLibraryCalls(hModule);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)HookCOD6,NULL,NULL,NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

