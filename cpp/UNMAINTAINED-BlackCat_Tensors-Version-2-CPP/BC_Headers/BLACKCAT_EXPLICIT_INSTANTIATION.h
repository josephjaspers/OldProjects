/*
 * File:   BLACKCAT_EXPLICIT_INSTANTIATION.h
 * Author: joseph
 *
 * Created on July 31, 2017, 7:54 PM
 */

#ifndef BLACKCAT_EXPLICIT_INSTANTIATION_H
#define BLACKCAT_EXPLICIT_INSTANTIATION_H

/*
 * Blackcat_Define.h
 *
 *  Created on: Aug 16, 2017
 *      Author: joseph
 */

/* DISABLE STANDARD RUNTIME CHECKS*/
//#define BLACKCAT_DISABLE_RUNTIME_CHECKS

/*DISABLE ADVANCED RUNETIME CHECKS  -- bounds checking for data accessors */
//#define BLACKCAT_DISABLE_ADVANCED_CHECKS

//#endif /* BLACKCAT_DEFINE_H_ */

#include "CPU.h"
template class CPU_MATHEMATICS<double>;
template class CPU_MATHEMATICS<float>;
template class CPU_MATHEMATICS<unsigned>;
template class CPU_MATHEMATICS<signed>;


#include "Tensor.h"
template class Tensor<double, CPU>;
template class Tensor<float, CPU>;
template class Tensor<unsigned, CPU>;
template class Tensor<signed, CPU>;

#include "Scalar.h"
template class Scalar<double, CPU>;
template class Scalar<unsigned, CPU>;
template class Scalar<signed, CPU>;
template class Scalar<float, CPU>;

#include "Matrix.h"
template class Matrix<double,CPU>;
template class Matrix<unsigned,CPU>;
template class Matrix<signed,CPU>;
template class Matrix<float,CPU>;

#include "Vector.h"
template class Vector<double,CPU>;
template class Vector<unsigned,CPU>;
template class Vector<signed,CPU>;
template class Vector<float,CPU>;
//
//GPU FORWARD DECLERATION
//#include "GPU.h"

//template class Tensor<double, GPU>;
//template class Tensor<float, GPU>;
//template class Tensor<unsigned, GPU>;
//template class Tensor<signed, GPU>;

//template class Scalar<double, GPU>;
//template class Scalar<unsigned, GPU>;
//template class Scalar<signed, GPU>;
//template class Scalar<float, GPU>;

//template class Matrix<double,GPU>;
//template class Matrix<unsigned,GPU>;
//template class Matrix<signed,GPU>;
//template class Matrix<float,GPU>;

//template class Vector<double,GPU>;
//template class Vector<unsigned,GPU>;
//template class Vector<signed,GPU>;
//template class Vector<float,GPU>;


#endif /* BLACKCAT_EXPLICIT_INSTANTIATION_H */

