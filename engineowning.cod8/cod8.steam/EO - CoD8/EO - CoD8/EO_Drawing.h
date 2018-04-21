
typedef float Color[4];

static Color RED = {1,0,0,1};
static Color RED_TRANS = {1,0,0,0.5};

static Color WHITE = {1,1,1,1};
static Color BLUE = {0,0,1,1};
static Color GREEN = {0,1,0,1};
static Color GREEN_TRANS = {0,1,0,0.5};
static Color MENUBG = {0,0,0,0.7};
static Color GRAY = {0.65, 0.65, 0.65, 1};
static Color BLACK = {0,0,0,1};

typedef int (*__cdecl DrawEngineText_406D70)(char* Text, int NumOfChars, void* Font, float X, float Y, float scaleX, float scaleY, float unk1, float* Color, int unk2);
extern DrawEngineText_406D70 DrawStringEngine;

typedef int ( __cdecl* DrawRotatedPic_52E380 ) ( ScreenMatrix* ptr, float x, float y, float w, float h, float angle, float* color, int shader );
extern DrawRotatedPic_52E380 DrawRotatedShader;

class EO_CDrawing
{
public:

	void DrawString( float x, float y, void* pFont, float fSize, float* pColor,  char* pText  );
	void DrawStringf(float x, float y, void* pFont, float fSize, float* pColor, char* pText, ...);
	void InitializeDrawing();
	void DrawShader( float x, float y, float w, float h, float *pColor, qhandle_t Shader );
	void DrawShaderRot( float x, float y, float w, float h, float *pColor, qhandle_t Shader,float Rotation );
	void DrawRect( float x, float y, float w, float h, float fThick, float* pColor );
	void DrawRectFilled( float x, float y, float w, float h, float fThick,float* backgroundColor, float* pColor );
	int StrWidth(char *szText,...);

} extern EO_Draw;


extern fontInfo_t *		normalFont;
extern fontInfo_t *		smalldevFont;
extern fontInfo_t *		consoleFont;
extern fontInfo_t *		bigFont;
extern fontInfo_t *		smallFont;
extern fontInfo_t *		boldFont;
extern fontInfo_t *		extrabigFont;
extern fontInfo_t *		objectiveFont;

extern qhandle_t		sWhite;
extern qhandle_t		GrenadeIcon;
extern qhandle_t		HelicopterIcon;
extern qhandle_t		HeadShotIcon;
extern qhandle_t		SuicideIcon;

extern fontInfo_t * (* R_RegisterFont )( char* pszFontName );
extern qhandle_t  (* R_RegisterShader )( char* ShaderName );
//comment