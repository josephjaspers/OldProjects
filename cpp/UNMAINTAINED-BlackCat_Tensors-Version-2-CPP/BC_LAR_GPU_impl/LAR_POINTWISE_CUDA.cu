#include "BLACKCAT_GPU_MATHEMATICS.cuh"


 __global__
void GPU_MATHEMATICS::power(float* s, const float* m1, const float* m2, unsigned sz)
{
	//NOT WRITTEN
}
 __global__
void GPU_MATHEMATICS::divide(float* s, const float* m1, const float* m2, unsigned sz)
{
	for (unsigned i = 0; i < sz; ++i)
	{
		s[i] = m1[i] / m2[i];
	}
}
 __global__
void GPU_MATHEMATICS::add(float* s, const float* m1, const float* m2, unsigned sz)
{

	for (unsigned i = 0; i < sz; ++i)
	{
		s[i] = m1[i] + m2[i];
	}
}
 __global__
void GPU_MATHEMATICS::subtract(float* s, const float* m1, const float* m2, unsigned sz)
{
	for (unsigned i = 0; i < sz; ++i)
	{
		s[i] = m1[i] - m2[i];
	}
}
 __global__
void GPU_MATHEMATICS::multiply(float* s, const float* m1, const float* m2, unsigned sz)
{
	for (unsigned i = 0; i < sz; ++i)
	{
		s[i] = m1[i] * m2[i];
	}
}
////Pointwise Scalar
 __global__
void GPU_MATHEMATICS::power(float *s, const float *m, float v, unsigned sz)
{
	 //NOT WRITTEN
}
 __global__
void GPU_MATHEMATICS::divide(float *s, const float *m, float v, unsigned sz)
{
	for (unsigned i = 0; i < sz; ++i)
	{
		s[i] = m[i] / v;
	}
}
 __global__
void GPU_MATHEMATICS::add(float *s, const float *m, float v, unsigned sz)
{
	for (unsigned i = 0; i < sz; ++i)
	{
		s[i] = m[i] + v;
	}
}
 __global__
void GPU_MATHEMATICS::subtract(float *s, const float *m, float v, unsigned sz)
{
	for (unsigned i = 0; i < sz; ++i)
	{
		s[i] = m[i] - v;
	}
}
 __global__
void GPU_MATHEMATICS::multiply(float *s, const float *m, float v, unsigned sz)
{
	for (unsigned i = 0; i < sz; ++i)
	{
		s[i] = m[i] * v;
	}
}

