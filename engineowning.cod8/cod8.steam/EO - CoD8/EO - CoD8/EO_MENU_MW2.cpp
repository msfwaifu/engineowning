
#include "EO_Main.h"


//das menu brauch man definitiv
//nicht mehr obfuscaten :P

int PlaceHolder;


cMenu Menu;

void cMenu::InitOptions()
{
	//NOTE: FIRST YOU NEED TO INITIALIZE THE TABS THEN THE SUBS AND FINALLY THE OPTIONS! ELSE IT WILL PROBABLY CRASH!

	//TABS INIT--------------------------
	AddTab("[Hack]");

	AddTab("[Config & Menu]");
	//------------------------------------

	AddSub(0,"Aimbot");
	AddSub(0,"ESP");
	AddSub(0,"Misc");
	AddSub(0,"PlayerList");

	AddSub(1,"Load configs");
	AddSub(1,"Save configs");
	AddSub(1,"Menu");

	AddOption(0,0,"Aimbot",0,1,&Aimbot.AimbotOn);

	Aimbot.Autoshoot = 1;
	AddOption(0,0,"Autoshoot",0,2,&Aimbot.Autoshoot,"OFF","Normal","Silent");
	AddOption(0,0,"Swap Teams",0,1,&Aimbot.SwapTeams);
	AddOption(0,0,"Aim at team",0,1,&Aimbot.AimAtTeam);
	AddOption(0,0,"Prediction",0,1,&Aimbot.Prediction);

	AddOption(0,1,"ESP",0,1,&ESP.ESPOn);
	AddOption(0, 1, "Enemy ESP", 0, 1, &ESP.EnemyEsp);
	AddOption(0, 1, "Team ESP", 0, 1, &ESP.TeamEsp);
	AddOption(0, 1, "Box ESP", 0, 3, &ESP.BoxEsp, "OFF", "Bordered Only", "Filled Only", "Both");
	AddOption(0, 1, "Name ESP", 0, 1, &ESP.NameEsp);
	AddOption(0, 1, "Weapon ESP", 0, 2, &ESP.WeaponEsp, "OFF", "Icon", "Text");
	AddOption(0, 1, "SnapLines", 0, 3, &ESP.SnapLinesMode, "OFF", "Center Bottom", "Crosshair", "Center Top");

	AddOption(0,2,"Spawn as jugg",0,1,&EO_Misc.Jugg);
	AddOption(0,2,"Team switch",0,1,&EO_Misc.TeamSwitch);
	AddOption(0,2,"Force class",0,15,&EO_Misc.ForceClass);
	AddOption(0,2,"Anti Aim",0,2,&Aimbot.AntiAim,"OFF","Normal","Riot","Riot & Crouch");
	AddOption(0,2,"View Troller",0,2,&Aimbot.ViewTroll,"OFF","Random","Rotating");
	AddOption(0,2,"Rage DVARs",0,1,&EO_Misc.fOptimizePerformance);
	AddOption(0,2,"KillFeed",0,3,&KillSpree.Active,"OFF","Sound & Icon","Sound","Icon");
	AddOption(0,2,"KillFeed Origin",0,8,&KillSpree.Origin,"Center","Top Left","Top Center","Top Right","Left","Right","Bottom Left","Bottom Center","Bottom Right");
	AddOption(0,2,"KillFeed Destination ",0,3,&KillSpree.Destination,"Left","Top","Right","Bottom");
	AddOption(0,2,"KillFeed Size",0,2,&KillSpree.Size,"Small","Normal","Big");
	AddOption(0,2,"KillFeed Count",1,10,&KillSpree.NumOfSymbols);
	AddOption(0,2,"KillFeed Rotate",0,1,&KillSpree.Rotating);
	AddOption(0,2,"KillFeed Icon",0,2,&KillSpree.Icon,"HeadShot","Skull","Random","TEST");
	AddOption(0,2,"Host autowall",0,1,&EO_Misc.HostAutowall);
	AddOption(0,2,"Force Host",0,1,&EO_Misc.ForceHost);

	for( int i = 0; i < 6; i++)
		SaveCon[i] = 0;
	for( int i = 0; i < 6; i++)
		LoadCon[i] = 0;

	AddOption(1,0,"Load config #1",0,1,&LoadCon[0]);
	AddOption(1,0,"Load config #2",0,1,&LoadCon[1]);
	AddOption(1,0,"Load config #3",0,1,&LoadCon[2]);
	AddOption(1,0,"Load config #4",0,1,&LoadCon[3]);
	AddOption(1,0,"Load config #5",0,1,&LoadCon[4]);
	AddOption(1,0,"Load config #6",0,1,&LoadCon[5]);

	AddOption(1,1,"Save config #1",0,1,&SaveCon[0]);
	AddOption(1,1,"Save config #2",0,1,&SaveCon[1]);
	AddOption(1,1,"Save config #3",0,1,&SaveCon[2]);
	AddOption(1,1,"Save config #4",0,1,&SaveCon[3]);
	AddOption(1,1,"Save config #5",0,1,&SaveCon[4]);
	AddOption(1,1,"Save config #6",0,1,&SaveCon[5]);


	AddOption(1,2,"NOTHING",1,0,&PlaceHolder);
	for(int i = 0; i < 18; i++)
		AddOption(0,3,"NO PLAYER",0,3,&Aimbot.PlayerList[i],"Normal","Prefer","True Enemy","Ignore","","","","","","");



	//MUSS ANGEPASST WERDEN WENN DAS MODUL GEMAPPED WIRD!!!!
	char TempPath[260];
	
	GetModuleFileNameA((HMODULE)ModuleBase,TempPath,260);
	std::string TempStr(TempPath);
	TempStr = TempStr.substr(0,TempStr.find_last_of('\\'));
	strcpy(Path,TempStr.c_str());
	//------------------------------------------------------
	
	




	ReadConfig(CONFIG_NAME);

	EO_Misc.HostAutowall = 0;
	EO_Misc.ForceHost = 0;

}


