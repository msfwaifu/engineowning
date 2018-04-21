#include "EO_Main.h"


char* KillSoundFeed[] =
{
"HEADSHOT!",
"DOUBLE KILL",
"!KILLING SPREE!",
"RAMPAGE!!!",
"^2!HOLY SHIT!",
"^2^^DOMINATING^^",
"^2WICKED SIIIICK",
"^2UNSTOPPABLE",
"^1!!MULTIKILL!!",
"^1M-M-M-MONTERKILLLL",
"^1!!!GODLIKE!!!",
"^1MeGaKiLl",
"^1OOOOOOOOOWNAAAAAAAAGE",
"^1ULTRAKILL!",
"^2!!!!!! ^1MONSTERKILL ^2!!!!!"
};






EO_Sounds KillSpree;

Color WHITE_ = {1,1,1,1};

void EO_Sounds::Update()
{
	int Shader;
	if(Icon == 0)
	{
		Shader = HeadShotIcon;
	}
	else if(Icon == 1)
	{
		Shader = SuicideIcon;
	}
	else if(Icon == 2)
	{
		rand() % 2 ? Shader = HeadShotIcon : Shader = SuicideIcon;
	}
	else if(Icon == 3)
	{
		Shader = rand() % 20; //testing...crasht
	}

	if(!Active)
		return;
	if(Timer != 0)
		Timer -= 1;
	else
	{
		for(int i = 0; i < 20; i++)
		{
			TextObjects[i].Reset();
		}
		Spree = 0;
		WHITE_[3] = 1;
		KillCounter = 0;
		KillCounter2 = 0;
	}
	if(GetKills() != LastKills)
	{
		WHITE_[3] = 1;
		Timer = 500;
		TextObjects[CurTextIndex].Setup(Shader);
		CurTextIndex += 1;
		if(CurTextIndex > 19)
			CurTextIndex = 0;

		int DeltaKills = GetKills() - LastKills;
		if(DeltaKills > 0)
		{
			if(Spree < 14)
			{
				if(Spree + DeltaKills < 15)
					Spree += DeltaKills;
				else
					Spree = 14;
			}
			KillCounter2 += DeltaKills;
		}
		

		LastKills = GetKills();

		char PathBuff[200];


		if(Active == 1 || Active == 2)
		{
			char SoundPath[50];
			sprintf(SoundPath,"snd\\%d.wav",Spree);
			PlaySoundA(SoundPath,NULL,SND_FILENAME | SND_ASYNC);
		}
		
	}
	if(Active == 2)
		return;
	if(Spree != 0)
	{
		WHITE_[3] -= 0.002;
	}
	if(KillCounter2 > 0)
	{
		TextObjects[CurTextIndex].Setup(Shader);
		CurTextIndex += 1;
		if(CurTextIndex > 19)
			CurTextIndex = 0;
		KillCounter2 -= 1;
		KillCounter += 1;
	}
	if(KillCounter > NumOfSymbols-1)
		KillCounter = 0;

	for(int i = 0; i < 20; i++)
	{
		TextObjects[i].Update(KillCounter);
	}
}



void EO_MovingText::Update(int CurCount)
{
	if(!InUse)
		return;
	if(OnceFix)
	{
		Counter = CurCount;
		OnceFix = false;
	}
	switch(KillSpree.Size)
	{
	case 0:
		Size = 50;
		break;
	case 1:
		Size = 75;
		break;
	case 2:
		Size = 100;
		break;
	}

	float DestY;
	float DestX;
	switch(KillSpree.Destination)
	{
		case 0:
			 DestY = refdef->y/2 - 200 + Counter*(Size + 5);
			 DestX = 40;
			break;
		case 1:
			 DestY = 40;
			 DestX = refdef->x/2 - 200 + Counter*(Size + 5);
			break;
		case 2:
			 DestY = refdef->y/2 - 200 + Counter*(Size + 5);
			 DestX = refdef->x - 40 - Size;
			break;
		case 3:
			 DestY = refdef->y - 40 - Size;
			 DestX = refdef->x/2 - 200 + Counter*(Size + 5);
			break;
			
	}
	float DeltaX = DestX - PosX;
	float DeltaY = DestY - PosY;

	PosX += DeltaX/10;
	PosY += DeltaY/10;

	if(KillSpree.Rotating)
	{
		if(Rotate > -360)
			Rotate -= 10;
	}
	
	EO_Draw.DrawShaderRot(PosX,PosY,Size,Size,WHITE_,KillIcon,Rotate);
}
void EO_MovingText::Setup(int Icon)
{
	
	

	Reset();
	
	switch(KillSpree.Origin)
	{
	case 0:
		PosY = refdef->y/2 - Size/2;
		PosX = refdef->x/2 - Size/2;
		break;
	case 1:
		PosY = 37.5;
		PosX = refdef->x - Size/2;
		break;
	case 2:
		PosY = 37.5;
		PosX = refdef->x/2 - Size/2;
		break;
	case 3:
		PosY = 37.5;
		PosX = 37.5;
		break;
	case 4:
		PosY = refdef->y/2 - Size/2;
		PosX = 37.5;
		break;
	case 5:
		PosY = refdef->y/2 - Size/2;
		PosX = refdef->x - Size/2;
		break;
	case 6:
		PosY = refdef->y - Size/2;
		PosX = refdef->x - Size/2;
		break;
	case 7:
		PosY = refdef->y/2 - Size/2;
		PosX = refdef->x - Size/2;
		break;
	case 8:
		PosY = refdef->y - Size/2;
		PosX = refdef->x - Size/2;
		break;
	}
	
	KillIcon = Icon;

	InUse = true;
	OnceFix = true;
}