



struct EO_MovingText
{
	bool InUse;
	bool OnceFix;
	int Counter;
	int Rotate;
	int KillIcon;
	float Size;
	float PosY;
	float PosX;
	
	void Update(int CurCount);
	void Setup(int Icon);
	EO_MovingText()
	{
		Rotate = 0;
		InUse = false;
	}
	void Reset()
	{
		InUse = false;
		PosY = refdef->y/2 - 37.5;
		PosX = refdef->x/2 - 37.5;
		Rotate = 0;
		OnceFix = true;
	}
};

struct EO_Sounds
{
	int Active;
	int Origin;
	int Destination;
	int Size;
	int NumOfSymbols;
	int Rotating;
	int Icon;

	int* CurKills;
	int Spree;
	int LastKills;
	int Timer;
	int KillCounter;
	int KillCounter2;

	EO_MovingText TextObjects[20];
	int CurTextIndex;

	int GetKills()
	{
		return *CurKills;
	}
	void Update();
	EO_Sounds()
	{
		Size = 1;
		NumOfSymbols = 5;

		CurKills = (int*)0x01DC04F8;
		LastKills = GetKills();
		Spree = 0;
		Timer = 500;

		CurTextIndex = 0;
		Active = true;
	}
};
extern EO_Sounds KillSpree;