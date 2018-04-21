#include "EO_Main.h"
//comment

DWORD dwCreateCmdRetn = NULL;
DWORD dwDrawBulletDecalRetn = NULL;
DWORD dwDrawBulletDecal2Retn = NULL;

void IN_CreateCmd()
{
	/*static bool bAttack = false;
	usercmd_t *pCmd;


	__asm {
		mov pCmd, eax;
	}

	if(Aimbot.BestTarget != -1) {
		pCmd->buttons |= BUTTON_ATTACK;

		if( bAttack )
			pCmd->buttons &= ~BUTTON_ATTACK;

		bAttack = !bAttack;
	}*/
}

void IN_CreateCmd2( void )
{
	usercmd_t*pCmd = NULL;

	__asm
	{
		MOV pCmd,EAX;
	}

}

__declspec ( naked ) void IN_CreateCmdGate ( void )
{
	__asm
	{
		PUSHAD;
	}

	IN_CreateCmd2();

	__asm
	{
		POPAD;
		JMP dwCreateCmdRetn;
	}
}
DWORD dwOrig = 0;
LONG CALLBACK pVEH_Hook( PEXCEPTION_POINTERS pInfo )
{
	
	if( pInfo->ContextRecord->Eip == 0x4F9FB9 )
	{
		EO_Client.R_EndFrame();
		pInfo->ContextRecord->Ecx = ( DWORD ) 0x5AC46C8;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if( pInfo->ContextRecord->Eip == 0x4040CA )
	{
		EO_Client.CL_WritePacket();
		pInfo->ContextRecord->Ecx = 0x5AB5E54;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if ( pInfo->ContextRecord->Eip == 0x5CFC07 || pInfo->ContextRecord->Eip == 0x5CFC2B )
	{
			PDWORD pdwCreateCmdRetn = (PDWORD)( pInfo->ContextRecord->Esp + 0x3C );
			dwCreateCmdRetn = *pdwCreateCmdRetn;
			*pdwCreateCmdRetn = (DWORD)IN_CreateCmdGate;

			switch ( pInfo->ContextRecord->Eip )
			{
			case 0x5CFC07:
				pInfo->ContextRecord->Ecx = 0x5AB5EA0;
				break;
			case 0x5CFC2B:
				pInfo->ContextRecord->Edx = 0x5AB5EA0;
				break;
			default:
			return EXCEPTION_CONTINUE_SEARCH;
		}
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if( pInfo->ContextRecord->Eip == 0x00788CE1)
	{
		MessageBoxA(NULL,"OK","OK",MB_OK);
		VirtualProtect((void*)0x1141090,1,PAGE_EXECUTE_READWRITE,0);
		//memset((void*)0x1141090,0,44 * (*(int*)0x1142690) & 0x7F);
		//pInfo->ContextRecord->Eip = 0x00788CF5;
		return EXCEPTION_CONTINUE_EXECUTION;
	
	}
	
	return EXCEPTION_CONTINUE_SEARCH;
}

void ExitHandler() //um die config zu speichern 
{
	Menu.CreateConfig(CONFIG_NAME);
}

void dwMainThread( )
{
	Sleep( 2000 );

	AddVectoredExceptionHandler( TRUE,pVEH_Hook );
	atexit(ExitHandler);

	while( TRUE )
	{
		*reinterpret_cast< PDWORD_PTR >( 0x9DC394 ) = 0;
		*reinterpret_cast< PDWORD_PTR >( 0x113D96C ) = 0;
		//DWORD dwOldProtect;
		//VirtualProtect((void*)0x113DB98,1,PAGE_READONLY,&dwOldProtect);

		
		//*reinterpret_cast< PDWORD_PTR >( 0xC176AC ) = 0;
		Sleep( 2000 );
	}
}

void InitThread( void )
{
	CreateThread( NULL, NULL, ( LPTHREAD_START_ROUTINE )dwMainThread, NULL, NULL, NULL );
}