//am besten gar nicht weiterscrollen
//es funktioniert eh alles



void cMenu :: DrawMenuMessage(float x,float y,FONT_T font,Color COL,char* msg)
{

	EO_Draw.DrawString(x,y,font,1,COL,msg);

	

	//execute your engine drawtext func here...
}
	
void cMenu :: DrawMenuRect(float X,float Y,float width,float height,Color col,bool adjust)
{
	if(adjust)
		SCR_AdjustFrom640(&X,&Y,&width,&height);

	EO_Draw.DrawShader(X,Y,width,height,col,sWhite);

	//execute your shape drawing func here...
}

void cMenu :: DrawRotated(float X,float Y,float width,float height,float ANGLE,Color col,bool adjust)
{
	if(adjust)
	{
		//SCR_AdjustFrom640(&X,&Y,&width,&height);
	}

	DrawRotatedShader(GSM(),X,Y,width,height,ANGLE,col,sWhite);
	//execute your shape drawing func here...
}
void cMenu::DrawBox ( float x, float y, float w, float h, float Size,float* color,bool adjust ) {

	DrawMenuRect(x,y,Size,h,color,adjust);
	DrawMenuRect(x,y,w,Size,color,adjust);
	DrawMenuRect(x,y+h,w,Size,color,adjust);
	DrawMenuRect(x+w,y,Size,h+Size,color,adjust);
}
void cMenu::DrawRectBorder(float X,float Y,float width,float height,float Size,Color colBG,Color colBOX,bool adjust)
{
	if(adjust)
		SCR_AdjustFrom640(&X,&Y,&width,&height);

	DrawMenuRect(X,Y,width,height,colBG,false);
	DrawBox(X,Y,width,height,Size,colBOX,false);
}


void cMenu::DrawLine(float x1,float y1,float x2,float y2,float Size,Color col,bool adjust)
{
	float x, y, angle, l1, l2, h1;
  


	h1 = y2 - y1;
	l1 = x2 - x1;
	l2 = sqrt ( l1 * l1 + h1 * h1 );
	x = x1 + ( ( l1 - l2 ) / 2 );
	y = y1 + ( h1 / 2 );
	angle = ( float ) atan ( h1 / l1 ) * ( 180 / 3.14159265358979323846 ) ;


	DrawRotated ( x, y, l2, Size, angle, col, adjust );
	
}


void DrawBackGroundLayer()
{

}
void DrawTextLayer()
{

}
char TabDrawBuff[600];

