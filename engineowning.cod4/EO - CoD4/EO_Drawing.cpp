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

fontInfo_t * ( *R_RegisterFont )( char* FontName, signed int Unknown )	 = ( fontInfo_t * (__cdecl*) ( char *, signed int ) )0x005F1EC0;
qhandle_t    ( *R_RegisterShader )( char* ShaderName, signed int Unknown ) = ( int (__cdecl*)( char *, signed int ) ) 0x005F2A80;

void EO_CDrawing::InitializeDrawing()
{
	normalFont			= R_RegisterFont("fonts/normalfont", 1);
	smalldevFont		= R_RegisterFont("fonts/smalldevfont", 1);
	consoleFont			= R_RegisterFont("fonts/consolefont", 1);
	bigFont				= R_RegisterFont("fonts/bigfont", 1);
	smallFont			= R_RegisterFont("fonts/smallfont", 1);
	boldFont			= R_RegisterFont("fonts/boldfont", 1);
	extrabigFont		= R_RegisterFont("fonts/extrabigfont", 1);
	objectiveFont		= R_RegisterFont("fonts/objectivefont", 1);

	sWhite			= R_RegisterShader("white", 7);
}

void DrawStringEngine( float x, float y, void* pFont, char* pText, float* pColor, float sX, float sY, float f1, float f2 ) 
{	
	DWORD dwCall = 0x005F6B00;
	
	__asm
	{ 
		push	3
		push	f1
		push	sY
		push	sX
		push	y
		push	x 
		push	pFont
		push	0x7FFFFFFF
		push	pText
		mov		ecx, pColor
		call	[dwCall]
		add		esp, 0x28
	}
}

void EO_CDrawing::DrawString( float x, float y, void* pFont, float fSize, float* pColor, const char* pText, ... )
{
	char szBuffer[512] = {0};
	va_list vaList;

	va_start(vaList, pText);
		vsprintf(szBuffer, pText, vaList);
	va_end(vaList);

	DrawStringEngine( x, y, pFont, szBuffer, pColor, fSize, fSize, 0.0f, 0.0f );
}

void DrawStretchPic(float x, float y, float w, float h, float uk1, float uk2, float uk3, float uk4, float* pColor, int iMaterial )
{
	DWORD dwCall = 0x005F65F0;

	__asm
	{
		push	pColor
		push	uk4
		push	uk3
		push	uk2
		push	uk1
		push	h
		push	w
		push	y
		push	x
		mov		eax, iMaterial
		call	[dwCall]
		add		esp, 0x24
	}
}

void EO_CDrawing::DrawShader( float x, float y, float w, float h, float *pColor, qhandle_t Shader )
{
	DrawStretchPic( x, y, w, h, 0.0f, 0.0f, 1.0f, 1.0f, pColor, Shader);
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
int EO_CDrawing::StrWidth(char *szText,...)
{
	char szBuf[300];
	va_list va_alist;
	va_start(va_alist,szText);
	vsprintf_s(szBuf,szText,va_alist);
	va_end(va_alist);

	return (strlen(szBuf)*6);
}
