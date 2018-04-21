#include "EO_Main.h"

#pragma region CRand_t

CRandomNumberGenerator RandomNumberGenerator;

inline CRandomNumberGenerator::CRandomNumberGenerator(const CRandomNumberGenerator&)
{
	this->seed();
}

inline CRandomNumberGenerator& CRandomNumberGenerator::operator=(const CRandomNumberGenerator&)
{
	return *this;
}

inline CRandomNumberGenerator::CRandomNumberGenerator(const UINT32& oneSeed)
{
	this->seed(oneSeed);
}

inline CRandomNumberGenerator::CRandomNumberGenerator(UINT32 *const bigSeed, const UINT32 seedLength)
{
	this->seed(bigSeed, seedLength);
}

inline CRandomNumberGenerator::CRandomNumberGenerator()
{
	this->seed();
}

inline double  CRandomNumberGenerator::rand()
{
	return double(this->randInt()) * (1.0 / 4294967295.0);
}

inline double CRandomNumberGenerator::rand(const double& n)
{

	return this->rand() * n;
}

inline double CRandomNumberGenerator::randExc()
{
	return double(this->randInt()) * (1.0 / 4294967296.0);
}

inline double  CRandomNumberGenerator::randExc(const double& n)
{
	return this->randExc() * n;
}

inline double  CRandomNumberGenerator::randDblExc()
{
	return (double(this->randInt()) + 0.5) * (1.0 / 4294967296.0);
}

inline double  CRandomNumberGenerator::randDblExc(const double& n)
{
	return this->randDblExc() * n;
}

inline double  CRandomNumberGenerator::rand53()
{
	UINT32 a = this->randInt() >> 5, b = this->randInt() >> 6;
	return (a * 67108864.0 + b) * (1.0 / 9007199254740992.0);  // by Isaku Wada
}

inline double  CRandomNumberGenerator::randNorm(const double& mean, const double& variance)
{
	// Return a real number from a normal (Gaussian) distribution with given
	// mean and variance by Box-Muller method
	double r = sqrt(-2.0 * log(1.0 - this->randDblExc())) * variance;
	double phi = 2.0 * 3.14159265358979323846264338328 * this->randExc();
	return mean + r * cos(phi);
}

UINT32  CRandomNumberGenerator::randInt()
{
	// Pull a 32-bit integer from the generator state
	// Every other access function simply transforms the numbers extracted here

	if (this->left == 0) this->reload();
	this->left--;

	register UINT32 s1;
	s1 = *this->pNext++;
	s1 ^= (s1 >> 11);
	s1 ^= (s1 << 7) & 0x9d2c5680UL;
	s1 ^= (s1 << 15) & 0xefc60000UL;
	return (s1 ^ (s1 >> 18));
}

UINT32  CRandomNumberGenerator::randInt(int iMin, int iMax)
{
	return this->randInt() % (iMax + 1 - iMin) + iMin;
}

byte  CRandomNumberGenerator::randByte()
{
	return static_cast<byte>(this->randInt(0x0, 0xFF));
}

UINT32  CRandomNumberGenerator::randInt(const UINT32& n)
{

	UINT32 used = n;
	used |= used >> 1;
	used |= used >> 2;
	used |= used >> 4;
	used |= used >> 8;
	used |= used >> 16;

	// Draw numbers until one is found in [0,n]
	UINT32 i;
	do
	i = this->randInt() & used;  // toss unused bits to shorten search
	while (i > n);
	return i;
}

inline void  CRandomNumberGenerator::seed(const UINT32 oneSeed)
{
	// Seed the generator with a simple uint32
	this->initialize(oneSeed);
	this->reload();
}

inline void  CRandomNumberGenerator::seed(UINT32 *const bigSeed, const UINT32 seedLength)
{
	this->initialize(19650218UL);
	register int i = 1;
	register UINT32 j = 0;
	register int k = (this->N > int(seedLength) ? this->N : int(seedLength));
	for (; k; --k)
	{
		this->state[i] =
			this->state[i] ^ ((this->state[i - 1] ^ (this->state[i - 1] >> 30)) * 1664525UL);
		this->state[i] += (bigSeed[j] & 0xffffffffUL) + j;
		this->state[i] &= 0xffffffffUL;
		++i;  ++j;
		if (i >= this->N) { this->state[0] = this->state[this->N - 1];  i = 1; }
		if (j >= seedLength) j = 0;
	}
	for (k = this->N - 1; k; --k)
	{
		this->state[i] =
			this->state[i] ^ ((this->state[i - 1] ^ (this->state[i - 1] >> 30)) * 1566083941UL);
		this->state[i] -= i;
		this->state[i] &= 0xffffffffUL;
		++i;
		if (i >= this->N) { this->state[0] = this->state[this->N - 1];  i = 1; }
	}
	this->state[0] = 0x80000000UL;  // MSB is 1, assuring non-zero initial array
	this->reload();
}

inline void  CRandomNumberGenerator::seed()
{
	// Seed the generator with hash of time() and clock() values
	this->seed(this->hash(time(NULL), clock()));
}

inline void  CRandomNumberGenerator::initialize(const UINT32 seed)
{
	register UINT32 *s = this->state;
	register UINT32 *r = this->state;
	register int i = 1;
	*s++ = seed & 0xffffffffUL;
	for (; i < this->N; ++i)
	{
		*s++ = (1812433253UL * (*r ^ (*r >> 30)) + i) & 0xffffffffUL;
		r++;
	}
}

inline void  CRandomNumberGenerator::reload()
{
	// Generate N new values in state
	// Made clearer and faster by Matthew Bellew (matthew.bellew@home.com)
	register UINT32 *p = this->state;
	register int i;
	for (i = this->N - this->M; i--; ++p)
		*p = this->twist(p[this->M], p[0], p[1]);
	for (i = this->M; --i; ++p)
		*p = this->twist(p[this->M - this->N], p[0], p[1]);
	*p = this->twist(p[this->M - this->N], p[0], this->state[0]);

	this->left = this->N, this->pNext = this->state;
}

inline UINT32  CRandomNumberGenerator::hash(time_t t, clock_t c)
{
	// Get a uint32 from t and c
	// Better than uint32(x) in case x is floating point in [0,1]
	// Based on code by Lawrence Kirby (fred@genesis.demon.co.uk)

	static UINT32 differ = 0;  // guarantee time-based seeds will change

	UINT32 h1 = 0;
	unsigned char *p = (unsigned char *)&t;
	for (size_t i = 0; i < sizeof(t); ++i)
	{
		h1 *= UCHAR_MAX + 2U;
		h1 += p[i];
	}
	UINT32 h2 = 0;
	p = (unsigned char *)&c;
	for (size_t j = 0; j < sizeof(c); ++j)
	{
		h2 *= UCHAR_MAX + 2U;
		h2 += p[j];
	}
	return (h1 + differ++) ^ h2;
}

inline void  CRandomNumberGenerator::save(UINT32* saveArray) const
{
	register UINT32 *sa = saveArray;
	register const UINT32 *s = this->state;
	register int i = this->N;
	for (; i--; *sa++ = *s++) {}
	*sa = this->left;
}

inline void  CRandomNumberGenerator::load(UINT32 *const loadArray)
{
	register UINT32 *s = this->state;
	register UINT32 *la = loadArray;
	register int i = this->N;
	for (; i--; *s++ = *la++) {}
	this->left = *la;
	this->pNext = &this->state[this->N - this->left];
}
#pragma endregion

