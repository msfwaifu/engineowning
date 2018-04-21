#include "EO_Main.h"

BOOL WINAPI DllMain( HINSTANCE hInstDLL,DWORD dwReason,LPVOID lpReserved )
{
	if( dwReason==DLL_PROCESS_ATTACH )
	{
		InitThread( );
		return TRUE;
	}
	return FALSE;
}