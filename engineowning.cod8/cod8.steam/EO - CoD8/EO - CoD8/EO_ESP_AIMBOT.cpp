
//comment
#include "EO_Main.h"

EO_ESP ESP;

void EO_ESP::ESP()
{
	if(!this->ESPOn)
		return;

	for (int i = 0; i < 2046; i++ )
	{
	

		centity_t pEntity = cg_entities[i];
		
		if(!pEntity.Valid)
			continue;
		if(pEntity.eType == ET_ITEM)
		{
			if(cg_entities[i].weapon == 0)
				continue;
			if(EO_Utils.GetWeapon(cg_entities[i].weapon).Icon == 0)
				continue;
			if(cg_entities[i].isAlive & 1)
			{
				vec2_t ScreenPos;
				if(EO_Utils.WorldToScreen(cg_entities[i].lerpOrigin,ScreenPos))
					EO_Draw.DrawShaderRot(ScreenPos[0] - 25,ScreenPos[1] - 25,50,50,WHITE,EO_Utils.GetWeapon(cg_entities[i].weapon).Icon,0);
			}
		}
		if(pEntity.eType == ET_MISSILE)
		{
			if(cg_entities[i].weapon == 0)
				continue;
			if(EO_Utils.GetWeapon(cg_entities[i].weapon).Icon == 0)
				continue;
			if(pEntity.isAlive & 1)
			{
				vec2_t ScreenPos;
				if(EO_Utils.WorldToScreen(pEntity.lerpOrigin,ScreenPos))
					EO_Draw.DrawShaderRot(ScreenPos[0] - 25,ScreenPos[1] - 25,50,50,RED,EO_Utils.GetWeapon(cg_entities[i].weapon).Icon,0);
			}
		}
		if(pEntity.eType == ET_HELICOPTER)
		{
			if(pEntity.isAlive & 1)
			{
				vec2_t ScreenPos;
				if(EO_Utils.WorldToScreen(pEntity.lerpOrigin,ScreenPos))
					EO_Draw.DrawShader(ScreenPos[0] - 50,ScreenPos[1] - 50,100,100,RED,HelicopterIcon);
			}
		}

		if( i > 17)
			continue;
		clientInfo_t pClient = clientinfo[i]; 

		if(!pClient.Valid)
			continue;
		if(cg_entities[i].clientNum == cg->ClientNum)
			continue;
		if((pEntity.eType != 1) || (!(pEntity.isAlive & 1)))
			continue;
		if(clientinfo[i].Team > 2)
			continue;
		
		Vector HeadPos;
		EO_Utils.GetPlayerTag( *( WORD* )0x1D69408,&cg_entities[i],HeadPos );

		float Screen[2];  
		float ScreenHead[2] = {0,0};

		bool enemy = !(((pClient.Team == 1) || (pClient.Team == 2)) && (pClient.Team == clientinfo[cg->ClientNum].Team));

		enemy ^= Aimbot.SwapTeams;

		if (enemy == 1 && this->EnemyEsp == 0) continue;

		if (enemy == 0 && this->TeamEsp == 0) continue;

		if (EO_Utils.WorldToScreen(pEntity.lerpOrigin,Screen) && EO_Utils.WorldToScreen(HeadPos,ScreenHead))
		{

			Color clBackground, clForeground;

			if( enemy ) 
			{

				memcpy(clBackground, RED_TRANS, 16);
				memcpy(clForeground, RED, 16);

				float height = (Screen[1] - ScreenHead[1] );
				float Width;
				if(height < 10)
					Width = height*3;
				else
					Width = height/2;

				if (this->BoxEsp > 0)
				{

					switch (this->BoxEsp)
					{

					case 1: //Only bordered
					{

						clBackground[3] = 0;
						break;

					}

					case 2: //Only filled
					{

						clForeground[3] = 0;
						break;

					}

					case 3:
					default:
						break;

					}

					EO_Draw.DrawRectFilled(Screen[0] - Width / 2, ScreenHead[1], Width, height, 2, clBackground, clForeground);

				}

				if (this->NameEsp)
					EO_Draw.DrawString(Screen[0] + Width/2 + 5,ScreenHead[1] + 10,consoleFont,1,RED,pClient.Name);

				if (cg_entities[i].weapon != 0)
				{

					if (this->WeaponEsp == 1) //icon
					{
						EO_Draw.DrawShaderRot(Screen[0] + Width / 2 + 5, ScreenHead[1] + 10, height, height / 2, RED, EO_Utils.GetWeapon(cg_entities[i].weapon).Icon, 0); 
					}
					else if (this->WeaponEsp == 2) //text
					{

						EO_Draw.DrawString(Screen[0] + Width / 2 + 5, ScreenHead[1] + 25, consoleFont, 0.8f, RED, EO_Utils.GetWeapon(cg_entities[i].weapon).szLocalizedName);

					}

				}

				if(cg_entities[cg->ClientNum].isAlive & 1)
					Aimbot.CalculateTarget(i,HeadPos);

			}
			else
			{

				memcpy(clBackground, GREEN_TRANS, sizeof(Color));
				memcpy(clForeground, GREEN, sizeof(Color));

				float height = (Screen[1] - ScreenHead[1] );
				float Width;
				if(height < 10)
					Width = height*3;
				else
					Width = height/2;

				if (this->BoxEsp > 0)
				{

					switch (this->BoxEsp)
					{

					case 1: //Only bordered
					{

						clBackground[3] = 0;
						break;

					}

					case 2: //Only filled
					{

						clForeground[3] = 0;
						break;

					}

					case 3:
					default:
						break;

					}

					EO_Draw.DrawRectFilled(Screen[0] - Width / 2, ScreenHead[1], Width, height, 2, clBackground, clForeground);

				}

				if (this->NameEsp)
					EO_Draw.DrawString(Screen[0] + Width / 2 + 5, ScreenHead[1] + 10, consoleFont, 1, GREEN, pClient.Name);

				if (cg_entities[i].weapon != 0)
				{

					if (this->WeaponEsp == 1) //icon
					{
						EO_Draw.DrawShaderRot(Screen[0] + Width / 2 + 5, ScreenHead[1] + 10, height, height / 2, GREEN, EO_Utils.GetWeapon(cg_entities[i].weapon).Icon, 0);
					}
					else if (this->WeaponEsp == 2) //text
					{

						EO_Draw.DrawString(Screen[0] + Width / 2 + 5, ScreenHead[1] + 25, consoleFont, 0.8f, GREEN, EO_Utils.GetWeapon(cg_entities[i].weapon).szName);

					}

				}

				if (Aimbot.AimAtTeam && cg_entities[cg->ClientNum].isAlive & 1)
					Aimbot.CalculateTarget(i, HeadPos);

			}
		}


		// SnapLines

		if (ScreenHead[0] == 0 && ScreenHead[1] == 0) continue;

		if (enemy)
		{

			switch (this->SnapLinesMode)
			{

			case 1: //Bottom center
			{

				int nX = refdef->x / 2;
				int nY = refdef->y;

				Menu.DrawLine(nX, nY, ScreenHead[0], ScreenHead[1], 2, RED, false);

				break;

			}

			case 2:
			{

				int nX = refdef->x / 2;
				int nY = refdef->y / 2;

				Menu.DrawLine(nX, nY, ScreenHead[0], ScreenHead[1], 2, RED, false);

				break;

			}

			case 3:
			{

				int nX = refdef->x / 2;
				int nY = 0;

				Menu.DrawLine(nX, nY, ScreenHead[0], ScreenHead[1], 2, RED, false);

				break;

			}

			case 0:
			default:
				break;

			}

		}
		else
		{

			switch (this->SnapLinesMode)
			{

			case 1: //Bottom center
			{

				int nX = refdef->x / 2;
				int nY = refdef->y;

				Menu.DrawLine(nX, nY, ScreenHead[0], ScreenHead[1], 2, GREEN, false);

				break;

			}

			case 2:
			{

				int nX = refdef->x / 2;
				int nY = refdef->y / 2;

				Menu.DrawLine(nX, nY, ScreenHead[0], ScreenHead[1], 2, GREEN, false);

				break;

			}

			case 3:
			{

				int nX = refdef->x / 2;
				int nY = 0;

				Menu.DrawLine(nX, nY, ScreenHead[0], ScreenHead[1], 2, GREEN, false);

				break;

			}

			case 0:
			default:
				break;

			}


		}



	}
}

