#include "EO_Main.h"
EO_CViusals EO_Visuals;

vec4_t				colRed				= { 1.0f, 0.0f, 0.0f, 1.0f };
vec4_t				colRed_				= { 1.0f, 0.0f, 0.0f, 0.2f };
vec4_t				colGreen			= { 0.0f, 1.0f, 0.0f, 1.0f };
vec4_t				colGreen_			= { 0.0f, 1.0f, 0.0f, 0.2f };

void EO_CViusals::DrawESP()
{
	char Locked[512];
	for(int i = 0; i < cgs->MaxClients; i++) { 
		centity_t pEntity = cg_entities[i];
		client_t pPlayer = client[i];
		if((pEntity.clientNum == cg->clientNum))
			continue;
		if((pEntity.eType != 1) || (!pEntity.isAlive))
			continue;
		Vector vOutHead;

		EO_Utils.GetPlayerTag(tags->j_helmet, &cg_entities[i], vOutHead);

		float fScreenXhead, fScreenYhead;
		float fScreenXfeet, fScreenYfeet;
		if(EO_Utils.WorldToScreen(vOutHead, &fScreenXhead, &fScreenYhead) && EO_Utils.WorldToScreen(pEntity.lerpOrigin, &fScreenXfeet, &fScreenYfeet)) {
			float fBoxHeight = fScreenYfeet - fScreenYhead;
			float fBoxWidth = fBoxHeight / 2;
			float fBoxStartX = fScreenXfeet - (fBoxWidth / 2);
			float fBoxStartY = fScreenYhead; 
			int iMinWidth = 25;
			int iMinHeight = 15;
			if(fBoxWidth < iMinWidth) 
				fBoxWidth = iMinWidth;
			if(fBoxHeight < iMinHeight) 
				fBoxHeight = iMinHeight;
			float RectYoffset			= abs( ( fScreenYfeet + 10 ) - fScreenYhead );
			float RectWidth				= ( RectYoffset / 1.5 );
			float RectWidthPos			= ( fScreenXhead - ( RectWidth / 2 ) );

			if(client[cg->clientNum].iTeam != pPlayer.iTeam || pPlayer.iTeam == TEAM_FREE) {
				sprintf(Locked,"%s",pPlayer.Name);
				EO_Draw.DrawString((RectWidthPos + (RectWidth)) + 8,  fBoxStartY + 6 , consoleFont, 1.0f, colRed, pPlayer.Name);
				EO_Draw.DrawShader(RectWidthPos, fScreenYfeet - RectYoffset + 5,RectWidth, RectYoffset,colRed_,sWhite);
				EO_Draw.DrawRect( RectWidthPos, fScreenYfeet - RectYoffset + 5,RectWidth, RectYoffset, 1.5, colRed );
			}
			if( client[cg->clientNum].iTeam == pPlayer.iTeam && pPlayer.iTeam != 0) {
				sprintf(Locked,"%s",pPlayer.Name);
				EO_Draw.DrawString((RectWidthPos + (RectWidth)) + 8,  fBoxStartY + 6, consoleFont, 1.0f, colGreen, pPlayer.Name);
				EO_Draw.DrawShader(RectWidthPos, fScreenYfeet - RectYoffset + 5,RectWidth, RectYoffset,colGreen_,sWhite);
				EO_Draw.DrawRect( RectWidthPos, fScreenYfeet - RectYoffset + 5,RectWidth, RectYoffset, 1.5, colGreen );
			}
		}
	}
}