#ifdef __CUDACC__
#ifndef BC_GPU_IMPL
#define BC_GPU_IMPL

#include <cuda_runtime_api.h>
#include <cuda.h>
#include <curand.h>
#include <curand_kernel.h>

#include <limits>
#include <cstddef>
#include <type_traits>

namespace BC {
namespace gpu_impl {

template<typename T, typename J> __global__
static void fill(T& t, const J j, int sz) {
	for (int i = 0; i < sz; ++i) {
		t[i] = j;
	}
}
template<typename T, typename J> __global__
static void fill(T& t, const J* j, int sz) {
	for (int i = 0; i < sz; ++i) {
		t[i] = j[0];
	}
}

template<class T, class U, class V> __global__
static void scalarMul(T* t, U* u, V* v) {
	*t = u[0] * v[0];
}

template<typename T> __global__
static void zero(T& t, int sz) {
	for (int i = 0; i < sz; ++i) {
		t[i] = 0;
	}
}

template<class T, class J> __global__
static void copy(T t, const J j, int sz) {
	for (int i = 0; i < sz; ++i) {
		t[i] = j[i];
	}
}

template<class T, class J> __global__
static void copyStructPtr(T t, J* j, int sz) {
	for (int i = 0; i < sz; ++i) {
		t[i] = (*j)[i];
	}
}

template<class T> __global__
static void eval(T t, int sz) {
	for (int i = 0; i < sz; ++i) {
		t[i];
	}
}

template<class T>
struct  _max {
	static constexpr T value = std::numeric_limits<T>::max();
};

template<typename T, typename J> __global__
static void randomize(T& t, J lower_bound, J upper_bound, int sz, int seed) {

	 curandState_t state;
	  curand_init(seed, /* the seed controls the sequence of random values that are produced */
	              seed, /* the sequence number is only important with multiple cores */
	              1, /* the offset is how much extra we advance in the sequence for each call, can be 0 */
	              &state);


	for (int i = 0; i < sz; ++i) {
		t[i] = curand(&state);
		t[i] /= 10000000000; //curand max value
		t[i] *= (upper_bound - lower_bound);
		t[i] += lower_bound;
	}
}

}


}

#endif
#endif //cudacc
