/*
 * BC_Mathematics_CPU.h
 *
 *  Created on: Dec 1, 2017
 *      Author: joseph
 */

#ifndef MATHEMATICS_CPU_H_
#define MATHEMATICS_CPU_H_

#include <cmath>
#include <iostream>
#include <string>

#include "BC_PrintFunctions.h"
#include "cblas.h"


namespace BC {


class CPU {
public:
	/*
	 * T -- An object (Generally an array) with a functional [] operator
	 * J -- Either a value on the stack to be assigned or another array similar to above.
	 *
	 * J -- may also be a single value passed by pointer, certains methods are overloaded to handle these instance
	 */

	//destructor - no destructor are for controlling destruction of the pointer
	template<typename T>
	static void initialize(T*& t, int sz) {
		t = new T[sz];
	}
	template<typename T>
	static void unified_initialize(T*& t, int sz) {
		t = new T[sz];
	}
	template<class T, class U>
	static void HostToDevice(T t, U u, int size) {
		copy(t, u, size);
	}
	template<class T, class U>
	static void DeviceToHost(T t, U u, int size) {
		copy(t, u, size);
	}


	template<typename T>
	static void destroy(T* t) {
		delete[] t;
	}
	template<typename T, typename J>
	static void fill(T& t, const J j, int sz) {
#pragma omp parallel for
		for (int i = 0; i < sz; ++i) {
			t[i] = j;
		}
#pragma omp barrier
	}

	template<typename T>
	static void zeros(T& t, int sz) {
#pragma omp parallel for
		for (int i = 0; i < sz; ++i) {
			t[i] = 0;
		}
#pragma omp barrier
	}

	template<typename T, typename J>
	static void fill(T& t, const J* j, int sz) {
#pragma omp parallel for
		for (int i = 0; i < sz; ++i) {
			t[i] = *j;
		}
#pragma omp barrier
	}

	template<typename T>
	static void eval(T t, int sz) {
#pragma omp parallel for
		for (int i = 0; i < sz; ++i) {
			t[i];
		}
#pragma omp barrier
	}
	template<typename T, typename J>
	static void set_heap(T *t, J *j) {
		*t = *j;
	}
	template<typename T, typename J>
	static void set_stack(T *t, J j) {
		*t = j;
	}

	template<typename T>
	static void zero(T t, int sz) {
#pragma omp parallel for
		for (int i = 0; i < sz; ++i) {
			t[i] = 0;
		}
#pragma omp barrier
	}
	template<typename T, typename J>
	static void copy(T t, const J j, int sz) {
		if (sz < BC_CPU_SINGLE_THREAD_THRESHOLD) {
			copy_single_thread(t, j, sz);
			return;
		}
#pragma omp parallel for
		for (int i = 0; i < sz; ++i) {
			t[i] = j[i];
		}
#pragma omp barrier
	}

	template<typename T, typename J>
	static void copy_single_thread(T& t, const J& j, int sz) {
		for (int i = 0; i < sz; ++i) {
			t[i] = j[i];
		}
	}
	template<typename T, typename J>
	static void copyHostToDevice(T t, J j, int sz) {
#pragma omp parallel for
		for (int i = 0; i < sz; ++i) {
			t[i] = j[i];
		}
#pragma omp barrier
	}

	template<typename T, typename J>
	static void randomize(T t, J lower_bound, J upper_bound, int sz) {
#pragma omp parallel for
		for (int i = 0; i < sz; ++i) {
			t[i] = ((double) (rand() / ((double) RAND_MAX + 1)) * (upper_bound - lower_bound)) + lower_bound;

		}
#pragma omp barrier
	}
	template<class T, class RANKS>
	static void print(const T ary, const RANKS ranks, int order, int print_length) {
		BC::print(ary, ranks, order, print_length);
	}

	template<class T, class RANKS>
	static void printSparse(const T ary, const RANKS ranks, int order, int print_length) {
		BC::printSparse(ary, ranks, order, print_length);
	}



	/*
	 * a = M x K
	 * b = K x N
	 * c = M x N
	 */

	//
public:
	template<class U, class T, class V>
	static void scalarMul(U eval, T a, V b) {
		*eval = a[0] * b[0];
	}

