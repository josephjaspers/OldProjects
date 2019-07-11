


/*
 * Shape.h
 *
 *  Created on: Jan 18, 2018
 *      Author: joseph
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>

namespace BC {



struct Shape { //: private INNER, private OUTER {

	using _shape = std::vector<int>;

	_shape is;
	_shape os;

	int sz;
	int order;
	bool array_ownership;

	Shape(const Shape& param) : is(param.is), os(param.os), sz(param.sz), order(param.order), array_ownership(param.array_ownership) {}
	Shape(_shape param) : is(param), order(param.size()), array_ownership(true) {
		os = _shape(order);
		if (order > 0) {
			os = _shape(order);
			sz = is[0];
			os[0] = is[0];
			for (int i = 1; i < order; ++i) {
				sz *= is[i];
				os[i] = os[i - 1] * is[i];
			}
		}
	}
	Shape(_shape is, _shape os, int order, int size, bool ownership) : is(is), os(os), order(order), sz(size), array_ownership(ownership) {}
	Shape() : array_ownership(false), order(0), sz(1), is(0), os(0) {}

	void printDetails() const {
		std::cout << " Tensor: " << std::endl;
		std::cout << " order = " << order << std::endl;
		std::cout << " size = " << sz << std::endl;
		std::cout << " inner dimensions: ";
		printDimensions();
		std::cout << " outer dimensions: ";
		printLDDimensions();
	}

	int rank() const { return order; }
	int size() const { return sz;    }
	int rows() const { return order > 0 ? is[0] : 1; }
	int cols() const { return order > 1 ? is[1] : 1; }
	int dimension(int i) const { return order > i ? is[i] : 1; }
	void printDimensions() const { for (int i = 0; i < order; ++i) { std::cout << "["<< is[i] << "]"; } std::cout << std::endl; }
	void printLDDimensions() const { for (int i = 0; i < order; ++i) { std::cout << "["<< os[i] << "]"; } std::cout << std::endl; }

	int LD_rows() const { return order > 0 ? os[0] : 1; }
	int LD_cols() const { return order > 1 ? os[1] : 1; }
	int LDdimension(int i) const { return order > i + 1 ? os[i] : 1; }

	const int* InnerShape() const { return &is[0]; }
	const int* OuterShape() const { return &os[0]; }

	void resetShape(_shape sh)  {
		is = sh;
		os = _shape(order);
		sz = is[0];
		os[0] = is[0];
		for (int i = 1; i < order; ++i) {
			sz *= is[i];
			os[i] = os[i - 1] * is[i];
		}

	}

	const Shape& expression_packet() const  { return *this; }
	auto shape_copy_packet() const 	{ return Shape(is, os, order, sz, true); }
	auto accessor_packet() const    { return Shape(is, os, order - 1, sz/is[order - 1], false); }
	auto transpose_packet() const   { return Shape({this->cols(), this->rows()}, os, 2, sz, false); }
	auto dotproduct_packet(int eval_order, const Shape& sh) const {

		return eval_order == 1 ?
				Shape({this->rows()}) :
				Shape({this->rows(), sh.cols()});
	}
	auto subAccessor_packet(_shape is_) const  { return Shape(is_, os, order, sz, false); }

	const Shape& asShape() const { return *this; }
	void ChangeShapeOwnership(bool swap = false) {
		array_ownership = swap;
	}
};

}

#endif /* SHAPE_H_ */