/*************************************************************************************************/

EO_Aimbot Aimbot;
/*
typedef struct
{
	Vector viewAngles;
}viewAngles_t;
viewAngles_t *local = ( viewAngles_t* )0x1141084 + 4;


typedef struct
{
    int        MaxEntNum;
    int        EntitieNum;
    float    visible;
    int        z_crap0;
    char lol[4]; // might be something u need but not necessary
    Vector    viewOrigin;
    Vector    start;
    Vector    end;
    Vector    viewAngle;
} bulletTrace_t;
 bulletTrace_t*bulletTrace;
vec3_t vec_origin={ 0, 0, 0 };

int  ( __cdecl* R_GetCurWeapon )( cg_t* cg ) = ( int( __cdecl* )( cg_t* ) )0x44C220;

bool R_BulletPenetrationCheck( bulletTrace_t *MapTrace )
{
    DWORD dwCallAddr = 0x5C8990;
    static bool returnC;
    __asm   mov     eax, MapTrace
    __asm    call    dwCallAddr
    __asm   mov    returnC, al

    return returnC;
}
void R_BulletPenetration( int unk1, bulletTrace_t* bulletTrace, int WeaponNum, int unk2, centity_t * cent, int unk3, Vector vieworg, int unk4 )
{
    DWORD dwCallAddr = 0x5CB080;
    __asm    
    {
        push unk4
        push vieworg
        push unk3
        push cent
        push unk2
        push WeaponNum
        push bulletTrace
        push unk1
        call dwCallAddr
        add     esp, 0x20
    }
}

void SetBulletImpacts(weapon_t* pWeapon, bool bState)
{
	if(!bState) 
	{
		if(!pWeapon->iWeaponBulletType)
			pWeapon->iWeaponBulletType = 100;
	} else 
	{
		if(pWeapon->iWeaponBulletType == 100)
			pWeapon->iWeaponBulletType = 0;
	}
}

bool GetRemainingIndex(Vector vieworg, centity_t *TargetEnt, Vector origin,float* power )
{
    if( !bulletTrace )
    {
        bulletTrace = new bulletTrace_t;
        ZeroMemory( bulletTrace, sizeof( bulletTrace_t ) );
    }

    int Weapon                = R_GetCurWeapon( cg );
	weapon_t* pWeapon = EO_Utils.GetWeapon(cg->WeaponID);

    //memset(bulletTrace, 0, 0x44);
    bulletTrace->MaxEntNum    = 2046;
	bulletTrace->EntitieNum = cg->ClientNum;
    bulletTrace->visible    = 1.0f;
	//bulletTrace->z_crap0 = EO_Utils.GetWeapon(cg->WeaponID)->iWeaponBulletType;
	bulletTrace->z_crap0 = clientinfo->weapon;
    
	VectorCopy( refdef->vieworg, bulletTrace->viewOrigin );
    VectorCopy( vieworg, bulletTrace->start );
    VectorCopy( origin, bulletTrace->end );

    Vector delta, angles;
    VectorSubtract( origin, vieworg, delta );
	EO_Utils.vectoangles( delta, angles );

	EO_Utils.AngleVectors( angles, bulletTrace->viewAngle, NULL, NULL );
	SetBulletImpacts(pWeapon, false);

    R_BulletPenetrationCheck( bulletTrace );  
	R_BulletPenetration(0, bulletTrace, Weapon, 0, &cg_entities[cg->ClientNum], 0xFFFFFFFF, vieworg, 0);

	SetBulletImpacts(pWeapon, true);
    
    if(bulletTrace->EntitieNum == TargetEnt->clientNum)
	{
		*power = bulletTrace->visible;
		return (bulletTrace->visible > 0);
	}
	return false;
}*/
DWORD BoneIDOffsets[] =
{
	0x1D695EC, //mainroot
	0x1D69406, //j_helmet
	0x1D69408 //j_head
};
int BonePredictionTable[] = 
{
	15, //mainroot
	3,  //helmet
	5   //head
};