//#define MENU_DEBUG
//#define DEBUG_VALS


bool UpdateDVAR = true;

void cMenu::DrawIt()
{
	GetKeys();
#ifdef MOUSE_CONTROL
	if(MenuActive)
	{
		//*(int*)OFF_BYPASSMOUSE1 = 1;
		//*(int*)OFF_BYPASSMOUSE2 = 1;

		if(UpdateDVAR)
		{
			EO_Utils.SetDvarByName<int>("cl_bypassmouseinput",1);
			UpdateDVAR = false;
		}

		if(Menu.MouseControlled)
			*(BYTE*)0x004D7CB5 = 0;		

	}
	else
	{
		//*(int*)OFF_BYPASSMOUSE1 = 0;
		//*(int*)OFF_BYPASSMOUSE2 = 0;

		if(!UpdateDVAR)
		{
			Engine.SendCmdToConsole(0,0,"cl_bypassmouseinput 0");
			UpdateDVAR = true;
		}

		*(BYTE*)0x004D7CB5 = 1;
		return;
	}
#endif

#ifdef MENU_DEBUG
	for(int i = 0; i < NumOfTabs;i++)
	{
		DrawMenuMessage(50+i*300,50,Engine.NormalFont,RED,TabPtr[i].Name);
		
		
		for(int j = 0; j < TabPtr[i].NumOfSubs;j++)
		{
			DrawMenuMessage(50+i*300,100+j*200,Engine.NormalFont,GREEN,TabPtr[i].SubMenuPTR[j].Name);

			for(int k = 0; k < TabPtr[i].SubMenuPTR[j].NumOfOpt;k++)
			{
				DrawMenuMessage(200+i*300,100+j*200+k*20,Engine.NormalFont,WHITE,TabPtr[i].SubMenuPTR[j].OptStructPtr[k].Name);
			}
		}
	}
	return;
#endif

#ifdef DEBUG_VALS
	char buffer[500];
	sprintf(buffer,"Tab: %d\n Sub: %d\n Option: %d\nNumOfTabs: %d\n NumOfSubs: %d\nNumOfOpts: %d",CurTab,TabPtr[CurTab].Cursub,TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].CurOpt,NumOfTabs,TabPtr[CurTab].NumOfSubs,TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt);
	DrawMenuMessage(200,600,normalFont,RED,buffer);
