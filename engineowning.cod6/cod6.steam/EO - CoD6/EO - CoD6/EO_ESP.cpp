#include "EO_Main.h"

EO_ESP ESP;

void EO_ESP::DrawName(int EntityNum,Color color,bool vis)
{
	float Screen[2];
	Vector BonePos;

	if(Engine.GetTagPos(Entity[EntityNum],"j_head",BonePos))
	{
	
		if(Engine.WorldToScreen(0,Engine.GetScreenMatrix(0),BonePos,Screen))
		{
			
			if(!vis)
			{				
				Draw.DrawString(Screen[0] + 10,Screen[1],Draw.ConsoleFont,color,Client[EntityNum]->szName);
			}
			else
			{
				Draw.DrawString(Screen[0] + 10,Screen[1],Draw.ConsoleFont,VISIBLE,Client[EntityNum]->szName);
			}
		}

	}
}
Color BoxCol;
void EO_ESP::DrawBox(int num,Color color,bool vis)
{
	float ScreenOrigin[2];
	float ScreenHead[2];
	Vector BonePos;



	color[3] = 0.5f;
	

	if(Engine.GetTagPos(Entity[num],"j_head",BonePos))
	{
		if(Engine.WorldToScreen(0,Engine.GetScreenMatrix(0),Entity[num]->vOrigin,ScreenOrigin) && Engine.WorldToScreen(0,Engine.GetScreenMatrix(0),BonePos,ScreenHead))
		{
			float height =(ScreenOrigin[1] - ScreenHead[1] );
			float Width = (Entity[num]->eFlags & 0x0008 ? (height * 3) : (height / 2)) + 5.f;
			
			if(!vis)
			{
				
				//Engine.DrawShaderStreched(ScreenOrigin[0] - Width / 2,ScreenHead[1],Width,height,0,0.5,0.5,0,color,Draw.ScanLines);
				
				
				Draw.DrawBox(ScreenOrigin[0] - Width / 2,ScreenHead[1],Width,height,color,2);
				color[3] = 0.2f;
				Draw.DrawRect(ScreenOrigin[0] - Width / 2,ScreenHead[1],Width,height,color);

			}
			else
			{
				Draw.DrawBox(ScreenOrigin[0] - Width / 2,ScreenHead[1],Width,height,VISIBLE,2);
				Color tempCol;
				tempCol[0] = VISIBLE[0];
				tempCol[1] = VISIBLE[1];
				tempCol[2] = VISIBLE[2];
				tempCol[3] = 0.2f;

				Draw.DrawRect(ScreenOrigin[0] - Width / 2,ScreenHead[1],Width,height,tempCol);
			}
		}

	}
	
	
}
