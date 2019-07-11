/*
 * Expression_Binary_Dotproduct.cu
 *
 *  Created on: Jan 9, 2018
 *      Author: joseph
 */
#ifdef  __CUDACC__
#ifndef EXPRESSION_BINARY_DOTPRODUCT_CU_
#define EXPRESSION_BINARY_DOTPRODUCT_CU_


#include "Expression_Binary_Dotproduct_impl.cu"
#include "Expression_Base.cu"
#include "../BlackCat_Internal_Definitions.h"
#include "../BC_MetaTemplateFunctions/Adhoc.h"
#include "../BC_Core/Implementation_Core/Shape.h"
#include <iostream>
#include <memory>

namespace BC {

/*
 * a = M x K
 * b = K x N
 * c = M x N
 */

//The evaluation of dot_products are tightly coupled with the unary expression - transpose, and binary expression scalar L and scalar R.T*
//This is just because CUDA doesn't have constexpr_if support yet. Get on it guys.
template<class T, class U>
void assignDP(T* from, U to) {
	throw std::invalid_argument("Illegal Assign");
}
template<class T, class lv, class rv>
void assignDP(T*& from, binary_expression<T, assign, lv, rv>& bed) {
	from = bed.left;
}
template<class T>
void assignDP(T*& from, T* to) {
	from = to;
}


template<class T, class lv, class rv, class Mathlibrary>
struct binary_expression_dotproduct : non_linear_expression<T, binary_expression_dotproduct<T, lv, rv, Mathlibrary>> {
	using scalar_type = typename MTF::determine_scalar<T>::type;

	//this is the deleter for the shared ptr --> We use a shared pointer so that everytime you pass the extended function of a dot product
	//the program does not recalculate the dot_product //Normally I hate shared pointers.
	struct deleter {
		void operator()(const scalar_type* t) {
			Mathlibrary::destroy(t);
		}
	};

	static constexpr int ALPHA_DEFAULT  = 1;
	static constexpr int BETA_DEFAULT   = 0;

	const lv& left;
	const rv& right;

	const int M = 0;
	const int N = 0;
	const int K = 0;
	const int LDA = 0;
	const int LDB = 0;
	const int LDC = 0;

	static constexpr bool lv_needs_to_be_evaluated = evaluate<lv>::conditional;
	static constexpr bool rv_needs_to_be_evaluated = evaluate<rv>::conditional;
	static constexpr bool transA = evaluate<lv>::transpose;
	static constexpr bool transB = evaluate<rv>::transpose;

	using l_eval_array = typename MTF::determine_scalar<lv>::type;
	using r_eval_array = typename MTF::determine_scalar<rv>::type;

	const int lv_size = M * K;
	const int rv_size = N * K;
	const int eval_size = M * N ;

	bool parent = true;
	std::shared_ptr<scalar_type> array;
	scalar_type* array_ptr = array.get();

	__attribute__((always_inline))
	binary_expression_dotproduct(const lv& left, const rv& right, int M, int N, int K, int ldM = 0, int ldN = 0, int ldK = 0) :
	M(M), N(N), K(K),
	LDA(ldM == 0 ? M : ldM), LDB(ldN == 0 ? K : ldN), LDC(ldK == 0 ? M : ldK),
	left(left), right(right) {

		eval();
		array_ptr = array.get();
	}


public:

