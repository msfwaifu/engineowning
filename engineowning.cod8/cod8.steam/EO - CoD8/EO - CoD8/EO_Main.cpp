#include "EO_Main.h"

//comment
BOOL WINAPI DllMain( HINSTANCE hInstDLL,DWORD dwReason,LPVOID lpReserved )
{
	if( dwReason==DLL_PROCESS_ATTACH )
	{
		Menu.ModuleBase = hInstDLL;
		InitThread( );
		return TRUE;
	}
	return FALSE;
}