void EO_Aimbot::InitializeAimbot()
{
	if(!Aimbot.AimbotOn)
		return;

	vec3_t vTarget,vAngles, vVelocity;
	BestTarget = -1;
	float fTemp;
	float fDistance = 0;
	float MaxDistance = 9999999999.0f;
	RiotTarget = -1;
	float RiotDamage = 0;

	if((*(byte*)(0x9DC3A0 + 0x374) & 2))
		return;
	if(!(cg_entities[cg->ClientNum].isAlive & 1))
		return;
	for( int i = 0;i<cgs->maxPlayers;i++ )
	{
		if(!cg_entities[i].Valid || cg_entities[i].eType != 1)
		{
			Menu.TabPtr[0].SubMenuPTR[3].OptStructPtr[i].Name = "NO PLAYER";
			continue;
		}
		Menu.TabPtr[0].SubMenuPTR[3].OptStructPtr[i].Name = clientinfo[i].Name;
		if(PlayerList[i] == 3)
			continue;
	
		if((cg_entities[i].isAlive & 1) && (cg->ClientNum != i))
		{
			bool enemy = ( ! ( ( ( clientinfo[i].Team == 1 ) || ( clientinfo[i].Team == 2 ) ) && ( clientinfo[i].Team == clientinfo[cg->ClientNum].Team) ) ) ^ SwapTeams;

			enemy ? 0 : AimAtTeam ? enemy = true : 0;

			

			if(enemy)
			{
				char* NamePtr = EO_Utils.GetWeapon(cg_entities[i].weapon).szName;
				if( strstr(NamePtr, "riot") ) //RIOT not sure if work (should from mw2) cheap method as i havent found WeaponType yet, changed erik's single char compare shit to strstr cmp^^
				{
					float Distance[2];
					Vector EyePos;
					if(EO_Utils.GetPlayerTag(*(WORD*)0x1D694C6,&cg_entities[i],EyePos)) //Get head pos from enemy
					{
						EO_Utils.GetAngleToOrigin(EyePos,cg_entities[i].lerpAngles,Distance[0],Distance[1]); 
						if (!(Distance[0] < 100.f && Distance[0] > -100.f))
						{
							//return; //this would disable the entire aimbot as soon as someone with riot is hitable....
							
							continue; //so just check the next player...

						}
					}
				}

				for(int j = 0; j < 2; j++)
				{
					EO_Utils.GetPlayerTag(*reinterpret_cast<WORD*>(BoneIDOffsets[j]),&cg_entities[i],vTarget );
					if(Aimbot.Prediction)
						Predict(&cg_entities[i],vTarget,BonePredictionTable[j],(j == 1) || (j == 2)); //auskommentieren = prediction nö

					if(EO_Utils.NormalTrace(vTarget,&cg_entities[i]) && fDistance != 1.1f)
					{
						fDistance = 1.0f;
						BestTarget = i;
						FoundEnemy = true;
						VectorCopy( vTarget,vTemp );
						continue;
					}
					/*float flPenetration = 0.0f;
					flPenetration = EO_Utils.GetRemainingPower(refdef->vieworg,&cg_entities[i],cg_entities[cg->ClientNum].weapon,vTarget);*/
						
					float flPenetration = 0.0f;
					if(!g_Autowall.GetRemainingPower(refdef->vieworg, &cg_entities[i], vTarget, &flPenetration))
					{
						if(PlayerList[i] == 2 && RiotDamage != 2)
						{
							RiotTarget = i;
							RiotDamage = 2;
						}
						continue;
					}
					if(PlayerList[i] == 2)
					{
						RiotTarget = i;
						RiotDamage = 2;

						fDistance = 1.1f;
						BestTarget = i;
						FoundEnemy = true;
						VectorCopy( vTarget,vTemp );
						continue;
					}
					if(flPenetration > 0.6f && PlayerList[i] == 1 && fDistance != 1.1f)
					{
						
						fDistance = 1.0f;
						BestTarget = i;
						FoundEnemy = true;
						VectorCopy( vTarget,vTemp );
						continue;
					}

					if(flPenetration > 0.80 && j == 2)
					{

						fDistance = 1;
						BestTarget = i;
						FoundEnemy = true;
						VectorCopy( vTarget,vTemp );
					}
					else if((flPenetration > fDistance))
					{
			
						fDistance = flPenetration;
						BestTarget = i;
						FoundEnemy = true;
						VectorCopy( vTarget,vTemp );
					}
					else if(flPenetration == fDistance && (flPenetration > 0))
					{
				
						float NewDist = EO_Utils.GetDistance( cg_entities[i].lerpOrigin, cg_entities[cg->ClientNum].lerpOrigin );
						if(NewDist < MaxDistance)
						{
							MaxDistance = NewDist;
							BestTarget = i;
							FoundEnemy = true;
							VectorCopy( vTarget,vTemp );
						}

					}
				}

			}
		}
	}
	if(BestTarget == -1)
		return;
	if(Silent)
		return;
	if(*(byte*)0x009DC5E1 != 0)
		return;
	float AimAt[2];
	EO_Utils.GetAngleToOrigin(vTemp,AimAt[0],AimAt[1]);
	*(float*)0x1141088 += AimAt[0];
	*(float*)0x1141084 += AimAt[1];

}



