

class EO_Aimbot
{
public:
	bool FoundEnemy;
	int BestTarget,BestBone;
	float LastDifference;
	float LastDifference2;

	EO_Aimbot()
	{
		BestTarget = -1;
		BestBone = -1;
	}
	void CalculateBestTarget(int EntityNum);

	void GetAngleToOrigin(Vector vOrigin, float &flOutX, float &flOutY);
	void GetAngleToOrigin(Vector vOrigin,Vector ViewAngle , float &flOutX, float &flOutY);
	void GetAngleToOrigin(Vector vOrigin,Vector vMyOrigin,Vector ViewAngle, float &flOutX, float &flOutY);


};extern EO_Aimbot Aimbot;