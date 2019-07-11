#ifdef __CUDACC__
#ifndef MATHEMATICS_GPU_H_
#define MATHEMATICS_GPU_H_
#include "Mathematics_GPU_impl.cu"

#include <cmath>
#include <iostream>
#include <string>

#include <cuda_runtime_api.h>
#include <cuda.h>

#include "BC_PrintFunctions.h"

#include "../BlackCat_Internal_Definitions.h"
#include "BC_PrintFunctions.h"
#include <cublas_v2.h>

#include "Mathematics_GPU_impl.cu"

namespace BC {

namespace Constants {

static float* static_initialize(int sz, float value) {
	float* t;
	cudaMallocManaged((void**) &t, sizeof(float));
	cudaMemcpy(t, &value, sizeof(float), cudaMemcpyHostToDevice);
	return t;
}

static const float* const BC_ONE = static_initialize(1, 1);
static const float* const BC_ZERO = static_initialize(1, 1);

}

class GPU {
public:

	static int blocks(int size) {
		return (size + CUDA_BASE_THREADS - 1) / CUDA_BASE_THREADS;
	}
	static int threads() {
		return CUDA_BASE_THREADS;
	}

	template<typename T>
	static void initialize(T*& t, int sz) {
		cudaMalloc((void**) &t, sizeof(T) * sz);
	}

	template<class T>
	static void HostToDevice(T* t, const T* u, int size) {
		cudaMemcpy(t, u, sizeof(T) * size, cudaMemcpyHostToDevice);
	}
	template<class T>
	static void DeviceToHost(T* t, const T* u, int size) {
		cudaMemcpy(t, u, sizeof(T) * size, cudaMemcpyDeviceToHost);
	}

	template<typename T>
	static void unified_initialize(T*& t, int sz) {
		cudaMallocManaged((void**) &t, sizeof(T) * sz);
	}

	template<class T, class U>
	static void copy(T t, U u, int sz) {
		gpu_impl::copy<<<blocks(sz),threads()>>>(t, u, sz);
		cudaDeviceSynchronize();
	}

	template<class T, template<class...> class U, class... set>
	static void copy(T t, U<set...> u, int sz) {
		gpu_impl::copy<<<blocks(sz),threads()>>>(t, u, sz);
		cudaDeviceSynchronize();
	}

	template<class T>
	static void eval(T t, int sz) {
		gpu_impl::eval<<<blocks(sz),threads()>>>(t, sz);
		cudaDeviceSynchronize();
	}

	template<class U, class T, class V>
	static void scalarMul(U eval, T a, V b) {
		gpu_impl::scalarMul<<<1, 1>>>(eval, a, b);
		cudaDeviceSynchronize();
	}

	template<typename T>
	static void destroy(T* t) {
		cudaFree((void*)t);
	}
	template<typename T>
	static void destroy(T t) {
		throw std::invalid_argument("destruction on class object");
	}
	template<typename T, typename J>
	static void fill(T& t, const J j, int sz) {
		gpu_impl::fill<<<blocks(sz),threads()>>>(t, j, sz);
		cudaDeviceSynchronize();
	}

	template<typename T, typename J>
	static void fill(T& t, const J* j, int sz) {
		gpu_impl::fill<<<blocks(sz),threads()>>>(t, j, sz);
		cudaDeviceSynchronize();
	}
	template<typename T>
	static void zero(T& t, int sz) {
		gpu_impl::zero<<<blocks(sz),threads()>>>(t, sz);
		cudaDeviceSynchronize();
	}

	template<typename T, class J>
	static void randomize(T t, J lower_bound, J upper_bound, int sz) {
		gpu_impl::randomize<<<blocks(sz),threads()>>>(t, lower_bound, upper_bound, sz, rand());
		cudaDeviceSynchronize();
	}

	// Multiply the arrays A and B on GPU and save the result in C
	// C(m,n) = A(m,k) * B(k,n)
//A ld = m
//B ld = k
//C ld = m

	static void MatrixMul(bool transA, bool transB, const float *A, const float *B, float *C, const int m, const int n, const int k, const float* scalarA = nullptr, const float* scalarB = nullptr, int lda = 0, int ldb = 0, int ldc = 0) {
		if (lda == 0 ) lda = m;
		if (ldb == 0 ) ldb = k;
		if (ldc == 0 ) ldc = m;

		cublasHandle_t handle;
		cublasCreate(&handle);
		cublasSetPointerMode(handle, CUBLAS_POINTER_MODE_DEVICE);

		auto TRANS_A = transA ? CUBLAS_OP_T : CUBLAS_OP_N;
		auto TRANS_B = transA ? CUBLAS_OP_T : CUBLAS_OP_N;

		const float *const alpha = scalarA ? const_cast<float*>(scalarA) : Constants::BC_ONE;  //assign the scalar
		const float *const beta = scalarB ? const_cast<float*>(scalarB) : Constants::BC_ZERO;//same

		cublasSgemm(handle, TRANS_A, TRANS_B, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
		cudaDeviceSynchronize();
		cublasDestroy(handle);
	}

	template<class ranks>
	static int calc_size(ranks R, int order) {
		if (order == 0) {
			return 1;
		}

		int sz = 1;
		for (int i = 0; i < order; ++i) {
			sz *= R[i];
		}
		return sz;
	}

	template<class T, class RANKS>
	static void print(const T* ary, const RANKS ranks, int order, int print_length) {
		int sz = calc_size(ranks, order);
		T* print = new T[sz];

		cudaMemcpy(print, ary, sizeof(T) * sz, cudaMemcpyDeviceToHost);

		BC::print(print, ranks, order, print_length);
		delete[] print;
	}
	template<class T, class RANKS>
	static void printSparse(const T* ary, const RANKS ranks, int order, int print_length) {
		int sz = calc_size(ranks, order);
		T* print = new T[sz];

		cudaMemcpy(print, ary, sizeof(T) * sz, cudaMemcpyDeviceToHost);

		BC::print(print, ranks, order, print_length);
		delete[] print;
	}
};

}

#endif /* MATHEMATICS_CPU_H_ */

#endif //if cudda cc defined