#endif 
	if(!MenuActive)
		return;

	for(int i = 0; i < 6; i++)
	{
		if(SaveCon[i] == 1)
		{
			SaveCon[i] = 0;
			char buffer[100];
			sprintf(buffer,"config%d.eoconfig",i+1);
			CreateConfig(buffer);
		}
		if(LoadCon[i] == 1)
		{
			LoadCon[i] = 0;
			char buffer[100];
			sprintf(buffer,"config%d.eoconfig",i+1);
			ReadConfig(buffer);
		}
	}
	if(MenuStyle == 0)
	{

		DrawRectBorder(PosX,PosY,500,40,2,MENUBG,WHITE,false); //TAB ANZEIGE

		if(TabPtr[CurTab].Cursub == -1)
		{
			DrawRectBorder(PosX,PosY+40,200,5+TabPtr[CurTab].NumOfSubs*30,2,MENUBG,WHITE,false); //SUBMENU ANZEIGE

			DrawRectBorder(PosX+200,PosY+40,300,5+TabPtr[CurTab].NumOfSubs*30,2,MENUBG,WHITE,false); //OPTION BG
		}
		else if(TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt < TabPtr[CurTab].NumOfSubs)
		{
			DrawRectBorder(PosX,PosY+40,200,5+TabPtr[CurTab].NumOfSubs*30,2,MENUBG,WHITE,false); //SUBMENU ANZEIGE

			DrawRectBorder(PosX+200,PosY+40,300,5+TabPtr[CurTab].NumOfSubs*30,2,MENUBG,WHITE,false); //OPTION BG
		}
		else
		{
			DrawRectBorder(PosX,PosY+40,200,5+TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt*30,2,MENUBG,WHITE,false); //SUBMENU ANZEIGE

			DrawRectBorder(PosX+200,PosY+40,300,5+TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt*30,2,MENUBG,WHITE,false); //OPTION BG
		}

		DrawRectBorder(PosX + CurTab*150,PosY,150,40,2,CURSORCOLOR,WHITE,false); //TAB CURSOR
		DrawRectBorder(PosX,PosY + 40 + TabPtr[CurTab].CurSubSelected*30,200,30,2,CURSORCOLOR,WHITE,false); //SUB CURSOR
		DrawRectBorder(PosX + 200,PosY + 40 + TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].CurOpt*30,300,30,2,CURSORCOLOR,WHITE,false); //OPTION CURSOR

		DrawBackGroundLayer();

		for(int i = 0; i < NumOfTabs; i++)
		{
			DrawMenuMessage(PosX + 5 + i*150,PosY+35,smallFont,FONTCOLOR,TabPtr[i].Name); //TAB NAMES
		}
		for(int i = 0; i < TabPtr[CurTab].NumOfSubs;i++)
		{
			DrawMenuMessage(PosX+5,PosY + 40 + 30 + i*30,smallFont,FONTCOLOR,TabPtr[CurTab].SubMenuPTR[i].Name); //SUB NAMES
		}
		for(int i = 0; i < TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt; i++) //OPTION NAMES + VALUES
		{
			if(TabPtr[CurTab].Cursub == -1)
				break;
			DrawMenuMessage(PosX+205,PosY+ 40 + 30 + i*30,smallFont,FONTCOLOR,TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].OptStructPtr[i].Name);
	
			if(TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[i].MaxVal == 0 && TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[i].MinVal == 0)
				continue;
			if(TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[i].UseString)
			{
				DrawMenuMessage(PosX+400,PosY + 40 + 30 + i*30,smallFont,FONTCOLOR,TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[i].OptNames[*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[i].CurVal]);
			}
			else if(TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[i].MaxVal == 1 && TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[i].MinVal == 0)
			{
				if(*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[i].CurVal == 1)
					DrawMenuMessage(PosX+400,PosY + 40 + 30 + i*30,smallFont,FONTCOLOR,"^2ON");
				else 
					DrawMenuMessage(PosX+400,PosY + 40 + 30 + i*30,smallFont,FONTCOLOR,"^1OFF");
			}
			else
			{
				char VBuff[20];
				sprintf(VBuff,"^1%d",*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].OptStructPtr[i].CurVal);
				DrawMenuMessage(PosX+400,PosY + 40 + 30 + i*30,smallFont,FONTCOLOR,VBuff);
			}
		}
	
	}
#ifdef MOUSE_CONTROL
	if(MenuActive)
		Engine.DrawShaderRotated(*(long*)0x0649D644 - 25,*(long*)0x0649D648,50,50,1,1,0,WHITE,Draw.RadarFriend);
#endif
}

void cMenu :: SCR_AdjustFrom640( float *x, float *y, float *w, float *h ) {
	float	xscale;
	float	yscale;

#if 0
		// adjust for wide screens
		if ( cls.glconfig.vidWidth * 480 > cls.glconfig.vidHeight * 640 ) {
			*x += 0.5 * ( cls.glconfig.vidWidth - ( cls.glconfig.vidHeight * 640 / 480 ) );
		}
#endif

	// scale for screen sizes
		xscale = Width / 640.0;
		yscale = Height / 480.0;
	if ( x ) {
		*x *= xscale;
	}
	if ( y ) {
		*y *= yscale;
	}
	if ( w ) {
		*w *= xscale;
	}
	if ( h ) {
		*h *= yscale;
	}
}
float StringWidth(char* text,float scaleX,float scaleY,FONT_T font)
{
	//ANPASSEN
	return 0;
	//return Engine.StrWidth(text,scaleX,font,scaleY);
}


void showmsg(char* what)
{
	MessageBoxA(NULL,what,what,MB_OK);
}
void showmsg(int what)
{
	char buffer[100];
	sprintf(buffer,"%d",what);
	showmsg(buffer);
}
void showmsg(float what)
{
	char buffer[100];
	sprintf(buffer,"%f",what);
	showmsg(buffer);
}
void cMenu::CpyColor(float* Color1,float *Color2)
{
	Color1[0] = Color2[0];
	Color1[1] = Color2[1];
	Color1[2] = Color2[2];
	Color1[3] = Color2[3];
}
bool IsMouseInRegion(int X,int Y,int width,int height)
{

	return ( *(long*)0x0649D644 > X && *(long*)0x0649D644 < X + width && *(long*)0x0649D648 > Y && *(long*)0x0649D648 < Y + height);
}

