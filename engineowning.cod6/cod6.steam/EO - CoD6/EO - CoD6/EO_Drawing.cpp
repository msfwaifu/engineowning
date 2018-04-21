#include "EO_Main.h"

EO_Drawing Draw;




void EO_Drawing::Init()
{
	DrawStrechShader = (DrawStrechedPic_50A630)0x50A630;
	RegisterShader = (RegisterShader_506B10)0x506B10;
	RegisterFont = (RegisterFont_4AC1D0)0x4AC1D0;
	DrawEngineText = (DrawEngineText_50AC40)0x50AC40;

	

	FontNormal = RegisterFont("fonts/normalfont",0);
	FontBig = RegisterFont("fonts/bigfont",0);
	FontSmall = RegisterFont("fonts/smallfont",0);
	ConsoleFont = RegisterFont("fonts/consoleFont",0);
	

	ShaderWhite = RegisterShader("white");
}