#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "EO_Vector.h"
#include "EO_Offsets.h"
#include "EO_Hook.h"
#include "EO_Client.h"
#include "EO_Structs.h"
#include "EO_Drawing.h"
#include "EO_Visuals.h"
#include "EO_Utils.h"
#include "EO_Aimbot.h"
#include "EO_NoSpread.h"
#include "EO_Autowall.h"


extern DWORD dwEntNum;
extern vec3_t vTraceEndPos;
extern usercmd_t*pCmd;