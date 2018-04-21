#include "EO_Main.h"

EO_CClient EO_Client;

vec4_t				colWhite = { 1.0f, 1.0f, 1.0f, 1.0f };

bool Once = true;

typedef int(*__cdecl SendCmdToCon_0x51B8E0)(int, int, char*);
SendCmdToCon_0x51B8E0 SendCmd = (SendCmdToCon_0x51B8E0)0x51B8E0;

int LastHealth = 100;
int LastTeam = 0;

void FunFunctions()
{

	if (GetAsyncKeyState(VK_F1) & 1 || EO_Misc.TeamSwitch)
	{

		LastTeam = clientinfo[cg->ClientNum].Team;
		Aimbot.SwapTeams = !Aimbot.SwapTeams;
		EO_Misc.TeamSwitch = 0;

		if (clientinfo[cg->ClientNum].Team == 2)
		{
			char buff[30];
			sprintf(buff, "cmd mr %d 2 axis", MAGICNUMBER);
			SendCmd(0, 0, buff);
		}
		else
		{
			char buff[30];
			sprintf(buff, "cmd mr %d 2 allies", MAGICNUMBER);
			SendCmd(0, 0, buff);
		}
	}
	if (GetAsyncKeyState(VK_F2) & 1 || EO_Misc.Jugg)
	{
		char buff[30];
		sprintf(buff, "cmd mr %d 9 axis", MAGICNUMBER);
		SendCmd(0, 0, buff);
		EO_Misc.Jugg = 0;
	}
	static int LastClass = 0;
	if (GetAsyncKeyState(VK_F3) & 1 || EO_Misc.ForceClass != LastClass)
	{
		char buff[50];
		sprintf(buff, "cmd mr %d 9 custom%d", MAGICNUMBER,EO_Misc.ForceClass);
		SendCmd(0, 0, buff);
		LastClass = EO_Misc.ForceClass;
	}
	if (GetAsyncKeyState(VK_F4) & 1)
	{
		char Buff[100];
		sprintf(Buff, "cmd mr %d 2 changeteam", MAGICNUMBER);
		SendCmd(0, 0, Buff);
	}
	if (GetAsyncKeyState(VK_END) & 1)
	{
		char buff[50];
		sprintf(buff, "mr %d -1 endround", MAGICNUMBER);
		SendCmd(0, 0, buff);
	}
	if (GetAsyncKeyState(VK_F5) & 1)
	{
		Aimbot.SwapTeams = !Aimbot.SwapTeams;
	}
	if (GetAsyncKeyState(VK_F7) & 1)
		Aimbot.Silent = !Aimbot.Silent;
	if (GetAsyncKeyState(VK_F8) & 1)
		Aimbot.AntiAim = !Aimbot.AntiAim;
	if (GetAsyncKeyState(VK_F9) & 1)
		Aimbot.ViewTroll = !Aimbot.ViewTroll;
	if (GetAsyncKeyState(VK_F10) & 1)
		EO_Misc.fOptimizePerformance = !EO_Misc.fOptimizePerformance;
	if (GetAsyncKeyState(VK_F11) & 1)
		Aimbot.AimAtTeam = !Aimbot.AimAtTeam;
	if (GetAsyncKeyState(VK_F12) & 1)
		KillSpree.Active = !KillSpree.Active;
}
weapon_t Weap;

int nOldMaxFps = 0;
int nOldPacketdup = 0;
int nOldRate = 0;
int nOldMaxPackets = 0;
int nOldDetailMap = 0;
int nOldNormalMap = 0;
int nOldNormal = 0;
int nOldDetail = 0;
int nOldFog = 0;
int nOldFxDraw = 0;
int nOldFxEnable = 0;

int nOptimizationCount = 0;

typedef int (*__cdecl sub_510080)(int a1, int a2,char* a3, int a4, int a5, float a6);
sub_510080 TestSub = (sub_510080)0x510080;

