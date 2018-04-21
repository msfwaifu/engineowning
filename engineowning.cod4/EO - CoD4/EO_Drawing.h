class EO_CDrawing
{
public:

	void DrawString( float x, float y, void* pFont, float fSize, float* pColor, const char* pText, ... );
	void InitializeDrawing();
	void DrawShader( float x, float y, float w, float h, float *pColor, qhandle_t Shader );
	void DrawRect( float x, float y, float w, float h, float fThick, float* pColor );
	int StrWidth(char *szText,...);
}extern EO_Draw;


extern fontInfo_t *		normalFont;
extern fontInfo_t *		smalldevFont;
extern fontInfo_t *		consoleFont;
extern fontInfo_t *		bigFont;
extern fontInfo_t *		smallFont;
extern fontInfo_t *		boldFont;
extern fontInfo_t *		extrabigFont;
extern fontInfo_t *		objectiveFont;

extern qhandle_t		sWhite;

extern fontInfo_t * (* R_RegisterFont )( char* FontName, signed int Unknown );
extern qhandle_t  (* R_RegisterShader )( char* ShaderName, signed int Unknown );