	static void MatrixMul(bool transA, bool transB, const float* A, const float* B, float* C, int m, int n, int k,
			const float* scalarA = nullptr, const float* scalarB = nullptr,  int lda = 0, int ldb =0, int ldc =0) {

		 auto TRANS_A =  transA ? CblasTrans : CblasNoTrans;
		 auto TRANS_B =  transB ? CblasTrans : CblasNoTrans;

		  if (lda == 0 ) lda = m;
		  if (ldb == 0 ) ldb = n;
		  if (ldc == 0 ) ldc = m;

	      const float beta   =  scalarB ? *scalarB : 0;
		  const float alpha  =  scalarA ? *scalarA : 1;

		cblas_sgemm(CblasColMajor, TRANS_A, TRANS_B, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
	}
	static void MatrixMul(bool transA, bool transB, const double* A, const double* B, double* C, int m, int n, int k,
			const double* scalarA = nullptr, const double* scalarB = nullptr, int lda = 0, int ldb = 0, int ldc = 0) {

		 auto TRANS_A =  transA ? CblasTrans : CblasNoTrans;
		 auto TRANS_B =  transB ? CblasTrans : CblasNoTrans;

		  if (lda == 0 ) lda = m;
		  if (ldb == 0 ) ldb = n;
		  if (ldc == 0 ) ldc = m;


		const double beta   =  scalarB ? *scalarB : 0.0;
		const double alpha  =  scalarA ? *scalarA : 1.0;

		//		std::cout << " beta = " << beta << " alpha = " << alpha << std::endl;
		//		  std::cout << "m  n k " << m << n << k << std::endl;
		//		  std::cout << "m  n k " << lda << ldb << ldc << std::endl;
		//
		//		  std::cout << "A " << std::endl;
		//		  for (int i = 0; i < 6; ++i) {
		//			  std::cout << A[i] << " ";
		//		  }
		//		  std::cout << std::endl;
		//		  if (transA) {
		//			   std::cout << " trans " << std::endl;
		//		  }
		cblas_dgemm(CblasColMajor, TRANS_A, TRANS_B, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
	}
};

}
#endif /* MATHEMATICS_CPU_H_ */


//	//This doesn't actually give a shit if transposed --- just using this till I integrate blas
//	template<class A, class B, class C, class D, class E>
//	static void MatrixMul(bool transA, bool transB, const A a, const B b,  C c, int m, int n, int k, const D scalarA = nullptr, const E scalarB = nullptr,  int lda = 0, int ldb = 0, int ldc = 0) {
//		if (lda == 0 and ldb == 0 and ldc ==0) {
//			lda = m;
//			ldb = n;
//			ldc = m;
//		}
//
//		typename MTF::remove_mods<A>::type alpha =  scalarA == nullptr  ? 1 : *scalarA;
//		typename MTF::remove_mods<B>::type beta  =  scalarB == nullptr  ? 1 : *scalarB;
//
//#pragma omp parallel for
//		for (int z = 0; z < k; ++z) {
//			for (int x = 0; x < n; ++x) {
//				for (int y = 0; y < m; ++y) {
//					c[z * ldc + y] += (a[x * lda + y]* alpha) * (b[z * ldb + x] * beta);
//
//				}
//			}
//		}
//#pragma omp barrier
//	}
//
//	template<class T>
//	static void MatrixMul(bool transA, bool transB, const T a, const T b,  T c, int m, int n, int k, const T scalarA = nullptr, const T scalarB = nullptr,  int lda = 0, int ldb = 0, int ldc = 0) {
//		if (lda == 0 and ldb == 0 and ldc ==0) {
//			lda = m;
//			ldb = n;
//			ldc = m;
//		}
//
//		typename MTF::remove_mods<T>::type alpha =  scalarA == nullptr  ? 1 : *scalarA;
//		typename MTF::remove_mods<T>::type beta  =  scalarB == nullptr  ? 1 : *scalarB;
//
//#pragma omp parallel for
//		for (int z = 0; z < k; ++z) {
//			for (int x = 0; x < n; ++x) {
//				for (int y = 0; y < m; ++y) {
//					c[z * ldc + y] += (a[x * lda + y] * scalarA) * (b[z * ldb + x] * scalarB);
//
//				}
//			}
//		}
//#pragma omp barrier
//	}
