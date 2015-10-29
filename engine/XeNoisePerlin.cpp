#include "stdafx.h"
#include "XeNoisePerlin.h"

namespace XE {

#define INTERPOLATE CosineInterpolate

int CNoisePerlin::s_perm[512];

static const int p[] = {
	151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96,
	53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240,
	21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94,
	252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87,
	174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48,
	27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230,
	220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63,
	161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196,
	135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64,
	52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82,
	85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223,
	183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101,
	155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113,
	224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193,
	238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
	239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176,
	115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114,
	67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};

CNoisePerlin::CNoisePerlin(float persistence, int octaves, int randomSeed) : 
	m_fPersistence(persistence), m_nOctaves(octaves), m_nRandomSeed(randomSeed) {

}

CNoisePerlin::~CNoisePerlin() {

}

void CNoisePerlin::Init() {
	for (int i = 0; i < 256; i++) {
		s_perm[256 + i] = s_perm[i] = p[i];
	}
}

float CNoisePerlin::Generate(float x, float y) {
	float total = 0.0f;
	for(int i=0; i<m_nOctaves-1; ++i) {
		float frequency = pow(2.0f, i);
		float amplitude = pow(m_fPersistence,i);
		total += amplitude * InterpolatedNoise(x*frequency+m_nRandomSeed, 
			y*frequency+m_nRandomSeed);
	}
	return total;
}

float CNoisePerlin::Generate(float x, float y, float z) {
	float total = 0.0f;
	for(int i=0; i<m_nOctaves-1; ++i) {
		float frequency = pow(2.0f, i);
		float amplitude = pow(m_fPersistence,i);
		total += amplitude * Noise(x*frequency+m_nRandomSeed, 
			y*frequency+m_nRandomSeed, 0.5f+m_nRandomSeed);
	}
	return total;
}

float CNoisePerlin::GetPersistence() const {
	return m_fPersistence;
}

int CNoisePerlin::GetOctaves() const {
	return m_nOctaves;
}

int CNoisePerlin::GetRandomSeed() const {
	return m_nRandomSeed;
}

float CNoisePerlin::Noise(float x, float y, float z) {
	int X = (int) FastFloor(x) & 255; // FIND UNIT CUBE THAT
	int Y = (int) FastFloor(y) & 255; // CONTAINS POINT.
	int Z = (int) FastFloor(z) & 255;
	x -= FastFloor(x); // FIND RELATIVE X,Y,Z
	y -= FastFloor(y); // OF POINT IN CUBE.
	z -= FastFloor(z);
	float u = Fade(x); // COMPUTE FADE CURVES
	float v = Fade(y); // FOR EACH OF X,Y,Z.
	float w = Fade(z);
	int A = s_perm[X] + Y; // HASH COORDINATES OF
	int AA = s_perm[A] + Z; // THE 8 CUBE CORNERS
	int AB = s_perm[A + 1] + Z;
	int B = s_perm[X + 1] + Y;
	int BA = s_perm[B] + Z;
	int BB = s_perm[B + 1] + Z;

	return Lerp(w,
		Lerp(v, Lerp(u, Grad(s_perm[AA], x, y, z), // AND ADD
		Grad(s_perm[BA], x - 1, y, z)), // BLENDED
		Lerp(u, Grad(s_perm[AB], x, y - 1, z), // RESULTS
		Grad(s_perm[BB], x - 1, y - 1, z))), // FROM 8
		Lerp(v,
		Lerp(u, Grad(s_perm[AA + 1], x, y, z - 1), // CORNERS
		Grad(s_perm[BA + 1], x - 1, y, z - 1)), // OF CUBE
		Lerp(u, Grad(s_perm[AB + 1], x, y - 1, z - 1),
		Grad(s_perm[BB + 1], x - 1, y - 1, z - 1))));
}

int CNoisePerlin::FastFloor(float x) {
	return x > 0 ? (int) x : (int) x - 1;
}

float CNoisePerlin::Fade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float CNoisePerlin::Lerp(float t, float a, float b) {
	return a + t * (b - a);
}

float CNoisePerlin::Grad(int hash, float x, float y, float z) {
	int h = hash & 15; // CONVERT LO 4 BITS OF HASH CODE
	float u = h < 8 ? x : y; // INTO 12 GRADIENT DIRECTIONS.
	float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float CNoisePerlin::LinearInterpolate(float a, float b, float x) {
	return (float)(a*(1-x) + b*x);
}

float CNoisePerlin::CosineInterpolate(float a, float b, float x) {
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * 0.5;
	return (float)(a*(1-f) + b*f);
}

float CNoisePerlin::Noise(int x, int y) {
	int n = x + y * 57;
	n = (n << 13) ^ n;
	return (float)(1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

float CNoisePerlin::SmoothNoise(int x, int y) {
	float corners = (Noise(x-1, y-1) + Noise(x+1, y-1) + 
		Noise(x-1, y+1) + Noise(x+1, y+1)) / 16;
	float sides   = (Noise(x-1, y) + Noise(x+1, y) + 
		Noise(x, y-1) + Noise(x, y+1)) / 8;
	float center  = Noise(x, y) / 4;
	return corners + sides + center;
}

float CNoisePerlin::InterpolatedNoise(float x, float y) {
	int integerX = (int)x;
	float fractionalX = x - integerX;

	int integerY = (int)y;
	float fractionalY = y - integerY;

	float v1 = SmoothNoise(integerX,     integerY);
	float v2 = SmoothNoise(integerX + 1, integerY);
	float v3 = SmoothNoise(integerX,     integerY + 1);
	float v4 = SmoothNoise(integerX + 1, integerY + 1);

	float i1 = INTERPOLATE(v1, v2, fractionalX);
	float i2 = INTERPOLATE(v3, v4, fractionalX);

	return INTERPOLATE(i1, i2, fractionalY);
}

}