void EO_Aimbot::CalculateTarget(int i,float* Head)
{
	//if(!EO_Utils.NormalTrace(Head,&cg_entities[i]))
		//return;

	float NewPower = EO_Utils.GetRemainingPower(refdef->vieworg,&cg_entities[i],clientinfo[cg->ClientNum].weapon,Head);

	//float NewDist = EO_Utils.GetDistance(refdef->vieworg,Head);
	if(NewPower > LastDistance)
	{
		LastDistance = NewPower;
		BestTarget = i;
		FoundEnemy = true;
	}
}



void EO_Aimbot::Predict(centity_t* TargetEntity, float* BonePosition,int Scale,bool NotAllowZ ) 
{
 vec3_t EnemyVelocityTemp;
 Vector EnemyVelocity;

 VectorSubtract( TargetEntity->newOrigin, TargetEntity->oldOrigin, EnemyVelocityTemp );

 EnemyVelocity.x = EnemyVelocityTemp[0];
 EnemyVelocity.y = EnemyVelocityTemp[1];
 EnemyVelocity.z = EnemyVelocityTemp[2];

 Vector CalcVec = EnemyVelocity.Normalize();


 CalcVec.x *= Scale;
 CalcVec.y *= Scale;
 CalcVec.z *= Scale;

 float TempOld = BonePosition[2];
 

 BonePosition[0] += CalcVec.x;
 BonePosition[1] += CalcVec.y;
 BonePosition[2] += CalcVec.z;

 if(NotAllowZ)
	 BonePosition[2] = TempOld;

}