	void eval() {
		auto A_unevaluated = evaluate<lv>::getArray(left);
		auto B_unevaluated = evaluate<rv>::getArray(right);
		scalar_type* scal_A = evaluate<lv>::getScalar(left);
		scalar_type* scal_B = evaluate<rv>::getScalar(right);

		T* A;
		T* B;

		if (lv_needs_to_be_evaluated) {
			if (self_eval<lv>::conditional) {
				Mathlibrary::eval(A_unevaluated, lv_size);
				assignDP(A, A_unevaluated);
			} else {
			Mathlibrary::initialize(A, lv_size);
			Mathlibrary::copy(A, A_unevaluated, lv_size);
			}
		}
			else { assignDP(A, A_unevaluated); }

		if (rv_needs_to_be_evaluated) {
			if (self_eval<rv>::conditional) {
				Mathlibrary::eval(B_unevaluated, rv_size);
				assignDP(B, B_unevaluated);
			} else {
				Mathlibrary::initialize(B, rv_size);
				Mathlibrary::copy(B, B_unevaluated, rv_size);
			}
		}
			else { assignDP(B, B_unevaluated); }


		scalar_type* tmp;
		Mathlibrary::initialize(tmp, eval_size);
		array = std::shared_ptr<scalar_type>(tmp, deleter());

		//If both sides are multiplied by a scalar --- multiply the scalars
		if (scal_A && scal_B) {
			T* scalar;
			Mathlibrary::initialize(scalar, 1);
			Mathlibrary::scalarMul(scalar, scal_A, scal_B);
			Mathlibrary::MatrixMul(transA, transB, A, B, array.get(), M, N, K, scalar, nullptr, LDA, LDB, LDC);
			Mathlibrary::destroy(scalar);
		} else if (scal_A) {
		Mathlibrary::MatrixMul(transA, transB, A, B, array.get(), M, N, K, scal_A, nullptr, LDA, LDB, LDC);
		} else if (scal_B){
			scal_A = scal_B;
			scal_B = nullptr;
			Mathlibrary::MatrixMul(transA, transB, A, B, array.get(), M, N, K, scal_A, nullptr, LDA, LDB, LDC);
		} else {
			Mathlibrary::MatrixMul(transA, transB, A, B, array.get(), M, N, K, nullptr, nullptr, LDA, LDB, LDC);
		}

//				std::cout << "dotproduct stats --------------------------------------------------------------------------" << std::endl;
//						std::cout << " m n k = " << M << "  "<< N << " " << K << std::endl;
//
//						if (lv_needs_to_be_evaluated) {
//							if (self_eval<lv>::conditional) {
//								std::cout << " lv self eval " << std::endl;
//							} else
//							std::cout << " lv was evaluated " << std::endl;
//						}
//						if (rv_needs_to_be_evaluated) {
//							if (self_eval<rv>::conditional) {
//								std::cout << " rv self eval " << std::endl;
//							} else
//							std::cout << " rv was evaluated " << std::endl;
//						}
//						if (transA) {
//							std::cout << " A - fast trans " << std::endl;
//						}
//						if (transB) {
//							std::cout << " B - fast trans " << std::endl;
//						}
//						if (evaluate<lv>::scalar) {
//							std::cout << " lv scalar detected " << std::endl;
//						}
//						if (evaluate<rv>::scalar) {
//							std::cout << " rv scalar detected " << std::endl;
//						}
//						if (scal_A && scal_B)
//						std::cout << "scalars = " << *scal_A <<  " " << *scal_B << std::endl;
//						std::cout << " --------------------------------------------------------------------------" << std::endl;

		if (lv_needs_to_be_evaluated && !self_eval<lv>::conditional) { Mathlibrary::destroy(A); }
		if (rv_needs_to_be_evaluated && !self_eval<rv>::conditional) { Mathlibrary::destroy(B); }

	}

		__attribute__((always_inline))  __BC_gcpu__
		 const T operator [](int index) const {
			return array_ptr[index];
		}
		__attribute__((always_inline))  __BC_gcpu__
			T operator [](int index) {
			return array_ptr[index];
		}
	};
}

#endif /* EXPRESSION_BINARY_DOTPRODUCT_CU_ */
#endif


//				Some printouts for debugging
//
//		std::cout << "dotproduct stats --------------------------------------------------------------------------" << std::endl;
//				std::cout << " m n k = " << M << "  "<< N << " " << K << std::endl;
//
//				if (lv_needs_to_be_evaluated) {
//					if (self_eval<lv>::conditioanl) {
//						std::cout << " lv self eval " << std::endl;
//					}
//					std::cout << " lv was evaluated " << std::endl;
//				}
//				if (rv_needs_to_be_evaluated) {
//					if (self_eval<rv>::conditioanl) {
//						std::cout << " rv self eval " << std::endl;
//					}
//					std::cout << " lv was evaluated " << std::endl;
//				}
//				if (transA) {
//					std::cout << " A - fast trans " << std::endl;
//				}
//				if (transB) {
//					std::cout << " B - fast trans " << std::endl;
//				}
//				if (evaluate<lv>::scalar) {
//					std::cout << " lv scalar detected " << std::endl;
//				}
//				if (evaluate<rv>::scalar) {
//					std::cout << " rv scalar detected " << std::endl;
//				}
//				if (scal_A && scal_B)
//				std::cout << "scalars = " << *scal_A <<  " " << *scal_B << std::endl;
//				std::cout << " --------------------------------------------------------------------------" << std::endl;


