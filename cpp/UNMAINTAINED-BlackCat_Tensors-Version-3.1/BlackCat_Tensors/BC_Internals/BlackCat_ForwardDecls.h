/*
 * Blackcat_ForwardsDecls.h
 *
 *  Created on: Jan 9, 2018
 *      Author: joseph
 */

#ifndef BLACKCAT_FORWARDSDECLS_H_
#define BLACKCAT_FORWARDSDECLS_H_

namespace BC {
class CPU;
class GPU;

#ifndef BLACKCAT_DEFAULT_MATHLIB_GPU

using DEFAULT_MATHLIB = CPU;
#else
using DEFAULT_MATHLIB = GPU
#endif

template<class, class ML = DEFAULT_MATHLIB> class Vector;
template<class, class ML = DEFAULT_MATHLIB> class RowVector;
template<class, class ML = DEFAULT_MATHLIB> class Matrix;
template<class, class ML = DEFAULT_MATHLIB> class Scalar;
}


#endif /* BLACKCAT_FORWARDSDECLS_H_ */
