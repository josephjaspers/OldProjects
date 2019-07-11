/*
 * BC_PointwiseDotproduct.cu
 *
 *  Created on: Feb 6, 2018
 *      Author: joseph
 */

#ifndef BC_POINTWISEDOTPRODUCT_CU_
#define BC_POINTWISEDOTPRODUCT_CU_

namespace BC {
#ifdef __CUDACC__
#define __BC_gcpu__ __host__ __device__
#define BLACKCAT_GPU_ENABLED
#else
#define __BC_gcpu__
#endif

template<class, class> class Matrix;
template<class, class> class Vector;
template<class, class> class expression;

template<class T, class functor_type>
struct pointwise_accessor : expression<T, pointwise_accessor<T, functor_type>> {
	//Evaluates a single row*column operation of two tensors

	functor_type lv;
	functor_type rv;

	T*	evaluation;
};


template<class T, class ml>
Vector<T, ml> operator * (const Matrix<T, ml>&, const Vector<T, ml>&) {

}






}


#endif /* BC_POINTWISEDOTPRODUCT_CU_ */
