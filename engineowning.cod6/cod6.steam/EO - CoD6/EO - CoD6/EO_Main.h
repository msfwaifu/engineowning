#include <Windows.h>
#include <stdio.h>
#include <cstdio>
#include <math.h>


typedef float Vector[3];

#define ANGLE2SHORT(x)((int)((x)*65536/360) & 65535)

#define MSG(a) MessageBoxA(NULL,a,a,MB_OK);


#include "EO_Friend.h"
#include "EO_Structs.h"
#include "EO_Drawing.h"
#include "EO_Engine.h"
#include "EO_Math.h"
#include "EO_ESP.h"
#include "EO_Aimbot.h"