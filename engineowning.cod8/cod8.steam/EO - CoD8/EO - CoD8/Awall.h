
class CAutowall
{
public:
	bool GetRemainingPower( Vector vieworg, centity_t* cent, Vector origin, float* remainingPower );

private:
	void SetBulletImpacts( weapon_t* pWeapon, bool bState );
	void SetupBulletTrace( bulletTrace_t* btr, Vector start, Vector end, int skipNum );
	void DrawBulletTrajectory( centity_t* cent, bulletTrace_t* bulletTrace, weapon_t* weapon, Vector vieworg );
}extern g_Autowall;

