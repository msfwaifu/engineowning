#include "EO_Main.h"
EO_CViusals EO_Visuals;

vec4_t				colRed				= { 1.0f, 0.0f, 0.0f, 1.0f };
vec4_t				colRed_				= { 1.0f, 0.0f, 0.0f, 0.2f };
vec4_t				colGreen			= { 0.0f, 1.0f, 0.0f, 1.0f };
vec4_t				colGreen_			= { 0.0f, 1.0f, 0.0f, 0.2f };

void DrawCorneredRect( float x, float y, float w, float h, float * rectColor, float length )
{
    /*** TOP ***/
    // --
    EO_Draw.DrawShader( x, y, length, 1, rectColor, sWhite );
    // |
    EO_Draw.DrawShader( x, y, 1, length, rectColor, sWhite );
    //     --
    EO_Draw.DrawShader( x + w - length, y, length, 1, rectColor, sWhite );
    //      |
    EO_Draw.DrawShader( x + w, y, 1, length, rectColor, sWhite );

    /*** BOTTOM ***/
    // --
    EO_Draw.DrawShader( x, y + h, length, 1, rectColor, sWhite );
    // |
    EO_Draw.DrawShader( x, y + h - length, 1, length, rectColor, sWhite );
    //     --
    EO_Draw.DrawShader( x + w - length, y + h, length, 1, rectColor, sWhite );
    //      |
    EO_Draw.DrawShader( x + w, y + h - length, 1, length, rectColor, sWhite );
}

void EO_CViusals::DrawESP()
{
	char Locked[512];
	for(int i = 0; i < cgs->maxPlayers; i++) { 
		entity_t pEntity = cg_entities[i];
		clientInfo_t pPlayer = clientInfo[i];
		if((pEntity.clientNum == cg->clientNum))
			continue;
		if((!pEntity.currentValid))
			continue;
		if((pEntity.eType != 1) || (!pEntity.isAlive))
			continue;
		vec3_t vOutHead;
		EO_Utils.GetPlayerTag(EO_Utils.ASM_RegisterTag("j_helmet", 1, 9), &cg_entities[i], vOutHead);
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


			float randRed = rand() % 255;
			float randGreen = rand() % 255;
			float randBlue = rand() % 255;

			float r = randRed / 255;
			float g = randGreen / 255;
			float b = randBlue / 255;

			float randColor[4] = { r, g, b, 1 };

			weapon_t * pWeapon = EO_Utils.GetWeapon(cg_entities[i].weapon);

			if(clientInfo[cg->clientNum].Team != pPlayer.Team || pPlayer.Team == TEAM_FFA) {
				sprintf(Locked,"%s",pPlayer.Name);
				EO_Draw.DrawString((RectWidthPos + (RectWidth)) + 8,  fBoxStartY + 6 , consoleFont, 1.0f, colRed, pPlayer.Name);
				EO_Draw.DrawShader(RectWidthPos, fScreenYfeet - RectYoffset + 5,RectWidth, RectYoffset,colRed_,sWhite);
				//DrawCorneredRect( RectWidthPos, fScreenYfeet - RectYoffset + 5,RectWidth, RectYoffset, colRed,5 );
				EO_Draw.DrawRect( RectWidthPos, fScreenYfeet - RectYoffset + 5,RectWidth, RectYoffset, 1.5, colRed );
				EO_Draw.DrawShader((RectWidthPos + (RectWidth)) + 8,fBoxStartY + 6,30,15,colRed,pWeapon->killIcon);
			}
			if( clientInfo[cg->clientNum].Team == pPlayer.Team && pPlayer.Team != TEAM_FFA) {
				sprintf(Locked,"%s",pPlayer.Name);
				EO_Draw.DrawString((RectWidthPos + (RectWidth)) + 8,  fBoxStartY + 6 , consoleFont, 1.0f, colGreen, pPlayer.Name);
				EO_Draw.DrawShader(RectWidthPos, fScreenYfeet - RectYoffset + 5,RectWidth, RectYoffset,colGreen_,sWhite);
				//DrawCorneredRect( RectWidthPos, fScreenYfeet - RectYoffset + 5,RectWidth, RectYoffset, colRed,5 );
				EO_Draw.DrawRect( RectWidthPos, fScreenYfeet - RectYoffset + 5,RectWidth, RectYoffset, 1.5, colGreen );
				EO_Draw.DrawShader((RectWidthPos + (RectWidth)) + 8,fBoxStartY + 6,30,15,colGreen,pWeapon->killIcon);
			}
		}
	}
}