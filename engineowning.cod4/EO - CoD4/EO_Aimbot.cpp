#include "EO_Main.h"

EO_CAimbot EO_Aimbot;

typedef struct
{
	Vector viewAngles;
}viewAngles_t;
viewAngles_t *local = ( viewAngles_t* )0xC84FD8;



void EO_CAimbot::InitializeAimbot()
{
	if(GetAsyncKeyState(VK_F1) & 1)
	{
		EO_Aimbot.Type = !EO_Aimbot.Type; //1 silent aim kurze zwischenlösung bis menu :P
	}

	Vector vTarget, vAngles, vTemp, vVelocity;
	iTarget = -1;
	float fTemp;
	float fDistance = 0;

	for( int i = 0;i<cgs->maxPlayers;i++ )
	{
		if(!cg_entities[i].currentValid)
			continue;
		if(cg_entities[i].eType != 1)
			continue;
	
		if((cg_entities[i].isAlive & 1) && (cg->clientNum != i))
		{
			if(clientInfo[i].Team != clientInfo[cg->clientNum].Team || clientInfo[i].Team == TEAM_FFA)
			{
				EO_Utils.GetPlayerTag(EO_Utils.ASM_RegisterTag("j_head",1,7),&cg_entities[i],vTarget);
				vTarget.z += 5;
				if(EO_Utils.NormalTrace(vTarget,&cg_entities[i]))
				{
					fDistance = 1.1f;
					iTarget = i;
					VectorCopy( vTarget,vTemp );
					continue;
				}
				float Power = 0;
				if(g_Autowall.bCanPenetrate(&cg_entities[i], vTarget,&Power))
				{
					

					if( Power > fDistance)
					{
						iTarget=i;
						fDistance = Power;
						VectorCopy( vTarget,vTemp );
						
					}
				}
			}
		}
	}
	if(iTarget == -1)
		return;


	EO_Utils.VectorViewAngles(vTemp,vAngles);



	if(Type == 0)
	{
		local->viewAngles.x+=vAngles.x;
		local->viewAngles.y+=vAngles.y;
		local->viewAngles.z+=vAngles.z;
	}
	else
	{
		Angles[0] = vAngles.x;
		Angles[1] = vAngles.y;
		Angles[2] = vAngles.z;
	}

}