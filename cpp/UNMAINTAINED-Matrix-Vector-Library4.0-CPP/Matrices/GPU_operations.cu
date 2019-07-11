#include "GPU_operations.cuh"


__global__ void Matrices_gpu::exp(double * sz, double * m1, double * m2, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = pow(m1[i], m2[i]);
	}
}
__global__ void Matrices_gpu::multiply(double * sz, double * m1, double * m2, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = m1[i] * m2[i];
	}
}
__global__ void Matrices_gpu::divide(double * sz, double * m1, double * m2, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = m1[i] / m2[i];
	}
}
__global__ void Matrices_gpu::add(double * sz, double * m1, double * m2, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = m1[i] + m2[i];
	}
}
__global__ void Matrices_gpu::subtract(double * sz, double * m1, double * m2, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = m1[i] - m2[i];
	}
}
__global__ void Matrices_gpu::exp(double * sz, double * m, double v, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = pow(m[i], v);
	}
}
__global__ void Matrices_gpu::multiply(double * sz, double * m, double v, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = m[i] * v;
	}
}
__global__ void Matrices_gpu::divide(double * sz, double * m, double v, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = m[i] / v;
	}
}
__global__ void Matrices_gpu::add(double * sz, double * m, double v, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = m[i] + v;
	}
}
__global__ void Matrices_gpu::subtract(double * sz, double * m, double v, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = m[i] - v;
	}
}
__global__ void Matrices_gpu::dot(double * sz, double * m1, int mat1_length, int mat1_width, double * m2, int mat2_length, int mat2_width)
{
	int save_size = mat1_width * mat2_length;
	int stride_size = mat1_length;
	int n = save_size * stride_size;

	for (int i = 0; i < n; ++i)
		//for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x)
	{
		int save_index = floor((double)i / (mat1_length));
		int m1_index = i % mat1_length + floor((double)save_index / mat1_width) * mat1_length;
		int m2_index = (i % mat2_width) * mat2_length + (save_index % mat2_length);
		sz[save_index] += m1[m1_index] * m2[m2_index];
	}
}
__global__ void Matrices_gpu::dot_transpose(double * s, double * m1, int mat1_length, int mat1_width, double * m2, int mat2_length, int mat2_width)
{
	int save_size = mat1_length * mat2_length;
	int stride_size = mat2_width;
	int n = save_size * stride_size;

	for (int i = 0; i < n; ++i)
	{
		int save_index = floor((double)i / (mat1_width));
		int m1_index = (i % mat1_width) * mat1_length + ((int)floor((double)(i / mat1_length) / mat2_width));
		int m2_index = (i % mat2_width) * mat2_length + (save_index % mat2_length);

		s[save_index] += m1[m1_index] * m2[m2_index];
	}
}
__global__ void Matrices_gpu::dot_Vector_Vector(double * sz, double * v1, double * v2, int n)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			sz[i] += v1[i] * v2[j];
		}
	}
}
__global__ void Matrices_gpu::dot_Vector_Vector_inner(double * s, double * v1, double * v2, int n)
{
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		*s += v1[i] * v2[i];
	}
}

__global__ void Matrices_gpu::dot_Matrix_T_Matrix(double * sz, double * m1, int mat1_length, int mat1_width, double * m2, int mat2_length, int mat2_width)
{
	int save_size = mat1_width * mat2_length;
	int stride_size = mat1_length;
	int n = save_size * stride_size;

	for (int i = 0; i < n; ++i)
		//for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x)
	{
		int save_index = floor((double)i / (mat1_width));
		int m1_index = (i % mat1_width) * mat1_length + (save_index % mat1_length);
		int m2_index = (i % mat2_width) * mat2_length + (save_index % mat2_length);
		sz[save_index] += m1[m1_index] * m2[m2_index];
	}
}

__global__ void Matrices_gpu::dot_Matrix_Matrix_T(double * sz, double * m1, int mat1_length, int mat1_width, double * m2, int mat2_length, int mat2_width)
{
	int save_size = mat1_width * mat2_length;
	int stride_size = mat1_length;
	int n = save_size * stride_size;

	for (int i = 0; i < n; ++i)
		//for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x)
	{
		int save_index = floor((double)i / (mat1_length));
		int m1_index = i % mat1_length + floor((double)save_index / mat1_width) * mat1_length;
		int m2_index = i % mat2_length + floor((double)save_index / mat2_width) * mat2_length;
		sz[save_index] += m1[m1_index] * m2[m2_index];
	}
}

__global__ void Matrices_gpu::dot_Matrix_T_Matrix_T(double * sz, double * m1, int mat1_length, int mat1_width, double * m2, int mat2_length, int mat2_width)
{
	int save_size = mat1_width * mat2_length;
	int stride_size = mat1_length;
	int n = save_size * stride_size;

	for (int i = 0; i < n; ++i)
		//for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x)
	{
		int save_index = floor((double)i / (mat1_width));
		int m1_index = (i % mat1_width) * mat1_length + (save_index % mat1_length);
		int m2_index = i % mat2_length + floor((double)save_index / mat2_width) * mat2_length;
		sz[save_index] += m1[m1_index] * m2[m2_index];
	}//
}

__global__ void equal(int& boolean, double* m1, double* m2, int n) {
	//Grid stride
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		if (m1[i] != m2[i]) {
			boolean = 0;
			return;
		}
	}
}
__global__ void Matrices_gpu::copy(double* sz, double* m1, int n) {
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		sz[i] = m1[i];
	}
}
__global__ void Matrices_gpu::equal(bool * boolean, double * m1, double * m2, int n)
{
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		if (m1[i] != m2[i]) {
			boolean = false;
			return;
		}
	}
}
__global__ void Matrices_gpu::fill(double * m1, double value, int n)
{
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < n;
		i += blockDim.x * gridDim.x)
	{
		m1[i] = value;
	}
}

__global__ void Matrices_gpu::transpose(double * s, double * m, int x, int y)
{
	for (int i = 0; i < x * y; ++i) {
		s[i] = m[i % y * x + (int)floor((double)i / y) % x];
	}
}

__global__ void Matrices_gpu::reshape(double * s, double * m, int x, int y)
{
	for (int i = blockIdx.x * blockDim.x + threadIdx.x;
		i < (x * y);
		i += blockDim.x * gridDim.x)
	{
		for (int i = 0; i < x * y; ++i) {
			s[i] = m[i % y * x + (int)floor((double)i / y) % x];
		}
	}
}
