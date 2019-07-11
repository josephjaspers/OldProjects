/*
 * BlackCat_Definitions.h
 *
 *  Created on: Dec 18, 2017
 *      Author: joseph
 */
#ifndef BLACKCAT_INTERNAL_DEFINITIONS_H_
#define BLACKCAT_INTERNAL_DEFINITIONS_H_
namespace BC {
	constexpr int OPENMP_SINGLE_THREAD_THRESHHOLD = 9999;

	enum DIMENSIONS {
		//Here at Blackcat Tensors we support all variations of dynamic
		dynamic = 0,
		Dynamic = 0,
		DYNAMIC = 0,
		SCALAR = 0,
		VECTOR = 1,
		MATRIX = 2,
		CUBE = 3,
	};
}

#endif /* BLACKCAT_INTERNAL_DEFINITIONS_H_ */
