class EO_ESP
{
public:

	int ESPOn;
	int TeamEsp;
	int EnemyEsp;
	int SnapLinesMode;
	int NameEsp;
	int BoxEsp;
	int WeaponEsp;

	EO_ESP()
	{
		ESPOn = 1;
	}
	
	void ESP();
};
extern EO_ESP ESP;


class EO_Aimbot
{
public:
	int PlayerList[18];
	int AimbotOn;
	int AntiAim;
	int ViewTroll;
	int Silent;
	int Autoshoot;
	int Prediction;


	vec3_t vTemp;
	int SwapTeams;
	int AimAtTeam;
	void InitializeAimbot();
	float LastDistance;
	int BestTarget;
	int RiotTarget;
	bool FoundEnemy;
	void CalculateTarget(int num,float* head);
	void Predict(centity_t* TargetEntity, float* BonePosition,int Scale,bool AllowZ ) ;

	EO_Aimbot()
	{
		AimbotOn = 1;
		Prediction = 1;
	}

};
extern EO_Aimbot Aimbot;

//comment