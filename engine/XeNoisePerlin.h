/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-23
 */

#ifndef _XENOISEPERLIN_H_
#define _XENOISEPERLIN_H_

namespace XE {

// JAVA REFERENCE IMPLEMENTATION OF IMPROVED NOISE - COPYRIGHT 2002 KEN PERLIN.
// 来源：ken perlin自己改进的算法java版
class CNoisePerlin
{
public:
	CNoisePerlin(float persistence=1.0f, int octaves=2, int randomSeed=0);
	virtual ~CNoisePerlin();

	static void Init();

	// Hugo Elias版
	float Generate(float x, float y);

	// 原版
	float Generate(float x, float y, float z);

	float GetPersistence() const;

	int GetOctaves() const;

	int GetRandomSeed() const;

private:
	float Noise(float x, float y, float z);

	int FastFloor(float x);

	float Fade(float t);

	float Lerp(float t, float a, float b);

	float Grad(int hash, float x, float y, float z);

	// 线性插值
	float LinearInterpolate(float a, float b, float x);

	// 余弦插值
	float CosineInterpolate(float a, float b, float x);

	float Noise(int x, int y);

	float SmoothNoise(int x, int y);

	float InterpolatedNoise(float x, float y);

private:
	static int					s_perm[512];

	float						m_fPersistence;			// 持续性，生成振幅
	int							m_nOctaves;				// 八度
	int							m_nRandomSeed;			// 随机种子
};


}

#endif //_XENOISEPERLIN_H_
