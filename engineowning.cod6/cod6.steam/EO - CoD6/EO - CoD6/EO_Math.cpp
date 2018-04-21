#include "EO_Main.h"


cMath Math;



float cMath::Get2DDistance(float Point1X,float Point1Y,float Point2X,float Point2Y)
{
	return sqrt( (Point1X - Point2X)*(Point1X - Point2X) + (Point1Y - Point2Y)*(Point1Y - Point2Y));

}

double cMath::Radians ( float Degrees ) {
    return  0.01745329238474369 * Degrees;
}
template <typename T> T CLAMP(const T& value, const T& low, const T& high) 
{
  return value < low ? low : (value > high ? high : value); 
}
void cMath::AngleVectors ( const float angles[3], float* forward, float* right, float* up ) {
    float angle;
    static float sr, sp, sy, cr, cp, cy, cpi = ( M_PI * 2 / 360 );

    angle = angles[1] * cpi;
    sy = sin ( angle );
    cy = cos ( angle );
    angle = angles[0] * cpi;
    sp = sin ( angle );
    cp = cos ( angle );
    angle = angles[2] * cpi;
    sr = sin ( angle );
    cr = cos ( angle );

    if ( forward ) {
        forward[0] = cp * cy;
        forward[1] = cp * sy;
        forward[2] = -sp;
    }

    if ( right ) {
        right[0] = ( -1 * sr * sp * cy + -1 * cr * -sy );
        right[1] = ( -1 * sr * sp * sy + -1 * cr * cy );
        right[2] = -1 * sr * cp;
    }

    if ( up ) {
        up[0] = ( cr * sp * cy + -sr * -sy );
        up[1] = ( cr * sp * sy + -sr * cy );
        up[2] = cr * cp;
    }
}
void cMath::VectorMA (Vector va, double scale, Vector vb, Vector vc)
{
	vc[0] = va[0] + scale*vb[0];
	vc[1] = va[1] + scale*vb[1];
	vc[2] = va[2] + scale*vb[2];
}


void cMath::VectorCopy ( float v1[3], float v2[3] ) {
    v2[0] = v1[0];
    v2[1] = v1[1];
    v2[2] = v1[2];
}

void cMath::VectorSubtract ( float* v1, float* v2, float* out ) {
    out[0] = v1[0] - v2[0];
    out[1] = v1[1] - v2[1];
    out[2] = v1[2] - v2[2];
}

void cMath::VectorAngles ( const float value1[3], float angles[3] ) {
    float   forward;
    float   yaw, pitch;

    if ( value1[1] == 0 && value1[0] == 0 ) {
        yaw = 0;
        if ( value1[2] > 0 ) {
            pitch = 90;
        } else {
            pitch = 270;
        }
    } else {
        if ( value1[0] ) {
            yaw = ( atan2 ( value1[1], value1[0] ) * 180 / M_PI );
        } else if ( value1[1] > 0 ) {
            yaw = 90;
        } else {
            yaw = 270;
        }
        if ( yaw < 0 ) {
            yaw += 360;
        }

        forward = sqrt ( value1[0] * value1[0] + value1[1] * value1[1] );
        pitch = ( atan2 ( value1[2], forward ) * 180 / M_PI );
        if ( pitch < 0 ) {
            pitch += 360;
        }
    }

    angles[0] = -pitch;
    angles[1] = yaw;
    angles[2] = 0;


}

void cMath::VectorAdd ( float* v1, float* v2, float* v3 ) {
    v3[0] = v1[0] * 2 + v2[0];
    v3[1] = v1[1] * 2 + v2[1];
    v3[2] = v1[2] * 2 + v2[2];
}

float cMath::GetDistance ( float A[3], float B[3] ) {
    float dx = A[0] - B[0];
    float dy = A[1] - B[1];
    float dz = A[2] - B[2];

    return ( float ) sqrt ( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) ) * 0.03048f;
}
#define VectorClear(x)			{x[0] = x[1] = x[2] = 0;}
void cMath::VectorNormalize(float* inout)
{
	float	length, ilength;

	length = sqrt (inout[0]*inout[0] + inout[1]*inout[1] + inout[2]*inout[2]);
	if (length == 0)
	{
		VectorClear (inout);
		return;
	}

	ilength = 1.0/length;
	inout[0] = inout[0]*ilength;
	inout[1] = inout[1]*ilength;
	inout[2] = inout[2]*ilength;

	return;
}
void cMath::AngletoForward( Vector AngleIn, Vector* out ) {
	float			angle;
	static float	sp, sy, cp, cy; // static to help MS compiler fp bugs
	
	angle = AngleIn[YAW] * ( M_PI * 2 / 360 );
	sy = sin( angle );
	cy = cos( angle );

	angle = AngleIn[PITCH]* ( M_PI * 2 / 360 );
	sp = sin( angle );
	cp = cos( angle );

	*out[0] = cp * cy;
	*out[1] = cp * sy;
	*out[2] = -sp ;
}

void cMath::SCR_AdjustFrom640( float *x, float *y, float *w, float *h ) {
	float	xscale;
	float	yscale;

#if 0
		// adjust for wide screens
		if ( cls.glconfig.vidWidth * 480 > cls.glconfig.vidHeight * 640 ) {
			*x += 0.5 * ( cls.glconfig.vidWidth - ( cls.glconfig.vidHeight * 640 / 480 ) );
		}
#endif

	// scale for screen sizes
		xscale = RefDef->iWidth / 640.0;
		yscale = RefDef->iHeight / 480.0;
	if ( x ) {
		*x *= xscale;
	}
	if ( y ) {
		*y *= yscale;
	}
	if ( w ) {
		*w *= xscale;
	}
	if ( h ) {
		*h *= yscale;
	}
}