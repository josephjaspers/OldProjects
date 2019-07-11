///*
// * TensorSupTensorDepFiles.h
// *
// *  Created on: Oct 7, 2017
// *      Author: joseph
// */
//
//#ifndef TENSORSUPTENSORDEPFILES_H_
//#define TENSORSUPTENSORDEPFILES_H_
//
//	mutable std::unordered_map<unsigned, Tensor<number_type, TensorOperations>*> IndexTensorMap;							//index Tensor map - caches index tensors [for faster access]
//	mutable std::unordered_map<std::pair<Shape, Shape>,Tensor<number_type, TensorOperations>*,BC::indexShape_pairHasher, BC::indexShape_pairEqual> SubTensorMap;	//index Tensor map - caches index tensors [for faster access]
//
//	mutable bool needsUpdate = true;
//	const Tensor<number_type, TensorOperations>* parent = nullptr;
//
//	void alertUpdate() const {
//		needsUpdate = true;
//
//		if (parent)
//			parent->alertUpdate();
//	}
//
//	Tensor<number_type, TensorOperations>* generateIndexTensor(unsigned index) const;															//Sub_Tensor generator
//	Tensor<number_type, TensorOperations>* generateSubTensor(Shape index, Shape shape) const;
//	bool needUpdate()							const;
//
//	//implementations ==============
//
//	template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator()(Shape index, Shape shape) {
//	#ifndef BLACKCAT_DISABLE_RUNTIME_CHECKS
//
//	#endif
//
//		std::pair<Shape, Shape> PairIndex(index, shape);
//
//
//		if (SubTensorMap.find(PairIndex) == SubTensorMap.end()) {
//			SubTensorMap[PairIndex] = generateSubTensor(index, shape);
//			return *(SubTensorMap[PairIndex]);
//		} else {
//			return *(SubTensorMap[PairIndex]);
//		}
//	}
//
//	template<typename number_type, class TensorOperations> const Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator()(Shape index, Shape shape) const {
//	#ifndef BLACKCAT_DISABLE_RUNTIME_CHECKS
//
//	#endif
//		std::pair<Shape, Shape> PairIndex(index, shape);
//
//
//		if (SubTensorMap.find(PairIndex) == SubTensorMap.end()) {
//			SubTensorMap[PairIndex] = generateSubTensor(index, shape);
//			return *(SubTensorMap[PairIndex]);
//		} else {
//			return *(SubTensorMap[PairIndex]);
//		}
//	}
//	template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations>* Tensor<number_type, TensorOperations>::generateSubTensor(Shape index, Shape shape) const {
//		return new Tensor<number_type, TensorOperations>(*this, index, shape);
//	}
//
//
//	//------------------------------Constructor for generating a sub tensor (NOT AN INDEX TENSOR)
//	namespace meh{
//	void print(Shape data, std::string message) {
//		std::cout << message << ": ";
//		for (int i = 0; i < data.size(); ++i)  {
//			std::cout << data[i] << " " ;
//		}
//	}
//	}
//
//
//
//	//------------------------------------- Generate Index Tensor-------------------------------------//
//
//	template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations>* Tensor<number_type, TensorOperations>::generateIndexTensor(unsigned index) const {
//		return new Tensor<number_type, TensorOperations>(*this, index);
//	}
//
//	template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations>* Tensor<number_type, TensorOperations>::generateSubTensor(Shape index, Shape shape) const {
//		return new Tensor<number_type, TensorOperations>(*this, index, shape);
//	}
//
//#include "Tensor.h"
//#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"
//
//
////------------------------------------- Scalar Accessor-------------------------------------//
//
//template<typename number_type, class TensorOperations> Scalar<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator()(unsigned index) {
//	return Scalar<number_type, TensorOperations>(&tensor[index], false);
//}
//
//template<typename number_type, class TensorOperations> const Scalar<number_type, TensorOperations> Tensor<number_type, TensorOperations>::operator()(unsigned index) const {
//	alertUpdate();
//	return Scalar<number_type, TensorOperations>(&tensor[index], false);
//}
//
////------------------------------------- Index Tensor Constructor------------------------------------//
//
//
//template<typename number_type, class TensorOperations>
//Tensor<number_type, TensorOperations>::Tensor(const Tensor<number_type, TensorOperations>& super_tensor, unsigned index) : tensor_ownership(false), subTensor(super_tensor.subTensor),
//rank_ownership(false), ld_ownership(false) {
//
//	unsigned tensor_index = 1;
//	for (unsigned i = 0; i < super_tensor.order - 1; ++i) {
//		tensor_index *= super_tensor.ranks[i];
//	}
//	tensor_index *= index;
//
//	this->tensor = &super_tensor.tensor[tensor_index];
//	this->ranks = super_tensor.ranks;
//	this->ld = super_tensor.ld;
//	this->order = super_tensor.order > 0 ? super_tensor.order - 1 : 0;
//
//	this->sz = super_tensor.sz / super_tensor.ranks[order];
//}
//
//
////------------------------------------- Index Tensor Operator-------------------------------------//
//
//
//template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator[](unsigned index) {
//
//#ifndef BLACKCAT_DISABLE_RUNTIME_CHECKS
//	if (index >= ranks[order - 1]) {
//	throw std::invalid_argument("Operator[] out of bounds -- Order: " + std::to_string(order) + " Index: " + std::to_string(index));
//}
//#endif
//
//	if (IndexTensorMap.find(index) == IndexTensorMap.end()) {
//		IndexTensorMap[index] = generateIndexTensor(index);
//		return *(IndexTensorMap[index]);
//	} else {
//		return *(IndexTensorMap[index]);
//	}
//}
//
//template<typename number_type, class TensorOperations>const Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator[](unsigned index) const {
//
//#ifndef BLACKCAT_DISABLE_RUNTIME_CHECKS
//	if (index >= ranks[order - 1]) {
//	throw std::invalid_argument("Operator[] out of bounds -- Order: " + std::to_string(order) + " Index: " + std::to_string(index));
//}
//#endif
//
//	if (IndexTensorMap.find(index) == IndexTensorMap.end()) {
//		IndexTensorMap[index] = generateIndexTensor(index);
//		return *(IndexTensorMap[index]);
//	} else {
//		return *(IndexTensorMap[index]);
//	}
//}
//
//
//template<typename number_type, class TensorOperations>
//void Tensor<number_type, TensorOperations>::clearTensorCache() {
//	if(IndexTensorMap.size() > 0) {
//		for (auto it = IndexTensorMap.begin(); it != IndexTensorMap.end(); ++it) {
//			delete it->second;
//		}
//	}
//	if(SubTensorMap.size() > 0) {
//		unsigned count = 1;
//		for (auto it = SubTensorMap.begin(); it != SubTensorMap.end(); ++it) {
//			if (it->second) {
//			delete it->second;
//			it->second = nullptr;
//			++count;
//			}
//		}
//	}
//}
//
////------------------------------------SUBTENSOR -------------------------------------//
//template<typename number_type, class TensorOperations> Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator()(Shape index, Shape shape) {
//#ifndef BLACKCAT_DISABLE_RUNTIME_CHECKS
//
//#endif
//
//	std::pair<Shape, Shape> PairIndex(index, shape);
//
//
//	if (SubTensorMap.find(PairIndex) == SubTensorMap.end()) {
//		SubTensorMap[PairIndex] = generateSubTensor(index, shape);
//		return *(SubTensorMap[PairIndex]);
//	} else {
//		return *(SubTensorMap[PairIndex]);
//	}
//}
//
//template<typename number_type, class TensorOperations> const Tensor<number_type, TensorOperations>& Tensor<number_type, TensorOperations>::operator()(Shape index, Shape shape) const {
//#ifndef BLACKCAT_DISABLE_RUNTIME_CHECKS
//
//#endif
//	std::pair<Shape, Shape> PairIndex(index, shape);
//
//
//	if (SubTensorMap.find(PairIndex) == SubTensorMap.end()) {
//		SubTensorMap[PairIndex] = generateSubTensor(index, shape);
//		return *(SubTensorMap[PairIndex]);
//	} else {
//		return *(SubTensorMap[PairIndex]);
//	}
//}
//
//
////------------------------------Constructor for generating a sub tensor (NOT AN INDEX TENSOR)
//
//
//template<typename number_type, class TensorOperations>
//Tensor<number_type, TensorOperations>::Tensor(const Tensor<number_type, TensorOperations>& super_tensor, Shape index, Shape shape)
//:
//tensor_ownership(false), rank_ownership(true), ld_ownership(false), subTensor(true){
//	if (super_tensor.order != index.size() || shape.size() > index.size()) {
//		throw std::invalid_argument("Non-definitive index given for subTensor");
//	}
////	for (unsigned i = 0; i < index.size(); ++i) {
////		if (index[index.size() - 1 - i]  > super_tensor.ranks[i]) {
////			super_tensor.printDimensions();
////					meh::print(index, "index " );
////					meh::print(shape, " shape");
////					throw std::invalid_argument("sub index out of bounds");
////
////			}
////		}
////
////	for (unsigned i = 0; i < shape.size(); ++i) {
////		if (shape[i] + index[index.size() - 1 - i] > super_tensor.ranks[i]) {
////			super_tensor.printDimensions();
////			meh::print(index, " index" );
////			meh::print(shape, " shape");
////			throw std::invalid_argument("sub tensor size greater than primary matrix");
////		}
////
////	}
//
//	parent = &super_tensor;
//	sz = BC::calc_sz(&shape[0], shape.size());
//	order = shape.size();
//	ranks = new unsigned[order];
//	ld = super_tensor.ld;
//	BC::copy(ranks, &shape[0], order);
//
//	unsigned t_id = 0;
//	for (int i = 0; i < index.size(); ++i) {
//		t_id += super_tensor.ld[i] * index[index.size() - i - 1];
//	}
//	tensor = &super_tensor.tensor[t_id];
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//template<typename number_type, class TensorOperations>
//void Tensor<number_type, TensorOperations>::clearTensorCache() {
//	if(IndexTensorMap.size() > 0) {
//		for (auto it = IndexTensorMap.begin(); it != IndexTensorMap.end(); ++it) {
//			delete it->second;
//		}
//	}
//	if(SubTensorMap.size() > 0) {
//		unsigned count = 1;
//		for (auto it = SubTensorMap.begin(); it != SubTensorMap.end(); ++it) {
//			if (it->second) {
//			delete it->second;
//			it->second = nullptr;
//			++count;
//			}
//		}
//	}
//}
//
//
//
//
//#endif /* TENSORSUPTENSORDEPFILES_H_ */
