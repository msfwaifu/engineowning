
#pragma once



class CRandomNumberGenerator {
	// Data
public:
	enum { N = 624 };       // length of state vector
	enum { SAVE = N + 1 };  // length of array for save()

protected:
	enum { M = 397 };  // period parameter

	UINT32 state[N];   // internal state
	UINT32 *pNext;     // next value to get from state
	int left;          // number of values left before reload needed

	//Methods
public:
	CRandomNumberGenerator(const UINT32& oneSeed);  // initialize with a simple uint32
	CRandomNumberGenerator(UINT32 *const bigSeed, UINT32 const seedLength = N);  // or an array
	CRandomNumberGenerator();                         // auto-initialize with /dev/urandom or time() and clock()
	CRandomNumberGenerator(const CRandomNumberGenerator&);            // prevent copy constructor
	CRandomNumberGenerator& operator=(const CRandomNumberGenerator&); // no-op operator=

	double rand();                          // real number in [0,1]
	double rand(const double& n);         // real number in [0,n]
	double randExc();                       // real number in [0,1)
	double randExc(const double& n);      // real number in [0,n)
	double randDblExc();                    // real number in (0,1)
	double randDblExc(const double& n);   // real number in (0,n)
	UINT32 randInt();                       // integer in [0,2^32-1]
	UINT32 randInt(int iMin, int iMax);     //integer between iMax & iMin
	byte randByte();
	UINT32 randInt(const UINT32& n);      // integer in [0,n] for n < 2^32
	double operator()() { return rand(); }  // same as rand()

	double rand53();

	double randNorm(const double& mean = 0.0, const double& variance = 0.0);

	void seed(const UINT32 oneSeed);
	void seed(UINT32 *const bigSeed, const UINT32 seedLength = N);
	void seed();

	void save(UINT32 *saveArray) const;
	void load(UINT32 *const loadArray);

protected:
	void initialize(const UINT32 oneSeed);
	void reload();
	UINT32 hiBit(const UINT32& u) const { return u & 0x80000000UL; }
	UINT32 loBit(const UINT32& u) const { return u & 0x00000001UL; }
	UINT32 loBits(const UINT32& u) const { return u & 0x7fffffffUL; }
	UINT32 mixBits(const UINT32& u, const UINT32& v) const
	{
		return this->hiBit(u) | this->loBits(v);
	}
	UINT32 twist(const UINT32& m, const UINT32& s0, const UINT32& s1) const
	{
		return m ^ (this->mixBits(s0, s1) >> 1) ^ UINT32(-(INT32)(this->loBit(s1) & 0x9908b0dfUL));
	}
	static UINT32 hash(time_t t, clock_t c);
};

extern CRandomNumberGenerator RandomNumberGenerator;


