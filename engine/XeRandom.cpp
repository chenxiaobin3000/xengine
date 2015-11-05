/*
 *  twister.cpp  Mex wrapper for the Mersenne Twister RNG.
 *
 *  Copyright 2009 The MathWorks, Inc.
 *  Revision: 1.0  Date: 2004/12/23
 *
 *  Requires MATLAB R13.

 *   TWISTER   Uniformly distributed pseudo-random numbers.
 *   R = TWISTER(N) returns an N-by-N matrix containing pseudo-random values
 *   drawn from a uniform distribution on the unit interval.  TWISTER(M,N) or
 *   TWISTER([M,N]) returns an M-by-N matrix.  TWISTER(M,N,P,...) or
 *   TWISTER([M,N,P,...]) generates an M-by-N-by-P-by-... array.  TWISTER with
 *   no arguments returns a scalar.  TWISTER(SIZE(A)) returns an array the same
 *   size as A.
 *
 *   TWISTER produces pseudo-random numbers using the Mersenne Twister
 *   algorithm by Nishimura and Matsumoto, and is an alternative to the
 *   built-in function RAND in MATLAB.  It creates double precision values in
 *   the closed interval [0, 1-2^(-53)], and can generate 2^19937 - 1 values
 *   before repeating itself.
 *
 *   The sequence of numbers generated is determined by the internal state of
 *   the generator.  Since MATLAB resets the state at start-up, the sequence of
 *   numbers generated will be the same in each session unless the state is
 *   changed.  Setting the generator to different states leads to unique
 *   computations, but does not improve any statistical properties.  Setting
 *   the generator to the same fixed state allows computations to be repeated.
 *
 *   TWISTER('state',J), where J is a scalar integer, initializes the state of
 *   the generator.  There is no simple connection between the sequence of
 *   random numbers generated from TWISTER('state',J) and TWISTER('state',J+1).
 *   TWISTER('state',0) resets the generator to its initial state.  J may also
 *   be an array of integers with length less than 625.
 *
 *   S = TWISTER('state') returns a 625-element vector of UINT32 values
 *   containing the current state of the uniform generator.
 *
 *   TWISTER('state',S), where S is the output of TWISTER('state'), sets the
 *   state of the generator to S.
 *
 *    Examples:
 *
 *       Three ways to initialize TWISTER differently each time:
 *          twister('state',sum(100*clock))
 *          twister('state',100*clock)
 *          twister('state',2^32*rand(n,1))  % where n < 625.
 *
 *       Generate 100 values, reset the state, and repeat the sequence:
 *          s = twister('state');
 *          u1 = twister(100,1);
 *          twister('state',s);
 *          u2 = twister(100,1); % contains exactly the same values as u1
 *
 *       Generate uniform values from the interval [a, b]:
 *          r = a + (b-a).*twister(100,1);
 *
 *       Generate integers uniform on the set 1:n:
 *          r = 1 + floor(n.*twister(100,1));
 *
 *       Generate standard normal random values using the inversion method:
 *          z = -sqrt(2).*erfcinv(2*twister(100,1));
 *
 *   Mex file derived from a copyrighted C program by Takuji Nishimura and
 *   Makoto Matsumoto.
 *
 *   Reference: M. Matsumoto and T. Nishimura, "Mersenne Twister: A
 *   623-Dimensionally Equidistributed Uniform Pseudo-Random Number Generator",
 *   ACM Transactions on Modeling and Computer Simulation, Vol. 8, No. 1,
 *   January 1998, pp 3--30.
 *
 *   See also RAND, RANDN.

 *   Note:  Initializing TWISTER to the scalar integer state 0 actually
 *   corresponds to the C call init_genrand(5489).
 */

#include "stdafx.h"
#include "XeRandom.h"

namespace XE {

/* Period parameters */
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

unsigned long CRandom::mt[N];

int CRandom::mti=N+1;

CRandom::CRandom() {

}

CRandom::~CRandom() {

}

void CRandom::Init(unsigned int seed) {
	if (0 == seed) {
		init_genrand((unsigned int)time(NULL));
	} else {
		init_genrand(seed);
	}
}

int CRandom::Random() {
	return (int)genrand_int32();
}

int CRandom::Random_100() {
	return Random() % 101;
}

float CRandom::Random_f() {
	return Random_100() * 0.01f;
}

int CRandom::Random_zero_up(int v) {
	return (int)(v * Random_f());
}

float CRandom::Random_zero_up(float v) {
	return v * Random_f();
}

int CRandom::Random_down_up(int v) {
	return (int)(v * 2 * (Random_f() - 0.5f));
}

float CRandom::Random_down_up(float v) {
	return v * 2 * (Random_f() - 0.5f);
}

void CRandom::init_genrand(unsigned long s) {
	mt[0]= s & 0xffffffffUL;
	for (mti=1; mti<N; mti++) {
		mt[mti] =
			(1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array mt[].                        */
		/* 2002/01/09 modified by Makoto Matsumoto             */
		mt[mti] &= 0xffffffffUL;
		/* for >32 bit machines */
	}
}

unsigned long CRandom::genrand_int32(void)
{
	unsigned long y;
	static unsigned long mag01[2]={0x0UL, MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= N) { /* generate N words at one time */
		int kk;

		if (mti == N+1)   /* if init_genrand() has not been called, */
			init_genrand(5489UL); /* a default initial seed is used */

		for (kk=0;kk<N-M;kk++) {
			y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
			mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (;kk<N-1;kk++) {
			y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
			mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
		mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

		mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return y;
}

}
