typedef float Color[4];

static Color RED = {1,0,0,1};
static Color BOX = {1,0,0,1};
static Color BOX_VIS = {0,1,0,1};

static Color WHITE = {1,1,1,1};
static Color BLUE = {0,0,1,1};
static Color GREEN = {0,1,0,1};
static Color GRAY = {0.65, 0.65, 0.65, 1};
static Color BLACK = {0,0,0,1};
static Color VISIBLE = {1,1,0,1};

typedef int (*__cdecl DrawStrechedPic_50A630)(float X, float Y, float w, float h, float TileX, float shaderwidth, float shaderheight,float TileY,float* color, int shader);
// TileX = value between 0.0 and 1.0f ... how much of the shader is cutted out on the X axis TileY is the same just with the Y axis.

typedef int (*__cdecl DrawEngineText_50AC40)( char* Text, int NumOfChars, void* Font, float X, float Y, float scaleX, float scaleY, float unk1, float* Color, int Type ); //Type 0 = normal 3 = shadowed


typedef int (*__cdecl RegisterShader_506B10)(char* name);

typedef void* (*__cdecl RegisterFont_4AC1D0)(char* name,int a2);




class EO_Drawing
{
public:
	
	DrawStrechedPic_50A630 DrawStrechShader;

	RegisterShader_506B10 RegisterShader;

	RegisterFont_4AC1D0 RegisterFont;

	DrawEngineText_50AC40 DrawEngineText;

	void* FontNormal;
	void* FontBig;
	void* FontSmall;
	void* ConsoleFont;
	int ShaderWhite;

	void Init();

	void DrawString(float X,float Y,void* font,Color col,char* txt)
	{
		DrawEngineText(txt,strlen(txt),font,X,Y,1,1,0,col,3);
	}
	void DrawRect(float X,float Y,float width,float height,Color Col)
	{
		DrawStrechShader(X,Y,width,height,0,1,1,0,Col,ShaderWhite);
	}
	void DrawBox ( float x, float y, float w, float h, float* color, float Size )
	{
		DrawRect(x,y,Size,h,color);
		DrawRect(x,y,w,Size,color);
		DrawRect(x,y+h,w,Size,color);
		DrawRect(x+w,y,Size,h+Size,color);
	}

};
extern EO_Drawing Draw;