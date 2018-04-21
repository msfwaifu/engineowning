#include "EO_Main.h"

EO_CDrawing EO_Draw;


fontInfo_t *		normalFont			= NULL;
fontInfo_t *		smalldevFont		= NULL;
fontInfo_t *		consoleFont			= NULL;
fontInfo_t *		bigFont				= NULL;
fontInfo_t *		smallFont			= NULL;
fontInfo_t *		boldFont			= NULL;
fontInfo_t *		extrabigFont		= NULL;
fontInfo_t *		objectiveFont		= NULL;

qhandle_t			sWhite				= NULL;
qhandle_t			GrenadeIcon			= NULL;
qhandle_t			HelicopterIcon		= NULL;
qhandle_t			HeadShotIcon		= NULL;
qhandle_t			SuicideIcon			= NULL;

qhandle_t    ( * R_RegisterShader )( char* ShaderName ) = ( int ( __cdecl* )( char* ))0x55FFC0;
fontInfo_t*  ( *R_RegisterFont )( char* pszFontName ) = ( fontInfo_t* ( __cdecl* )( char* ) )0x485440;

int (*CG_DrawEngineText)(char* Text, int a2, void* Font, float x, float y, float a6, float a7, float a8, float* pColor, int a10) = (int(__cdecl *)(char*,int,void*,float,float,float,float,float,float*,int ))0x406D70;
SIZE_T (*CG_DrawStretchPic)(float x, float y, float w, float h, float s1, float t1, float s2, float t2, float* color, qhandle_t hShader) = ( SIZE_T (__cdecl *)(float, float, float, float, float, float, float, float, vec3_t, qhandle_t  ))0x4EE7F0;

DrawRotatedPic_52E380 DrawRotatedShader = (DrawRotatedPic_52E380)0x52E380;

void EO_CDrawing::InitializeDrawing()
{
	normalFont			= R_RegisterFont("fonts/normalfont");
	smalldevFont		= R_RegisterFont("fonts/smalldevfont");
	consoleFont			= R_RegisterFont("fonts/consolefont");
	bigFont				= R_RegisterFont("fonts/bigfont");
	smallFont			= R_RegisterFont("fonts/smallfont");
	boldFont			= R_RegisterFont("fonts/boldfont");
	extrabigFont		= R_RegisterFont("fonts/extrabigfont");
	objectiveFont		= R_RegisterFont("fonts/objectivefont");

	sWhite				= R_RegisterShader("white");
	GrenadeIcon			= R_RegisterShader("hud_grenadeicon");
	HelicopterIcon		= R_RegisterShader("remotemissile_target_hostile");
	HeadShotIcon		= R_RegisterShader("killiconheadshot");
	SuicideIcon			= R_RegisterShader("killiconsuicide");
}

DrawEngineText_406D70 DrawStringEngine = (DrawEngineText_406D70)0x406D70;

void EO_CDrawing::DrawString( float x, float y, void* pFont, float fSize, float* pColor,  char* pText )
{
	DrawStringEngine(pText,strlen(pText),pFont,x,y,1.0f,1.0f,0,pColor,3);
}

void EO_CDrawing::DrawStringf(float x, float y, void* pFont, float fSize, float* pColor, char* pText, ...)
{

	va_list va;
	va_start(va, pText);

	char szBuffer[1025];

	vsnprintf(szBuffer,1024, pText, va);

	DrawStringEngine(szBuffer, strlen(szBuffer), pFont, x, y, 1.0f, 1.0f, 0, pColor, 3);

}

void EO_CDrawing::DrawShader( float x, float y, float w, float h, float *pColor, qhandle_t Shader )
{
	//DrawStretchPic( x, y, w, h, 0.0f, 0.0f, 1.0f, 1.0f, pColor, Shader);
	CG_DrawStretchPic((float)x,(float)y,(float)w,(float)h,0,0,1,1,pColor,Shader);
}
void EO_CDrawing::DrawShaderRot( float x, float y, float w, float h, float *pColor, qhandle_t Shader,float Rotation )
{
	DrawRotatedShader(GSM(),x,y,w,h,Rotation,pColor,Shader);
}
void EO_CDrawing::DrawRect( float x, float y, float w, float h, float fThick, float* pColor )
{
	DrawShader( x, y, w, fThick, pColor, sWhite );
	y += fThick;
	DrawShader( x, y, fThick, h - ( 2 * fThick ), pColor, sWhite );
	y += ( h - ( 2 * fThick ) );
	DrawShader( x, y, w, fThick, pColor, sWhite );
	y -= ( h - ( 2 * fThick ) );
	x += ( w - fThick );
	DrawShader( x, y, fThick, h - ( 2 * fThick ), pColor, sWhite);
}
void EO_CDrawing::DrawRectFilled( float x, float y, float w, float h, float fThick,float* bgColor, float* pColor )
{
	DrawShader(x,y,w,h,bgColor,sWhite);

	DrawShader( x, y, w, fThick, pColor, sWhite );
	y += fThick;
	DrawShader( x, y, fThick, h - ( 2 * fThick ), pColor, sWhite );
	y += ( h - ( 2 * fThick ) );
	DrawShader( x, y, w, fThick, pColor, sWhite );
	y -= ( h - ( 2 * fThick ) );
	x += ( w - fThick );
	DrawShader( x, y, fThick, h - ( 2 * fThick ), pColor, sWhite);
	
}
int EO_CDrawing::StrWidth(char *szText,...)
{
	char szBuf[300];
	va_list va_alist;
	va_start(va_alist,szText);
	vsprintf_s(szBuf,szText,va_alist);
	va_end(va_alist);

	return (strlen(szBuf)*6);
}
//comment