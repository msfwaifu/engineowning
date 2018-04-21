
struct color_t  
{ 
    color_t(){} 

    color_t(float r, float g, float b, float a) 
    { 
        this->r = r; 
        this->g = g; 
        this->b = b; 
        this->a = a; 
    }

    color_t(int r, int g, int b, int a ) 
    { 
        this->r = ((float)r / 255.f); 
        this->g = ((float)g / 255.f); 
        this->b = ((float)b / 255.f); 
        this->a = ((float)a / 255.f); 
    } 

    float r, g, b, a; 
};

enum CVARTYPE
{
	Toggle,
	Plus,
	Invisible
};

struct CVar
{
	string Name;
	float Value;
	float Min;
	float Max;
	float Int;
	CVARTYPE Type;

	float Right()
	{
		if (Type == Plus)
		{
			if (Value < (Max - Int))
				Value += Int;
			else
				Value = Max;
		}
		else
		{
			if (Value == 1.0f)
				Value = 0.0f;
			else 
				Value = 1.0f;
		}
		return Value;
	}
	float Left()
	{
		if (Type == Plus)
		{
			if (Value > (Min + Int))
				Value -= Int;
			else
				Value = Min;
		}
		else
		{
			if (Value == 1.0f)
				Value = 0.0f;
			else 
				Value = 1.0f;
		}
		return Value;
	}
};
class CVarManager
{
public:
	vector<CVar*> Vars;
	int Count;
	CVar* AddVar(string Name, float Value=0.0f, float Min=0.0f, float Max = 1.0f,CVARTYPE Type = Toggle, float Int = 0.1f)
	{
		Count++;
		CVar* pVar = new CVar;
		pVar->Min = Min;
		pVar->Max = Max;
		pVar->Value = Value;
		pVar->Name = Name;
		pVar->Type = Type;
		pVar->Int = Int;
		Vars.push_back(pVar);
		return pVar;
	}
	CVar* FindVarByName(string Name)
	{
		for (int i=0;i<Count;i++)
		{
			if (Vars[i] && Vars[i]->Name.c_str() == Name.c_str())
				return Vars[i];
		}
		return NULL;
	}
	bool Write(string File)
	{
		FILE* pFile = fopen(File.c_str(),"w");
		if (pFile == NULL)
			return false;
		for (int i=0;i<Count;i++)
		{
			char Line[256];
			sprintf(Line,"%s=%.1f\n",Vars[i]->Name.c_str(),Vars[i]->Value);
			fwrite(Line,strlen(Line),1,pFile);
		}
		fclose(pFile);
		return true;
	}
	bool Read(string File)
	{
		FILE* pFile = fopen(File.c_str(),"r");
		if (pFile == NULL)
			return false;
		char Line[1024];
		while (fgets(Line,1024,pFile) != NULL)
		{
			char* Equal = strchr(Line,'=');
			if (Equal == NULL)
				continue;
			char Name[64];
			int Len = (Equal - Line);
			strncpy(Name,Line,Len);
			Name[Len] = '\0';
			CVar* pVar = FindVarByName(Name);
			if (pVar)
			{
				Equal += 0x1;
				pVar->Value = atof(Equal);
			}
		}
		return true;
	}
};



extern CVarManager Manager;
extern CVar*	save;
extern CVar*	Jugger;