void cMenu :: MouseControlSub()
{
	SHORT lbutton = GetAsyncKeyState(VK_LBUTTON);
	SHORT rButton = GetAsyncKeyState(VK_RBUTTON);
	if(MenuStyle == 0)
	{
		if(IsMouseInRegion(PosX,PosY-40,250,40))
		{
			if(lbutton & 1)
			{
				if(CurTab > 0)
					CurTab -= 1;
			}
			else if(rButton & 1 )
			{
				if(CurTab < NumOfTabs - 1)
					CurTab += 1;
			}
		}
		for(int i = 0; i < TabPtr[CurTab].NumOfSubs;i++)
		{
			if(IsMouseInRegion( PosX,PosY + i*30,250,30))
			{
				//TabPtr[CurTab].CurSubSelected = i;
				if(lbutton & 1 || rButton & 1)
				{
					TabPtr[CurTab].CurSubSelected = i;
					TabPtr[CurTab].Cursub = i;
				}
			}
		}
		if(TabPtr[CurTab].Cursub != -1)
		{
			for(int i = 0; i < TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt; i++)
			{
				if(IsMouseInRegion(PosX+250,PosY + i*30,350,30))
				{
					TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].CurOpt = i;
					if(lbutton & 1)
					{
						if(i == TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt - 1)
						{
							TabPtr[CurTab].Cursub = -1;
							return;
						}

						if(*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal > TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].MinVal)
							*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal -= 1;
					}
					else if(rButton & 1)
					{
						if(i == TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt - 1)
						{
							TabPtr[CurTab].Cursub = -1;
							return;
						}
						if(*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal < TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].MaxVal)
							*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal += 1;
					}
				}
			}
		}
	}
	else if(MenuStyle == 1)
	{
		for( int i = 0; i < NumOfTabs; i++)
		{
			if(IsMouseInRegion( PosX + i*150,PosY,150,40 ))
			{
				if(lbutton & 1)
					CurTab = i;
			}
		}
		for(int i = 0; i <TabPtr[CurTab].NumOfSubs;i++)
		{
			if(IsMouseInRegion( PosX,PosY + 40 + i*30,200,30))
			{
				if(lbutton & 1)
				{
					TabPtr[CurTab].Cursub = i;
					TabPtr[CurTab].CurSubSelected = i;
				}
			}
		}
		if(TabPtr[CurTab].Cursub != -1)
		{
			for(int i = 0; i < TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt;i++)
			{
				
				if(IsMouseInRegion(PosX + 200,PosY + 40 + i*30,300,30))
				{
					TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].CurOpt = i;
					if(lbutton & 1)
					{
						if(i == TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt - 1)
						{
							TabPtr[CurTab].Cursub = -1;
							return;
						}

						if(*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal > TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].MinVal)
							*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal -= 1;
					}
					else if(rButton & 1)
					{
						if(i == TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt - 1)
						{
							TabPtr[CurTab].Cursub = -1;
							return;
						}
						if(*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal < TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].MaxVal)
							*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal += 1;
					}
				}
			}
		}

	}
}

