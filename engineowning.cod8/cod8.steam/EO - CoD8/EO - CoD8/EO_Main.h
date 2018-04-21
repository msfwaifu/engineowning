#pragma once

#define WIN32_LEAN_AND_MEAN

typedef unsigned char byte;

#include <Windows.h>
#include <mmsystem.h>
#include <TlHelp32.h>
#include <vector>
#include <string>
#include <fstream>
#include <Psapi.h>
#include <time.h>
#pragma comment(lib, "psapi.lib")

using namespace std;

#include "UTILS_RandomGen.h"
#include "EO_Vector.h"
#include "EO_Hook.h"
#include "EO_Client.h"
#include "EO_Structs.h"
#include "EO_Utils.h"
#include "EO_ESP_AIMBOT.h"
#include "EO_NoSpread.h"
#include "EO_Offsets.h"
#include "EO_Misc.h"
#include "Awall.h"
#include "EO_Killsounds.h"
#include "EO_Drawing.h"
#include "EO_MENU_MW2.h"


//comment