void EO_CClient::R_EndFrame()
{

	if (Once)
	{
		EO_Draw.InitializeDrawing();
		((LRESULT(__cdecl*)())0x4A40B0)(); //Open DevConsole.
		Menu.Init(50,200);
		Once = false;
		KillSpree.LastKills = KillSpree.GetKills();
	}
	EO_Utils.SetDvarByName<int>("party_maxplayers",18);


	if (EO_Misc.fOptimizePerformance)
	{

		*(DWORD*)0x609BD7C = 4; //fullbright ON

		nOldMaxFps = EO_Utils.GetDvar<int>(0x1DCC004); //maxfps
		EO_Utils.SetDvar<int>(0x1DCC004, 120);

		nOldPacketdup = EO_Utils.GetDvarByName<int>("cl_packetdup"); //packetdup
		EO_Utils.SetDvarByName<int>("cl_packetdup", 5);

		nOldMaxPackets = EO_Utils.GetDvar<int>(0x113D974); //maxpackets
		EO_Utils.SetDvar<int>(0x113D974, 100);

		nOldRate = EO_Utils.GetDvarByName<int>("rate"); //rate
		EO_Utils.SetDvarByName<int>("rate", 25000);

		nOldDetail = EO_Utils.GetDvar<int>(0x609BFA4); //r_detail
		EO_Utils.SetDvar<int>(0x609BFA4, 0);

		nOldNormal = EO_Utils.GetDvar<int>(0x609C02C); //r_normal
		EO_Utils.SetDvar<int>(0x609C02C, 0);

		nOldDetailMap = EO_Utils.GetDvar<int>(0x609BE34); //r_detailMap
		EO_Utils.SetDvar<int>(0x609BE34, 0);

		nOldNormalMap = EO_Utils.GetDvar<int>(0x609C0BC); //r_normalmap
		EO_Utils.SetDvar<int>(0x609C0BC, 0);

		nOldFog = EO_Utils.GetDvar<int>(0x609C0FC); //r_fog
		EO_Utils.SetDvar<int>(0x609C0FC, 0);

		nOldFxEnable = EO_Utils.GetDvar<int>(0x197CAA4); //fx_enable
		EO_Utils.SetDvar<int>(0x197CAA4, 0);

		nOldFxDraw = EO_Utils.GetDvar<int>(0x197CB20); //fx_draw
		EO_Utils.SetDvar<int>(0x197CB20, 0);


		nOptimizationCount++;

	}
	else
	{

		if (nOptimizationCount > 0)
		{

			*(DWORD*)0x609BD7C = 9; //fullbright OFF

			EO_Utils.SetDvar<int>(0x1DCC004, nOldMaxFps); //maxfps

			EO_Utils.SetDvarByName<int>("cl_packetdup", nOldPacketdup); //packetdup

			EO_Utils.SetDvar<int>(0x113D974, nOldMaxPackets); //maxpackets

			EO_Utils.SetDvarByName<int>("rate", nOldRate); //rate

			EO_Utils.SetDvar<int>(0x609BFA4, nOldDetail); //r_detail

			EO_Utils.SetDvar<int>(0x609C02C, nOldNormal); //r_normal

			EO_Utils.SetDvar<int>(0x609BE34, nOldDetailMap); //r_detailMap

			EO_Utils.SetDvar<int>(0x609C0BC, nOldNormalMap); //r_normalMap

			EO_Utils.SetDvar<int>(0x609C0FC, nOldFog); //r_fog

			EO_Utils.SetDvar<int>(0x197CAA4, nOldFxEnable); //fx_enable

			EO_Utils.SetDvar<int>(0x197CB20, nOldFxDraw); //fx_draw
	

		}

	}
	if(EO_Misc.HostAutowall)
		EO_Utils.SetDvar<float>(0x9BABC0,999.f);
	if(EO_Misc.ForceHost)
		EO_Utils.SetDvarByName<int>("party_minplayers",0);

	if (cg_entities[cg->ClientNum].isAlive & 1)
	{

		//! Once block über isAlive check.
		Menu.DrawIt();
		KillSpree.Update();

		viewmatrix->Recoil[0] = 0;
		viewmatrix->Recoil[1] = 0;
		viewmatrix->Recoil[2] = 0;


		EO_Draw.DrawString(10, 15, consoleFont, 1.0, colWhite, "EngineOwning - Call of Duty: 8");

		EO_Draw.DrawString(10, 30, consoleFont, 1, WHITE, "^1F1 ^7Team change ^1F2^7 Jugg ^1F3 ^7custom class (5) ^1F4 ^7Change team ^1F5 ^7Swap teams aimbot ^1F6 ^7shoot mode ^1F7 ^7Silent aim ^1F8 ^7Anti aim ^1F9 ^7View troller ^1F10 ^7Rage DVARS ^1F11 ^7AimAtTeam ^1END ^7endround F12 Dis killsounds");
		

		EO_Draw.DrawString(10, 45, consoleFont, 1, WHITE, Aimbot.AntiAim ? "Anti Aim ^2ON" : "Anti Aim ^1OFF");
		EO_Draw.DrawString(10, 60, consoleFont, 1, WHITE, Aimbot.ViewTroll ? "View troller ^2ON" : "View Troller ^1OFF");
		EO_Draw.DrawString(10, 75, consoleFont, 1, WHITE, Aimbot.Silent ? "Silent Aim ^2ON" : "Silent Aim ^1OFF");
		EO_Draw.DrawString(10, 90, consoleFont, 1, WHITE, EO_Misc.fOptimizePerformance ? "Optimize Rage Performance ^2ON" : "Optimize Rage Performance ^1OFF");
		EO_Draw.DrawStringf(10, 105, consoleFont, 1, WHITE, "AimAtTeam %s", Aimbot.AimAtTeam ? "^2ON" : "^1OFF");

		EO_Draw.DrawStringf(10, 130, consoleFont, 1, WHITE, "Teamnum: %i", clientinfo[cg->ClientNum].Team);
		EO_Draw.DrawStringf(10, 145, consoleFont, 1, WHITE, "MatchID: %d", MAGICNUMBER);
		EO_Draw.DrawStringf(10, 160, consoleFont, 1, WHITE, "Test: %d", int((*(byte*)0x8780B0)));
		EO_Draw.DrawStringf(10, 175, consoleFont, 1, WHITE, "Ping: %d",OFF_PING);


		float cX, cY;
		cX = refdef->x / 2;
		cY = refdef->y / 2;
		EO_Draw.DrawRect(cX - 1, cY - (10) - 1, 3, 20 + 2, 1, colWhite);
		EO_Draw.DrawRect(cX - (10) - 1, cY - 1, 20 + 2, 3, 1, colWhite);
		
		ESP.ESP();
		
		

		Aimbot.InitializeAimbot();
		FunFunctions();
		

	}
}