void cMenu::GetKeys()
{
	if(MenuActive)
	{
		if(Menu.MouseControlled)
			MouseControlSub();

	if(GetAsyncKeyState(VK_NUMPAD1) & 1)
	{
		/*CurTab -= 1;
		if(CurTab < 0)
			CurTab = NumOfTabs-1;*/
		CurTab = 0;
	}
	else if(GetAsyncKeyState(VK_NUMPAD2) & 1)
	{
		/*CurTab += 1;
		if(CurTab > NumOfTabs-1)
			CurTab = 0;*/
		CurTab = 1;
	}
	else if(GetAsyncKeyState(VK_NUMPAD3) & 1)
		CurTab = 2;
	if(GetAsyncKeyState(VK_UP) & 1)
	{
		if(TabPtr[CurTab].Cursub == -1)
		{
			TabPtr[CurTab].CurSubSelected -= 1;
			if(TabPtr[CurTab].CurSubSelected < 0)
				TabPtr[CurTab].CurSubSelected = TabPtr[CurTab].NumOfSubs-1;
		}
		else
		{
			TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt -= 1;
			if(TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt < 0)
				TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt = TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].NumOfOpt-1;
		}
	}
	if(GetAsyncKeyState(VK_DOWN) & 1)
	{
		if(TabPtr[CurTab].Cursub == -1)
		{
			TabPtr[CurTab].CurSubSelected += 1;
			if(TabPtr[CurTab].CurSubSelected > TabPtr[CurTab].NumOfSubs-1)
				TabPtr[CurTab].CurSubSelected = 0;
		}
		else
		{
			TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt += 1;
			if(TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt > TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].NumOfOpt-1)
				TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt = 0;
		}
	}
	if(GetAsyncKeyState(VK_LEFT) & 1)
	{
		if(TabPtr[CurTab].Cursub == -1)
		{
			TabPtr[CurTab].Cursub = TabPtr[CurTab].CurSubSelected;
		}
		else
		{
			if(TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt-1 == TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].CurOpt)
				TabPtr[CurTab].Cursub = -1;
			*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal -= 1;
			if(*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal < TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].MinVal)
				*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal = TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].MaxVal;
		}
	}
	if(GetAsyncKeyState(VK_RIGHT) & 1)
	{
		if(TabPtr[CurTab].Cursub == -1)
		{
			TabPtr[CurTab].Cursub = TabPtr[CurTab].CurSubSelected;
		}
		else
		{
			if(TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].NumOfOpt-1 == TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].Cursub].CurOpt)
				TabPtr[CurTab].Cursub = -1;

			*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal += 1;
			if(*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal > TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].MaxVal)
				*TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].CurVal = TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].OptStructPtr[TabPtr[CurTab].SubMenuPTR[TabPtr[CurTab].CurSubSelected].CurOpt].MinVal;
		}
	}
	}
	if(GetAsyncKeyState(VK_NUMPAD0) & 1)
	{
		MenuActive = !MenuActive;
	}
}


//void cOption::Init(char* nName,int min,int max,int* OutVPTR)
//{
//		Valid = true;
//		UseString = false;
//		Name = nName;
//		MinVal = min;
//		MaxVal = max;
//		CurVal = OutVPTR;
//		OptNames[0] = EMPTY;
//		OptNames[1] = EMPTY;
//		OptNames[2] = EMPTY;
//		OptNames[3] = EMPTY;
//		OptNames[4] = EMPTY;
//		OptNames[5] = EMPTY;
//		OptNames[6] = EMPTY;
//		OptNames[7] = EMPTY;
//		OptNames[8] = EMPTY;
//		OptNames[9] = EMPTY;
//		TextSize = StringWidth(Name,1,1,Engine.NormalFont); //ANPASSEN
//}
//void cOption::Init(char* nName,int min,int max,int* OutVPTR,char* OptName1,char* OptName2,char* OptName3,char* OptName4,char* OptName5,char* OptName6,char* OptName7,char* OptName8,char* OptName9,char* OptName10)
//{
//		Valid = true;
//		UseString = true;
//		Name = nName;
//		MinVal = min;
//		MaxVal = max;
//		CurVal = OutVPTR;
//		OptNames[0] = OptName1;
//		OptNames[1] = OptName2;
//		OptNames[2] = OptName3;
//		OptNames[3] = OptName4;
//		OptNames[4] = OptName5;
//		OptNames[5] = OptName6;
//		OptNames[6] = OptName7;
//		OptNames[7] = OptName8;
//		OptNames[8] = OptName9;
//		OptNames[9] = OptName10;
//
//		TextSize = StringWidth(Name,1,1,Engine.NormalFont); //ANPASSEN
//}
//void cSubMenu::Init(char* name)
//{
//		Name = name;
//		CurOpt = 0;
//		NumOfOpt = 0;
//		TextSize = StringWidth(Name,1,1,Engine.NormalFont); //ANPASSEN
//
//}
//void cTab::Init(char* name)
//{
//		Name = name;
//		Cursub = 0;
//		NumOfSubs = 0;
//		TextSize = StringWidth(Name,1,1,Engine.NormalFont); //ANPASSEN
//}

