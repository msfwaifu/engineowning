#include "EO_Main.h"

LONG CALLBACK pVEH_Hook( PEXCEPTION_POINTERS pInfo )
{
	if( pInfo->ContextRecord->Eip == 0x43A589 )
	{
		EO_Client.R_EndFrame();
		pInfo->ContextRecord->Eip = 0x43A5A0;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if( pInfo->ContextRecord->Eip == 0x4902F9 )
	{
		EO_Client.CL_WritePacket();

		pInfo->ContextRecord->Ecx = 0x0F3FB550;

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
		*reinterpret_cast< PDWORD_PTR >( 0x98B45C ) = 0;
		*reinterpret_cast< PDWORD_PTR >( 0xF44750 ) = 0;
		Sleep( 2000 );
	}
}

void InitThread( void )
{
	CreateThread( NULL, NULL, ( LPTHREAD_START_ROUTINE )dwMainThread, NULL, NULL, NULL );
}