//	Tensor<number_type, TensorOperations> operator^(const Scalar<number_type, TensorOperations>& t) const;
//	Tensor<number_type, TensorOperations> operator/(const Scalar<number_type, TensorOperations>& t) const;
//	Tensor<number_type, TensorOperations> operator+(const Scalar<number_type, TensorOperations>& t) const;
//	Tensor<number_type, TensorOperations> operator-(const Scalar<number_type, TensorOperations>& t) const;
//	Tensor<number_type, TensorOperations> operator&(const Scalar<number_type, TensorOperations>& t) const;
//
//	Tensor<number_type, TensorOperations>& operator^=(const Scalar<number_type, TensorOperations>& t);
//	Tensor<number_type, TensorOperations>& operator/=(const Scalar<number_type, TensorOperations>& t);
//	Tensor<number_type, TensorOperations>& operator+=(const Scalar<number_type, TensorOperations>& t);
//	Tensor<number_type, TensorOperations>& operator-=(const Scalar<number_type, TensorOperations>& t);
//	Tensor<number_type, TensorOperations>& operator&=(const Scalar<number_type, TensorOperations>& t);
	//virtual Tensor<number_type, TensorOperations>& operator=(const Scalar<number_type, TensorOperations>& s);

//template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator^=(const Scalar<number_type, TensorOperations>& scal) {
//	subTensor ?
//			TensorOperations::power(tensor, ranks, order, ld, tensor, ld, scal())
//	:
//			TensorOperations::power(tensor, tensor, scal(), sz);
//
//	alertUpdate();
//    return *this;
//}
//
//template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator/=(const Scalar<number_type, TensorOperations>& scal) {
//	subTensor ?
//			TensorOperations::divide(tensor, ranks, order, ld, tensor, ld, scal())
//	:
//			TensorOperations::divide(tensor, tensor, scal(), sz);
//
// 	alertUpdate();
//    return *this;
//}
//
//template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator+=(const Scalar<number_type, TensorOperations>& scal) {
//	subTensor ?
//			TensorOperations::add(tensor, ranks, order, ld, tensor, ld, scal())
//	:
//			TensorOperations::add(tensor, tensor, scal(), sz);
//
//    alertUpdate();
//    return *this;
//}
//
//template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator-=(const  Scalar<number_type, TensorOperations>&  scal) {
//	subTensor ?
//				TensorOperations::subtract(tensor, ranks, order, ld, tensor, ld, scal())
//		:
//				TensorOperations::subtract(tensor, tensor, scal(), sz);
//
//    alertUpdate();
//    return *this;
//}
//
//template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator&=(const  Scalar<number_type, TensorOperations>&  scal) {
//
//	subTensor ?
//				TensorOperations::multiply(tensor, ranks, order, ld, tensor, ld, scal())
//		:
//				TensorOperations::multiply(tensor, tensor, scal(), sz);
//
//    alertUpdate();
//    return *this;
//}
////--------------------------------scalar non assignment --------------------------------------------------------//
//
//template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator-(const Scalar<number_type, TensorOperations>& scal) const {
//    Tensor<number_type, TensorOperations> s(*this, false);
//    subTensor ?
//    		TensorOperations::subtract(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal())
//    :
//    		TensorOperations::subtract(s.tensor, tensor, scal(), sz);
//
//    return s;
//}
//
//template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator&(const Scalar<number_type, TensorOperations>& scal) const {
//    Tensor<number_type, TensorOperations> s(*this, false);
//
//    subTensor ?
//    		TensorOperations::multiply(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal())
//    :
//    		TensorOperations::multiply(s.tensor, tensor, scal(), sz);
//
//    return s;
//}
//
//template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator^(const  Scalar<number_type, TensorOperations>&  scal) const {
//    Tensor<number_type, TensorOperations> s(*this, false);
//    subTensor ?
//    		TensorOperations::power(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal())
//    :
//    		TensorOperations::power(s.tensor, tensor, scal(), sz);
//
//    return s;
//}
//
//template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator/(const  Scalar<number_type, TensorOperations>&  scal) const {
//    Tensor<number_type, TensorOperations> s(*this, false);
//    subTensor ?
//    		TensorOperations::divide(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal())
//    :
//    		TensorOperations::divide(s.tensor, tensor, scal(), sz);
//
//
//    return s;
//}
//
//template<typename number_type, class TensorOperations>Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator+(const  Scalar<number_type, TensorOperations>&  scal) const {
//    Tensor<number_type, TensorOperations> s(*this, false);
//    subTensor ?
//    		TensorOperations::add(s.tensor, s.ranks, s.order, s.ld, tensor, ld, scal())
//    :
//    		TensorOperations::add(s.tensor, tensor, scal(), sz);
//
//
//    return s;
//}