void cMenu::GameOUTALL(char* text)
{
	/*Engine.GameOUT(INFO_INGAME,text);
	Engine.GameOUT(INFO_INGAME_CONSOLE,text);
	Engine.GameOUT(INFO_WINDOW,text);
	Engine.GameOUT(INFO_CENTER,text);*/
}
bool cMenu::StringCmp(char* a1,char* a2)
{
	int length = strlen(a1);
	if(length != strlen(a2))
		return false;

	for(int i = 0; i < length; i++)
	{
		if(a1[i] != a2[i])
			return false;
	}
	return true;
}
bool cMenu::StringCmp2(char* a1,char* a2)
{
	int length = strlen(a1);
	for(int i = 0; i < length; i++)
	{
		if(a1[i] != a2[i])
			return false;
	}
	return true;
}
bool cMenu::fileExist (char* name) {
    if (FILE *file = fopen(name, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

int cMenu::GetCmd(char* filename,char* cmdname)
{
	std::ifstream file(filename);
    std::string str; 

	size_t strlenght = strlen(cmdname);

	while (std::getline(file, str))
    {

		if(strcmp(str.substr(0,2).c_str(),"//") == 0)
			continue;
		string compare=str.substr(0,strlenght).c_str();

		

		if(strcmp(compare.c_str(),cmdname) == 0)
		{
			string test=str.substr(strlenght+1,str.length());
			file.close();
			return atoi(test.c_str());
		}
		
	}
	file.close();
	return -1337;
}

void cMenu::ReadConfig(char* conname)
{
	GameOUTALL("Reading config...\n");
	char name[300];
	
	sprintf(name,"%s\\%s",Path,conname); //anpassen
	//sprintf(name,"%s",conname);

	if(!fileExist(name))
	{
		GameOUTALL("CONFIG NOT FOUND!");
		return;
	}
	for(int tab = 0; tab < NumOfTabs; tab++)
	{
		for(int Sub = 0; Sub < TabPtr[tab].NumOfSubs;Sub++)
		{
			for(int Opt = 0; Opt < TabPtr[tab].SubMenuPTR[Sub].NumOfOpt; Opt++)
			{
				int cmdVal = GetCmd(name,TabPtr[tab].SubMenuPTR[Sub].OptStructPtr[Opt].Name);
				if(cmdVal == -1337)
					continue;
				*TabPtr[tab].SubMenuPTR[Sub].OptStructPtr[Opt].CurVal = cmdVal;
			}
		}
	}
}
void cMenu::CreateConfig(char* conname)
{	
	GameOUTALL("Creating config...\n");
	char name[300];
	
	sprintf(name,"%s\\%s",Path,conname);
	//sprintf(name,"%s",conname);

	ofstream OptionFile;
	OptionFile.open (name);
	for(int tab = 0; tab < NumOfTabs; tab++)
	{
		for(int Sub = 0; Sub < TabPtr[tab].NumOfSubs;Sub++)
		{
			for(int Opt = 0; Opt < TabPtr[tab].SubMenuPTR[Sub].NumOfOpt - 1; Opt++)
			{
				if(TabPtr[tab].SubMenuPTR[Sub].OptStructPtr[Opt].MaxVal == 0 && TabPtr[tab].SubMenuPTR[Sub].OptStructPtr[Opt].MinVal == 0)
					continue;

				OptionFile << TabPtr[tab].SubMenuPTR[Sub].OptStructPtr[Opt].Name << "=" << *TabPtr[tab].SubMenuPTR[Sub].OptStructPtr[Opt].CurVal << endl;
			}
		}
	}
	OptionFile.close();
}




cDebugConsole Con;
void cDebugConsole::DrawCon()
{
	for(int i = 0; i < 19; i++)
	{

		Menu.DrawMenuMessage(30,Menu.Height - 30 - i*20,smallFont,RED,ConOut[i]);
	}
}
void cDebugConsole::Add(char* Output)
{
	for(int i = 0; i < 18;i++)
	{
		ZeroMemory(ConOut[i],500);
		strncpy(ConOut[i],ConOut[i+1],500);
	}
	strncpy(ConOut[19],Output,500);
	//Engine.GameOUT(INFO_WINDOW,"[HACK] %s \n",Output);
}