extern void FixSpread();
//comment

int curRot = 0;
void AntiAim(usercmd_t* curCmd)
{

	if(*(int*)0xA535F4 == 1) // IsInKillcam
		return;

	if (Aimbot.AntiAim == 1)
	{
		
		curCmd->viewangles[0] = ANGLE2SHORT((rand() % 2) ? -(RandomNumberGenerator.randInt(0,85)) : RandomNumberGenerator.randInt(0,85));
		curCmd->viewangles[1] = ANGLE2SHORT(RandomNumberGenerator.randInt(0,720));
	}
	else if(Aimbot.AntiAim > 1)
	{
		if(Aimbot.RiotTarget == -1 && Aimbot.BestTarget == -1)
		{

		}
		else
		{
			int target;
			if(Aimbot.RiotTarget != -1)
				target = Aimbot.RiotTarget;
			else if(Aimbot.BestTarget != -1)
				target = Aimbot.BestTarget;
			vec3_t EnemyMiddl;
			float AngleToEn[2];
		
			EO_Utils.GetPlayerTag(*(WORD*)0x1D695EC,&cg_entities[target],EnemyMiddl);
			EO_Utils.GetAngleToOrigin(EnemyMiddl,AngleToEn[0],AngleToEn[1]);

			AngleToEn[0] -= 180;
	
			float* WeapAngles = (float*)0xA534EC;

			curCmd->viewangles[1] += ANGLE2SHORT(AngleToEn[0]);
			curCmd->viewangles[0] += ANGLE2SHORT(AngleToEn[1]);
			if(Aimbot.AntiAim == 3)
			{
				//Do crouch
			}
		}

	}

	if (Aimbot.ViewTroll == 1)
		curCmd->viewangles[2] = ANGLE2SHORT(RandomNumberGenerator.randInt(0,360));
	else if(Aimbot.ViewTroll == 2)
	{
		if(curRot > 999999999)
			curRot = 0;
		curCmd->viewangles[2] = curRot;
		curRot += 500;
	}
}

int nLastTimeShot = 0;

void EO_CClient::CL_WritePacket()
{


	if (cg_entities[cg->ClientNum].isAlive & 1)
	{

		int *cl_cmdNumber = (int *)0x1142690;
		usercmd_t *cl_cmds = (usercmd_t*)0x1141090;
		int newCmdNum = *cl_cmdNumber & 0x7F;
		usercmd_t *newCmd = &cl_cmds[newCmdNum];
		(*cl_cmdNumber)++;
		int cmdNum = *cl_cmdNumber & 0x7F;
		usercmd_t *oldCmd = &cl_cmds[cmdNum];
		*oldCmd = *newCmd;
		newCmd->servertime -= 1;

		AntiAim(oldCmd);
		int nWeapShootDelay = EO_Utils.GetWeapon(R_GetCurrentWeapon(cg)).iWeaponFireDelay;
		if( Aimbot.BestTarget != -1 && Aimbot.Autoshoot != 0 )
		{
			newCmd->buttons |= IN_ATTACK;
			if (Aimbot.Autoshoot == 1 && (nLastTimeShot == 0 || GetTickCount() - nLastTimeShot > nWeapShootDelay) && (*(byte*)0x009DC5E1 == 0))
            {
			
                ((void(__cdecl*)(int, centity_t* pent, int nEID, char bUnc))0x546D10)(0, &cg_entities[cg->ClientNum], 42, 1);
                ((void(__cdecl*)(int, centity_t* pent, int nEID, char bUnc))0x546D10)(0, &cg_entities[cg->ClientNum], 30, 1);

                nLastTimeShot = GetTickCount();
            }
		}
		
		

		if (*(float*)0x9DC718 == 1.0)
			return;

		gNoSpread.ApplySpread(newCmd);
	}
}