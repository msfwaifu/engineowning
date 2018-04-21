#define DotProduct(x,y) ((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorScale(v, s, o)    ((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))

#define M_PI 3.14159265358979323846
#define RADPI 57.295779513082f

#define PITCH 0

#define YAW 1

#define ROLL 2



class cMath {
public:
    double Radians ( float Degrees );
    void AngleVectors ( const float angles[3], float* forward, float* right, float* up );
    void VectorCopy ( float v1[3], float v2[3] );
    void VectorSubtract ( float* v1, float* v2, float* out );
    void VectorAngles ( const float value1[3], float angles[3] );
    void VectorAdd ( float* v1, float* v2, float* v3 );
    float GetDistance ( float A[3], float B[3] );
	float Get2DDistance(float Point1X,float Point1Y,float Point2X,float Point2Y);
	void VectorNormalize(float* inout);

	void VectorMA (Vector va, double scale, Vector vb, Vector vc);
	void AngletoForward( Vector AngleIn, Vector* out );
	void SCR_AdjustFrom640( float *x, float *y, float *w, float *h ) ;
};

extern cMath Math;