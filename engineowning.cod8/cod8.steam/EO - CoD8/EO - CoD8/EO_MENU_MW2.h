
#define CONFIG_NAME "LastOptions.eoconfig"


typedef void* FONT_T;
typedef int SHADER_T;
typedef float Color[4];

static char EMPTY[] = "-EMPTY-";



void showmsg(char* what);
void showmsg(int what);
void showmsg(float what);
float StringWidth(char* text,float scaleX,float scaleY,FONT_T font);

static int BACKPLCH = 0;

class cDebugConsole
{
public:
	char ConOut[20][501];

	void DrawCon();
	void Add(char* Output);
	//char* operator<<(char* Args)
	//{
	//	Add(Args);
	//}
};
extern cDebugConsole Con;


struct cOption
{
	bool Valid,UseString;
	int MinVal,MaxVal;
	int* CurVal;
	char* Name;
	char* OptNames[10];
	
	//float TextSize;
	cOption()
	{
		//TextSize = 0;
		Name = EMPTY;
		Valid = false;
		UseString = false;
		MinVal = 0;
		MaxVal = 0;
		Name = EMPTY;
		for(int i = 0; i < 9; i++)
			OptNames[i] = EMPTY;
	}
	void Init(char* nName,int min,int max,int* OutVPTR,char* OptName1,char* OptName2,char* OptName3,char* OptName4,char* OptName5,char* OptName6,char* OptName7,char* OptName8,char* OptName9,char* OptName10)
	{
		Valid = true;
		UseString = true;
		Name = nName;
		MinVal = min;
		MaxVal = max;
		CurVal = OutVPTR;
		OptNames[0] = OptName1;
		OptNames[1] = OptName2;
		OptNames[2] = OptName3;
		OptNames[3] = OptName4;
		OptNames[4] = OptName5;
		OptNames[5] = OptName6;
		OptNames[6] = OptName7;
		OptNames[7] = OptName8;
		OptNames[8] = OptName9;
		OptNames[9] = OptName10;

		//TextSize = StringWidth(Name,1,1,Engine.NormalFont); //ANPASSEN
	}
	void Init(char* nName,int min,int max,int* OutVPTR)
	{
		Valid = true;
		UseString = false;
		Name = nName;
		MinVal = min;
		MaxVal = max;
		CurVal = OutVPTR;
		OptNames[0] = EMPTY;
		OptNames[1] = EMPTY;
		OptNames[2] = EMPTY;
		OptNames[3] = EMPTY;
		OptNames[4] = EMPTY;
		OptNames[5] = EMPTY;
		OptNames[6] = EMPTY;
		OptNames[7] = EMPTY;
		OptNames[8] = EMPTY;
		OptNames[9] = EMPTY;
		//TextSize = StringWidth(Name,1,1,Engine.NormalFont); //ANPASSEN
	}
};

struct cSubMenu
{
	
	char* Name;
	int NumOfOpt;
	int CurOpt;
	cOption * OptStructPtr;
	

	cSubMenu()
	{
		Name = EMPTY;
		CurOpt = 0;
		NumOfOpt = 1;
		OptStructPtr = new cOption[1];
		
	}
	void AddOption(char* nName,int min,int max,int* OutVPTR,char* OptName1,char* OptName2,char* OptName3,char* OptName4,char* OptName5,char* OptName6,char* OptName7,char* OptName8,char* OptName9,char* OptName10)
	{
		NumOfOpt += 1;

		cOption* TempNewOpt = new cOption[NumOfOpt+1];
		memcpy(TempNewOpt,OptStructPtr,sizeof(cOption)*NumOfOpt);
		
		TempNewOpt[NumOfOpt-2].Init(nName, min, max, OutVPTR, OptName1, OptName2, OptName3, OptName4, OptName5, OptName6, OptName7, OptName8, OptName9, OptName10);
		TempNewOpt[NumOfOpt-1].Init("BACK",0,0,&BACKPLCH);

		delete[] OptStructPtr;
		OptStructPtr = new cOption[NumOfOpt+1];
		memcpy(OptStructPtr,TempNewOpt,sizeof(cOption)*NumOfOpt+1);

		delete[] TempNewOpt;
	}
	void AddOption(char* nName,int min,int max,int* OutVPTR)
	{
		NumOfOpt += 1;

		cOption* TempNewOpt = new cOption[NumOfOpt+1];
		memcpy(TempNewOpt,OptStructPtr,sizeof(cOption)*NumOfOpt);
		
		TempNewOpt[NumOfOpt-2].Init(nName, min, max, OutVPTR);
		TempNewOpt[NumOfOpt-1].Init("BACK",0,0,&BACKPLCH);

		delete[] OptStructPtr;
		OptStructPtr = new cOption[NumOfOpt+1];
		memcpy(OptStructPtr,TempNewOpt,sizeof(cOption)*(NumOfOpt+1));

		delete[] TempNewOpt;
	}
	void Init(char* name)
	{
		Name = name;
		CurOpt = 0;
		NumOfOpt = 1;
	}
	void Reset()
	{
		Name = EMPTY;
		CurOpt = 0;
		NumOfOpt = 1;
		delete[] OptStructPtr;
	}
	~cSubMenu()
	{
		delete[] OptStructPtr;
	}
};
struct cTab
{
	
	char* Name;
	
	int NumOfSubs,Cursub,CurSubSelected;
	cSubMenu* SubMenuPTR;
	


