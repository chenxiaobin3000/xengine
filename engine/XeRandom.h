/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-11- 3
 */

#ifndef _XERANDOM_H_
#define _XERANDOM_H_

namespace XE {

class CRandom
{
public:
	CRandom();
	virtual ~CRandom();

	void Init(unsigned int seed=0);

	// 返回随机数
	int Random();

	// 返回0-100之间随机数
	int Random_100();

	// 返回0-1之间随机数，精度：两位小数
	float Random_f();

	// 返回0到参数之间的随机数
	int Random_zero_up(int v);

	// 返回0到参数之间的随机数
	float Random_zero_up(float v);

	// 返回参数正负数之间的随机数
	int Random_down_up(int v);

	// 返回参数正负数之间的随机数
	float Random_down_up(float v);

private:
	// twister.cpp 初始化
	void init_genrand(unsigned long s);

	// twister.cpp 生成
	unsigned long genrand_int32(void);

private:
	static const int N = 624;

	/* the array for the state vector  */
	static unsigned long mt[N];

	/* mti==N+1 means mt[N] is not initialized */
	static int mti;
};

}

#endif //_XERANDOM_H_
