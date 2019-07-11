///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///*
// * File:   LAR_General.h
// * Author: joseph
// *
// * Created on July 23, 2017, 3:24 PM
// */
//
//#include "BLACKCAT_GPU_MATHEMATICS.cuh"
//
////unsigned
////__global__ void GPU_MATHEMATICS::initialize(unsigned*& d, unsigned sz) {
////    d = new unsigned[sz];
////}
////
////unsigned
////__global__ void GPU_MATHEMATICS::destruction(unsigned * d) {
////    delete [] d;
////}
//
//
//__global__ void GPU_MATHEMATICS::copy(unsigned * store, const unsigned * v, unsigned sz) {
//    for (int i = 0; i < sz; ++i) {
//        store[i] = v[i];
//    }
//}
//
//
//__global__ void GPU_MATHEMATICS::fill(unsigned * m, unsigned f, unsigned sz) {
//    for (int i = 0; i < sz; ++i) {
//        m[i] = f;
//    }
//}
//
//
//__global__ void GPU_MATHEMATICS::transpose(unsigned * s, unsigned s_ld, const unsigned * m, unsigned rows, unsigned cols, unsigned m_ld) {
//
//	for (unsigned r = 0; r < rows; ++r) {
//		for (unsigned c= 0; c< cols; ++c) {
//			s[r * s_ld + c] = m[c * m_ld + r];
//		}
//	}
//}
//
//
//__global__ void GPU_MATHEMATICS::max(unsigned* max_val, const unsigned* data, const unsigned* ranks, const unsigned* ld, unsigned order) {
//
//	if (order == 1) {
//		for (unsigned i = 0; i < ranks[order-1]; ++i) {
//			if (*max_val < data[i]) {
//				*max_val = data[i];
//			}
//		}
//	} else {
//
//		for (unsigned i = 0; i < ranks[order-1]; ++i) {
//			max<<<256,256>>>(max_val, &data[i * ld[order-1]], ranks, ld, order-1);
//		}
//	}
//}
//
//
//__global__ void GPU_MATHEMATICS::min(unsigned* min_val, const unsigned* data, const unsigned* ranks, const unsigned* ld, unsigned order) {
//
//	if (order == 1) {
//		for (unsigned i = 0; i < ranks[order-1]; ++i) {
//			if (*min_val < data[i]) {
//				*min_val = data[i];
//			}
//		}
//	} else {
//
//		for (unsigned i = 0; i < ranks[order-1]; ++i) {
//			min<<<256,256>>>(min_val, &data[i * ld[order-1]], ranks, ld, order-1);
//		}
//	}
//}
//
//
//__global__ void GPU_MATHEMATICS::max_index(unsigned* max_val, unsigned* max_indexes, const unsigned* data, const unsigned* ranks, const unsigned* ld, unsigned order) {
//
//	if (order == 1) {
//		for (unsigned i = 0; i < ranks[order-1]; ++i) {
//			if (*max_val < data[i]) {
//				*max_val = data[i];
//				*max_indexes = i;
//			}
//		}
//	} else {
//
//		unsigned curr_max;
//		for (unsigned i = 0; i < ranks[order-1]; ++i) {
//			curr_max = *max_val;
//			max_index<<<256,256>>>(max_val, max_indexes, &data[i * ld[order-1]], ranks, ld, order-1);
//
//			//if modified -- update
//			if (curr_max != *max_val) {
//				max_indexes[order-1] = i;
//			}
//		}
//	}
//}
//
//
//
//__global__ void GPU_MATHEMATICS::min_index(unsigned* min_val, unsigned* min_indexes, const unsigned* data, const unsigned* ranks, const unsigned* ld, unsigned order) {
//
//	if (order == 1) {
//		for (unsigned i = 0; i < ranks[order-1]; ++i) {
//			if (*min_val < data[i]) {
//				*min_val = data[i];
//				*min_indexes = i;
//			}
//		}
//	} else {
//
//		unsigned curr_max;
//		for (unsigned i = 0; i < ranks[order-1]; ++i) {
//			curr_max = *min_val;
//			min_index<<<256,256>>>(min_val, min_indexes, &data[i * ld[order-1]], ranks, ld, order-1);
//
//			//if modified -- update
//			if (curr_max != *min_val) {
//				min_indexes[order-1] = i;
//			}
//		}
//	}
//}
//
//
//
//
//__global__ void GPU_MATHEMATICS::randomize(unsigned * m, unsigned lower_bound, unsigned upper_bound, unsigned sz) {
//    for (int i = 0; i < sz; ++i) {
//        m[i] =  i % 2 == 0 ? 3 : -3 ;
//    }
//}
//
//
//__global__ void GPU_MATHEMATICS::randomize(unsigned * m, unsigned* ld, unsigned* ranks, unsigned order, unsigned lower_bound, unsigned upper_bound) {
//    --order;
//    if (order == 0) {
//    	randomize<<<256,256>>>(m, lower_bound, upper_bound , ranks[order]);
//    } else {
//    	for (unsigned i = 0; i < ranks[order]; ++i) {
//    		randomize<<<256,256>>>(&m[ld[order] * i], ld, ranks, order, lower_bound, upper_bound);
//    	}
//    }
//}
//
//void GPU_MATHEMATICS::print(const unsigned* ary, unsigned sz) {
//	for (unsigned i = 0; i < sz; ++i) {
//		std::cout << ary[i] << " " << std::endl;
//	}
//}
//
//
//__global__ void GPU_MATHEMATICS::print(const unsigned* ary, const unsigned* dims, const unsigned* lead_dims, unsigned index) {
//
//
////	if (index < 3) {
////		for (unsigned r = 0; r < dims[0]; ++r) {
////
////			if (r != 0)
////			std::cout << std::endl;
////
////			for (unsigned c = 0; c< dims[1]; ++c) {
////				auto str =std::to_string(ary[r + c * lead_dims[index - 1]]);
////				str = str.substr(0, str.length() < 3 ? str.length() : 3);
////				std::cout << str << " ";
////			}
////		}
////		std::cout << "]" << std::endl << std::endl;
////
////	} else {
////		std::cout << "[";
////		for (unsigned i = 0; i < dims[index - 1]; ++i) {
////			print(&ary[i * lead_dims[index - 1]], dims, lead_dims, index - 1);
////		}
////	}
//}
