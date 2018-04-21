#include "EO_Main.h"

DWORD dwDrawBulletDecalRetn = NULL;
DWORD dwEntNum = NULL;
vec3_t vTraceEndPos;

__declspec( naked ) void CG_DrawBulletDecalGate( void )
{
	__asm
	{
		PUSHAD;
	}

	g_Autowall.UpdateAutowall( );

	__asm
	{
		POPAD;
		JMP dwDrawBulletDecalRetn;
	}
}

LONG CALLBACK pVEH_Hook( PEXCEPTION_POINTERS pInfo )
{
	if( pInfo->ContextRecord->Eip == OFFS_ENDFRAME_EXCEPTION )
	{
		EO_Client.R_EndFrame();
		pInfo->ContextRecord->Eip = OFFS_ENDFRAME_CONTINUE;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if( pInfo->ContextRecord->Eip == OFFS_WRITEPACKET_EXECPTION )
	{
		EO_Client.CL_WritePacket();

		pInfo->ContextRecord->Ecx = OFFS_WRITEPACKET_CONTINUE;

		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if( pInfo->ContextRecord->Eip == 0x455A26 )
	{
		if ( *reinterpret_cast<PDWORD_PTR>( pInfo->ContextRecord->Esp ) != 0x4560FD )
		{
			dwDrawBulletDecalRetn = *reinterpret_cast<PDWORD_PTR>( pInfo->ContextRecord->Esp );

			dwEntNum = pInfo->ContextRecord->Eax;

			DWORD_PTR dwTracePosPointer = *reinterpret_cast<PDWORD_PTR>( pInfo->ContextRecord->Esp + 0x10 );

			vTraceEndPos[0] = *reinterpret_cast<PFLOAT>( dwTracePosPointer );
			vTraceEndPos[1] = *reinterpret_cast<PFLOAT>( dwTracePosPointer + 0x4 );
			vTraceEndPos[2] = *reinterpret_cast<PFLOAT>( dwTracePosPointer + 0x8 );

			*reinterpret_cast<PDWORD_PTR>( pInfo->ContextRecord->Esp ) = reinterpret_cast<DWORD_PTR>(&CG_DrawBulletDecalGate);
		}

		pInfo->ContextRecord->Eip = 0x455A7A;

		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

void dwMainThread( )
{
	Sleep( 2000 );

	AddVectoredExceptionHandler( TRUE,pVEH_Hook );

	while( TRUE )
	{
		*reinterpret_cast< PDWORD_PTR >( OFFS_ENDFRAME_DVAR ) = 0;
		*reinterpret_cast< PDWORD_PTR >( OFFS_WRITEPACKET_DVAR ) = 0;
		Sleep( 2000 );
	}
}

void InitThread( void )
{
	CreateThread( NULL, NULL, ( LPTHREAD_START_ROUTINE )dwMainThread, NULL, NULL, NULL );
}