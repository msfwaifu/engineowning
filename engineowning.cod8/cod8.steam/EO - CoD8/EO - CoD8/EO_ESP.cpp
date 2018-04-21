

#include "EO_Main.h"

EO_ESP ESP;

void EO_ESP::ESP()
{
	for (int i = 0; i < 18; i++ )
	{
		centity_t pEntity = cg_entities[i];
		clientInfo_t pClient = clientinfo[i]; 

		if((pEntity.clientNum == cg->clientNum))
			continue;
		if((pEntity.eType != 1) || (!pEntity.isAlive & 1))
			continue;

		Vector HeadPos;
		EO_Utils.GetPlayerTag( *( WORD* )0x1D69408,&cg_entities[i],HeadPos );

		float Screen[2];  
		float ScreenHead[2];
		if (EO_Utils.WorldToScreen(pEntity.lerpOrigin,Screen) && EO_Utils.WorldToScreen(HeadPos,ScreenHead))
		{
			

			if( clientinfo[cg->clientNum].Team == pClient.Team && pClient.Team != 0) 
			{
				float height = (Screen[1] - ScreenHead[1] );
				float Width = height/2;

				EO_Draw.DrawRect(Screen[0] - Width/2,ScreenHead[1],Width,height,3,GREEN);
				EO_Draw.DrawString(Screen[0] + Width/2 + 5,ScreenHead[1],consoleFont,1,GREEN,pClient.Name);
			}
			else if(pClient.Team != 0)
			{
				float height = (Screen[1] - ScreenHead[1] );
				float Width = height/2;

				EO_Draw.DrawRect(Screen[0] - Width/2,ScreenHead[1],Width,height,3,RED);
				EO_Draw.DrawString(Screen[0] + Width/2 + 5,ScreenHead[1],consoleFont,1,RED,pClient.Name);
			}
		}
	}
}