	cTab()
	{
		CurSubSelected = 0;
		Name = EMPTY;
		SubMenuPTR = new cSubMenu[1];
		NumOfSubs = 0;
		Cursub = -1;
	}
	void AddSubMenu(char* name)
	{
		
		NumOfSubs += 1;

		cSubMenu* TempNewOpt = new cSubMenu[NumOfSubs+1];
		memcpy(TempNewOpt,SubMenuPTR,sizeof(cSubMenu)*NumOfSubs);
		
		TempNewOpt[NumOfSubs-1].Init(name);

		delete[] SubMenuPTR;
		SubMenuPTR = new cSubMenu[NumOfSubs+1];
		memcpy(SubMenuPTR,TempNewOpt,sizeof(cSubMenu)*(NumOfSubs+1));

		delete[] TempNewOpt;
		
	}
	void Init(char* name)
	{
		Name = name;
		Cursub = -1;
		NumOfSubs = 0;


		//TextSize = StringWidth(Name,1,1,Engine.NormalFont); //ANPASSEN
	}
};

class cMenu
{
	int MouseControlled;
	int MenuStyle;

	//##########################################################
	//MENU INTERNAL
	void GetKeys();
	void MouseControlSub();
	//##########################################################

public:
	HANDLE ModuleBase;
	char Path[260];

	int SaveCon[6];
	int LoadCon[6];

	//###########################################################
	//Drawing interface
	void DrawMenuMessage(float x,float y,FONT_T font,Color COL,char* msg);
	void DrawMenuRect(float X,float Y,float width,float height,Color col,bool adjust);
	void DrawRotated(float X,float Y,float width,float height,float ANGLE,Color col,bool adjust);
	void DrawBox(float X,float Y,float width,float height,float Size,Color col,bool adjust);
	void DrawRectBorder(float X,float Y,float width,float height,float Size,Color BGcolor,Color BOXColor,bool adjust);

	void DrawLine(float X1,float Y1,float X2,float Y2,float Size,Color col,bool adjust);

	void SCR_AdjustFrom640( float *x, float *y, float *w, float *h );
	int GetCmd(char* filename,char* cmdname);
	//##########################################################

	bool MenuActive;

	Color MENUBG,FONTCOLOR,CURSORCOLOR;

	float PosX,PosY,Width,Height;
	int NumOfTabs,CurTab;
	cTab* TabPtr;

	cMenu()
	{
		PosX = 0;
		PosY = 0;
		NumOfTabs = 0;
		CurTab = 0;
		TabPtr = new cTab[1];

		CpyColor(MENUBG,BLACK);
		CpyColor(FONTCOLOR,WHITE);
		CpyColor(CURSORCOLOR,GRAY);
		MenuActive = true;
	}
	void Init(float X,float Y)
	{
		PosX = X;
		PosY = Y;
		InitOptions();
	}
	void AddTab(char* name)
	{
		NumOfTabs += 1;

		cTab* TempNewOpt = new cTab[NumOfTabs+1];
		memcpy(TempNewOpt,TabPtr,sizeof(cTab)*NumOfTabs);
		
		TempNewOpt[NumOfTabs-1].Init(name);

		delete[] TabPtr;
		TabPtr = new cTab[NumOfTabs+1];
		memcpy(TabPtr,TempNewOpt,sizeof(cTab)*(NumOfTabs+1));

		delete[] TempNewOpt;
	}
	void AddSub(int Tab,char* name)
	{
		if(Tab >= 0)
		{
			if(Tab > NumOfTabs-1)
			{
				//showmsg("ERROR: wanted to add a submenu to a non existing pointer!");
				//showmsg(name);
				Con.Add("ERROR: wanted to add a submenu to a non existing pointer!");
				Con.Add(name);
				return;
			}
			TabPtr[Tab].AddSubMenu(name);
		}
		else
			Con.Add("Negative pointer.");
	}
	void AddOption(int Tab,int Sub,char* name,int Min,int Max,int* cur)
	{
		if(Tab >= 0 && Sub >= 0)
		{
			if(Tab > NumOfTabs-1)
			{
				Con.Add("ERROR: wanted to add an option to a non existing Tabpointer!");
				Con.Add(name);
				return;
			}
			if( Sub > TabPtr[Tab].NumOfSubs - 1)
			{
				Con.Add("ERROR: wanted to add an option to a non existing Subpointer!");
				Con.Add(name);
				return;
			}
			TabPtr[Tab].SubMenuPTR[Sub].AddOption(name,Min,Max,cur);
		}
		else
			Con.Add("Negative pointer.");
	}
	void AddOption(int Tab,int Sub,char* name,int Min,int Max,int* cur,char* OptName1,char* OptName2,char* OptName3 = "",char* OptName4 = "",char* OptName5 = "",char* OptName6 = "",char* OptName7 = "",char* OptName8 = "",char* OptName9 = "",char* OptName10 = "")
	{
		if(Tab >= 0 && Sub >= 0)
		{
			if(Tab > NumOfTabs-1)
			{
				Con.Add("ERROR: wanted to add an option to a non existing Tabpointer!");
				Con.Add(name);
				return;
			}
			if( Sub > TabPtr[Tab].NumOfSubs - 1)
			{
				Con.Add("ERROR: wanted to add an option to a non existing Subpointer!");
				Con.Add(name);
				return;
			}
			TabPtr[Tab].SubMenuPTR[Sub].AddOption(name,Min,Max,cur,OptName1, OptName2, OptName3, OptName4, OptName5, OptName6, OptName7, OptName8, OptName9, OptName10);
		}
		else
			Con.Add("Negative pointer.");
	}

	void DrawIt();
	void InitOptions(); //GETS AUTOMTICLY CALLED

	void CpyColor(float* Color1,float* Color2);
	
	bool StringCmp(char* a1,char* a2);
	bool StringCmp2(char* a1,char* a2);
	void GameOUTALL(char* text);

	bool fileExist (char* name);
	void ReadConfig(char* name);
	void CreateConfig(char* name);

};


extern cMenu Menu;