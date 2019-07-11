/*
 * Tensor_IdentityClasses.h
 *
 *  Created on: Dec 30, 2017
 *      Author: joseph
 */

#ifndef TENSOR_IDENTITYCLASSES_H_
#define TENSOR_IDENTITYCLASSES_H_

namespace BC {

/*
 * These classes are the superclasses of the tensor cores -- they are passed to the Tensor_Operations through the derived class.
 * They clarify the rank of the tensor to each type.
 */

	template<class derived>
	struct IDENTITY_BASE {
			  derived& convert() 	   { return static_cast      <derived&>(*this); }
		const derived& convert() const { return static_cast<const derived&>(*this); }
	};


template<class core> struct SCALAR : IDENTITY_BASE<core> { static constexpr int RANK = 0; };
template<class core> struct VECTOR : IDENTITY_BASE<core> { static constexpr int RANK = 1; };
template<class core> struct MATRIX : IDENTITY_BASE<core> { static constexpr int RANK = 2; };
template<class core> struct CUBE   : IDENTITY_BASE<core> { static constexpr int RANK = 3; };
template<class core> struct TENSOR : IDENTITY_BASE<core> { static constexpr int RANK = -1; };

	template<class scalar, class functor, class evaluation, class math_lib>
	struct _TRAITS {
			using scalar_type 		= scalar;
			using functor_type 		= functor;
			using evaluation_type 	= evaluation;
			using math_library 		= math_lib;
	};



	template<int rank, class core> struct IDENTIFY;
	template<class core> struct IDENTIFY<0,  core> { using type = SCALAR<core>; };
	template<class core> struct IDENTIFY<1,  core> { using type = VECTOR<core>; };
	template<class core> struct IDENTIFY<2,  core> { using type = MATRIX<core>; };
	template<class core> struct IDENTIFY<3,  core> { using type = CUBE<core>; };
	template<class core> struct IDENTIFY<-1, core> { using type = TENSOR<core>; };

}

#endif /* TENSOR_IDENTITYCLASSES_H_ */
