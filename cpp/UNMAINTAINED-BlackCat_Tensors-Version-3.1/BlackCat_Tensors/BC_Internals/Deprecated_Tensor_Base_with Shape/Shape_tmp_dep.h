

//
///*
// * Shape.h
// *
// *  Created on: Jan 18, 2018
// *      Author: joseph
// */
//
//#ifndef SHAPE_H_
//#define SHAPE_H_
//
//#include <vector>
//
//namespace BC {
//class _expression {};
//class _accessor {};
//class _subAccessor {};
//class _transpose {};
//class _dotproduct {};
//class _generic {};
//
//typedef std::vector<int> _shape;
//
//struct inner_shape {
//
//	static constexpr int COMPILE_TIME_ROWS() { return 0; }
//	static constexpr int COMPILE_TIME_COLS() { return 0; }
//
//
//	bool parent;
//	int sz = 1;
//	int *is = &sz;
//	int order = 0 ;
//	int rank() const { return order; }
//	int size() const { return sz; }
//	int rows() const { return order > 0  ? is[0] : 1; }
//	int cols() const { return order > 1  ? is[1] : 1; }
//	int dimension(int i) const { return order > i  ? is[i] : 1; }
//
//	const auto InnerShape() const { return is; }
//
//	inner_shape() : parent(false){}
//	inner_shape(std::initializer_list<int> sh) : order(sh.size()), parent(true) {
//		sz = 1;
//		is = new int[order];
//		for (int i = 0; i < order; ++i) {
//			sz *= sh.begin()[i];
//			is[i] =  sh.begin()[i];
//		}
//	}
//	inner_shape(_shape sh) : order(sh.size()), parent(true) {
//		sz = 1;
//		is = new int[order];
//		for (int i = 0; i < order; ++i) {
//			sz *= sh.begin()[i];
//			is[i] =  sh.begin()[i];
//		}
//	}
//	bool inner_shape_override(_shape sh) {
//		if (!parent) {
//			std::cout << " cannot alter non-parent tensor -- must create a deep copy --" << std::endl;
//			throw std::invalid_argument("Override Nested Shape Illegal");
////			return false;
//		} else {
//			delete[] is;
//
//			is = new int[order];
//			for (int i = 0; i < order; ++i) {
//				sz *= sh.begin()[i];
//				is[i] =  sh.begin()[i];
//			}
//		}
//		return true;
//	}
//
//
//	inner_shape(const inner_shape&  sh, _expression) : parent(false), sz(sh.sz), order(sh.order), is(sh.is) {}
//	inner_shape(const inner_shape&  sh, _accessor  ) : parent(false), sz(sh.sz / sh.is[sh.order - 1]), order(sh.order - 1), is(sh.is) {}
//	~inner_shape() {
//		if (parent) {
//			delete[] is;
//		}
//	}
//
//	void printDimensions() const {
//		for (int i = 0; i < order; ++i) {
//			std::cout << "[" << is[i] << "]";
//		}
//		std::cout << std::endl;
//	}
//};
//
//
//
//struct outer_shape {
//
//	static constexpr int COMPILE_TIME_LD_ROWS() { return 0; }
//	static constexpr int COMPILE_TIME_LD_COLS() { return 0; }
//
//	int one = 1;
//	bool parent = false;
//	int * is = &one;
//	int order = 0;
//
//	int LD_rows() const { return order > 0  ? is[0] : 1; }
//	int LD_cols() const { return order > 1  ? is[1] : 1; }
//	int LD_dimension(int i) const { return order > i  ? is[i] : 1; }
//
//	const auto OuterShape() const { return is; }
//	outer_shape() : parent(false) {}
//	outer_shape(std::initializer_list<int> sh) : order(sh.size()), parent(true) {
//		is = new int[order];
//		for (int i = 0; i < order; ++i) {
//			is[i] =  sh.begin()[i];
//		}
//	}
//	outer_shape(std::vector<int> sh) : order(sh.size()), parent(true) {
//		is = new int[order];
//		for (int i = 0; i < order; ++i) {
//			is[i] =  sh.begin()[i];
//		}
//	}
//	bool outer_shape_override(_shape sh) {
//		if (!parent) {
//			std::cout << "attemping to override  non parent outershape. -- Create a deep copy" << std::endl;
//			throw std::invalid_argument("error");
////			return false;
//		}
//
//		delete[] is;
//		is = new int[order];
//		for (int i = 0; i < order; ++i) {
//			is[i] =  sh.begin()[i];
//		}
//		return true;
//	}
//	outer_shape(const outer_shape& sh) : is(sh.is), parent(false), order(sh.order) {}
//	outer_shape(const outer_shape& sh, _expression) : is(sh.is), parent(false), order(sh.order) {}
//	outer_shape(const outer_shape& sh, _accessor  ) : is(sh.is), parent(false), order(sh.order) {}
//	~outer_shape() {
//		if (parent) {
//			delete[] is;
//		}
//	}
//};
//
//
//template<class T>
//struct shape_packet {
//	const inner_shape& is;
//	const outer_shape& os;
//
//	shape_packet(const inner_shape& is_, const outer_shape& os_) : is(is_), os(os_) {}
//};
//
//
//template<>
//struct shape_packet<_transpose> {
//
//	int row = 1;
//	int col = 1;
//	int order = 2;
//	const outer_shape& os;
////	shape_packet(int rows, const outer_shape& os) : row(rows), order(1), os(os) {}
//	shape_packet(int rows, int cols, const outer_shape& os) : row(rows), col(cols), order(2), os(os) {}
////	shape_packet(int order, int rows, int cols, const outer_shape& os) : row(rows), col(cols), order(order), os(os) {}
//
//};
//template<>
//struct shape_packet<_dotproduct> {
//
//	int row;
//	int col;
//	int order;
//	shape_packet(int ORDER, int r, int c = 1) : row(r), col(c), order(ORDER){}
//};
//template<>
//struct shape_packet<_generic> {
//	_shape shape;
//	shape_packet(_shape sh) : shape(sh) {}
//};
//
//template<>
//struct shape_packet<_subAccessor> {
//	std::vector<int> is;
//	const outer_shape& os;
//	shape_packet(std::vector<int> in, outer_shape out) : is(in), os(out) {}
//};
//
//
//template<class INNER, class OUTER>
//struct Shape : private INNER, private OUTER {
//private:
//	const inner_shape& getInner() const { return *this; }
//	const outer_shape& getOuter() const { return *this; }
//public:
//	static constexpr int COMPILE_TIME_ROWS() { return 0; }
//	static constexpr int COMPILE_TIME_COLS() { return 0; }
//
//		using INNER::rank;
//		using INNER::size;
//		using INNER::rows;
//		using INNER::cols;
//		using INNER::dimension;
//		using INNER::printDimensions;
//		using INNER::InnerShape;
//
//		using OUTER::LD_rows;
//		using OUTER::LD_cols;
//		using OUTER::LD_dimension;
//		using OUTER::OuterShape;
//
//	const bool array_ownership = INNER::parent and OUTER::parent;
//
//	using IS = INNER;
//	using OS = OUTER;
//
//	auto expression_packet() const  { return shape_packet<_expression>(getInner(), getOuter()); }
//	auto shape_copy_packet()		const 	{ _shape sh(this->rank());
//	for (int i = 0; i < this->rank(); ++i) {
//		sh[i] = this->InnerShape()[i];  }
//	 return shape_packet<_generic>(sh);
//	}
//	auto accessor_packet() const    { return shape_packet<_accessor  >(getInner(), getOuter()); }
//	auto transpose_packet() const   { return shape_packet<_transpose>(this->cols(), this->rows(), getOuter()); }
//	auto dotproduct_packet(int eval_order, const Shape& sh) const  { return shape_packet<_dotproduct>(eval_order, this->rows(), sh.cols()); }
//	auto subAccessor_packet(std::vector<int> is) const  { return shape_packet<_subAccessor>(is, getOuter()); }
//
//	const Shape& asShape() const { return *this; }
//	void ChangeShapeOwnership(bool swap = false) {
//		INNER::parent = swap;
//		OUTER::parent = swap;
//	}
//
//
//	Shape(std::initializer_list<int> param) : INNER(param), OUTER(param) {}
//	Shape() : array_ownership(false) {}
//
///*
//
//	void print_() {}
//	template<class T>
//	void print_ (T t) { std::cout << t << std::endl; }
//	template<class...T, class M>
//	void print_(M m, T... t)  { std::cout << m << std::endl; print_(t...); }
//
//*/
//
//	template<class... T>
//	std::vector<int> init(T... set) {
//		return std::vector<int> { set... };
//	}
//
//	template<class pass_type>
//	Shape(shape_packet<pass_type> exp) : INNER(exp.is, pass_type()), OUTER(exp.os, pass_type()) {}
//	Shape(shape_packet<_transpose> exp) : INNER(exp.order == 1 ? init(exp.col) : init(exp.row, exp.col)), //1== Vector, else Matrix order//
//											OUTER(exp.os) {
//	}
//	Shape(shape_packet<_dotproduct> exp) : INNER(exp.order == 1 ? init(exp.row) : init(exp.row, exp.col)), //1== Vector, else Matrix order//
//												OUTER(exp.order == 1 ? init(exp.row) : init(exp.row, exp.col)) {}
//
//	Shape(shape_packet<_subAccessor> exp) : INNER(exp.is), OUTER(exp.os) {}
//
//
//	Shape(shape_packet<_generic> exp) : INNER(exp.shape), OUTER(exp.shape) {}
//	bool resetShape(shape_packet<_generic> exp =  shape_packet<_generic>(_shape(0))) {
//		return this->inner_shape_override(exp.shape) && this->outer_shape_override(exp.shape);
//	}
//
//
//
//};
//
//}
//#endif /* SHAPE_H_ */
//



/*
 * Shape.h
 *
 *  Created on: Jan 18, 2018
 *      Author: joseph
 */


using _shape = std::vector<int>;

#ifndef SHAPE__H_
#define SHAPE__H_

#include <vector>

namespace BC {
class _expression {};
class _accessor {};
class _subAccessor {};
class _transpose {};
class _dotproduct {};
class _generic {};

using _shape = std::vector<int>;

class Shape {

	bool ownership = true;
	int order = is.size();
	int sz;
	_shape is;
	_shape os;

public:


	Shape(_shape is = _shape(0), _shape os = _shape(0), int order = 0, int sz = 1, bool owner = false) : ownership(owner), sz(sz) {
		if (order == -1)
			order = is.size();
		if (sz == -1) {
			if (is.size() > 0) {
				sz = is[0];
				for (int i = 1; i < order; ++i) {
					sz *= is[i];
				}
			}
		}
	}
	Shape(const Shape& sh) : ownership(sh.ownership), sz(sh.sz), order(sh.order), is(sh.is), os(sh.os) {}
	Shape(const Shape&& sh) : ownership(sh.ownership), sz(sh.sz), order(sh.order), is(sh.is), os(sh.os) {}



	static constexpr int COMPILE_TIME_ROWS() { return 0; }
	static constexpr int COMPILE_TIME_COLS() { return 0; }


	int rank() const { return order; }
	int size() const { return sz;    }
	int rows() const { return order > 0 ? is[0] : 1; }
	int cols() const { return order > 1 ? is[1] : 1; }
	int dimension(int i) const { return order > i ? is[i] : 1; }
	void printDimensions() const { for (int i = 0; i < order; ++i) { std::cout << "["<< is[i] << "]"; } std::cout << std::endl; }

	int LD_rows() const { return order > 1 ? os[0] : 1; }
	int LD_cols() const { return order > 2 ? os[1] : 1; }
	int LDdimension(int i) const { return order > i + 1 ? os[i] : 1; }

	const int* InnerShape() const { return &is[0]; }
	const Shape& asShape() const { return *this; }

	bool array_ownership = false;

	auto expression_packet() const  { return *this; }
	auto shape_copy_packet() const 	{ return *this; }
	auto accessor_packet() const    { return Shape(is, os, order -1 , this->size() / is[order - 1]); }
	auto transpose_packet() const   {
		_shape sh = {this->cols(), this->rows()};
		return Shape(sh, os, order, sz, false);
	}

	auto dotproduct_packet(int eval_order, const Shape& sh) const  {
		if (eval_order == 1) {
			return _shape({this->rows()});
		} else {
			return _shape({this->rows(), cols()});
		}
	}
	auto subAccessor_packet(std::vector<int> is) const  { return Shape(is, os); }

	void ChangeShapeOwnership(bool swap = false) {
		array_ownership = false;
	}
	void resetShape(_shape is = _shape(0), _shape os = _shape(0), int order = 0, int sz = 1, bool owner = false) {
		if (!array_ownership) {
			throw std::invalid_argument("tensor must be owner to reset - and change dimensionality");
		}
		if (order == -1)
			order = is.size();
		if (sz == -1) {
			if (is.size() > 0) {
				sz = is[0];
				for (int i = 1; i < order; ++i) {
					sz *= is[i];
				}
			}
		}
	}
};

}
#endif /* SHAPE_H_ */



///




/*
 * Shape.h
 *
 *  Created on: Jan 18, 2018
 *      Author: joseph
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>



//struct inner_shape {
//
//	static constexpr int COMPILE_TIME_ROWS() { return 0; }
//	static constexpr int COMPILE_TIME_COLS() { return 0; }
//
//
//	bool parent;
//	int sz = 1;
//	int *is = &sz;
//	int order = 0 ;
//	int rank() const { return order; }
//	int size() const { return sz; }
//	int rows() const { return order > 0  ? is[0] : 1; }
//	int cols() const { return order > 1  ? is[1] : 1; }
//	int dimension(int i) const { return order > i  ? is[i] : 1; }
//
//	const auto InnerShape() const { return is; }
//
//	inner_shape() : parent(false){}
//	inner_shape(std::initializer_list<int> sh) : order(sh.size()), parent(true) {
//		sz = 1;
//		is = new int[order];
//		for (int i = 0; i < order; ++i) {
//			sz *= sh.begin()[i];
//			is[i] =  sh.begin()[i];
//		}
//	}
//	inner_shape(_shape sh) : order(sh.size()), parent(true) {
//		sz = 1;
//		is = new int[order];
//		for (int i = 0; i < order; ++i) {
//			sz *= sh.begin()[i];
//			is[i] =  sh.begin()[i];
//		}
//	}
//	bool inner_shape_override(_shape sh) {
//		if (!parent) {
//			std::cout << " cannot alter non-parent tensor -- must create a deep copy --" << std::endl;
//			throw std::invalid_argument("Override Nested Shape Illegal");
////			return false;
//		} else {
//			delete[] is;
//
//			is = new int[order];
//			for (int i = 0; i < order; ++i) {
//				sz *= sh.begin()[i];
//				is[i] =  sh.begin()[i];
//			}
//		}
//		return true;
//	}
//
//
//	inner_shape(const inner_shape&  sh, _expression) : parent(false), sz(sh.sz), order(sh.order), is(sh.is) {}
//	inner_shape(const inner_shape&  sh, _accessor  ) : parent(false), sz(sh.sz / sh.is[sh.order - 1]), order(sh.order - 1), is(sh.is) {}
//	~inner_shape() {
//		if (parent) {
//			delete[] is;
//		}
//	}
//
//	void printDimensions() const {
//		for (int i = 0; i < order; ++i) {
//			std::cout << "[" << is[i] << "]";
//		}
//		std::cout << std::endl;
//	}
//};
//
//
//
//struct outer_shape {
//
//	static constexpr int COMPILE_TIME_LD_ROWS() { return 0; }
//	static constexpr int COMPILE_TIME_LD_COLS() { return 0; }
//
//	int one = 1;
//	bool parent = false;
//	int * is = &one;
//	int order = 0;
//
//	int LD_rows() const { return order > 0  ? is[0] : 1; }
//	int LD_cols() const { return order > 1  ? is[1] : 1; }
//	int LD_dimension(int i) const { return order > i  ? is[i] : 1; }
//
//	const auto OuterShape() const { return is; }
//	outer_shape() : parent(false) {}
//	outer_shape(std::initializer_list<int> sh) : order(sh.size()), parent(true) {
//		is = new int[order];
//		for (int i = 0; i < order; ++i) {
//			is[i] =  sh.begin()[i];
//		}
//	}
//	outer_shape(std::vector<int> sh) : order(sh.size()), parent(true) {
//		is = new int[order];
//		for (int i = 0; i < order; ++i) {
//			is[i] =  sh.begin()[i];
//		}
//	}
//	bool outer_shape_override(_shape sh) {
//		if (!parent) {
//			std::cout << "attemping to override  non parent outershape. -- Create a deep copy" << std::endl;
//			throw std::invalid_argument("error");
////			return false;
//		}
//
//		delete[] is;
//		is = new int[order];
//		for (int i = 0; i < order; ++i) {
//			is[i] =  sh.begin()[i];
//		}
//		return true;
//	}
//	outer_shape(const outer_shape& sh) : is(sh.is), parent(false), order(sh.order) {}
//	outer_shape(const outer_shape& sh, _expression) : is(sh.is), parent(false), order(sh.order) {}
//	outer_shape(const outer_shape& sh, _accessor  ) : is(sh.is), parent(false), order(sh.order) {}
//	~outer_shape() {
//		if (parent) {
//			delete[] is;
//		}
//	}
////};
//
//namespace BC {
//
//
//struct _reference { template<class B> struct get { using type = B&; }; };
//struct _value	 { template<class B> struct get { using type = B; }; };
//template<class, class> class dual {};
//
//typedef std::vector<int> _shape;
//
//template<class T>
//struct shape_packet {
//public:
//	_shape is;
//	_shape os;
//	int size;
//	int order;
//	bool ownership;
//
//	shape_packet(const _shape is_, const _shape os_ = _shape(0), int order = 0, int sz = 0, bool own = false) : is(is_), os(os_), order(order), ownership(own) {
//		if (sz == 0) {
//			size = 1;
//			for (int i = 0; i < is.size(); ++i) {
//				size *= is[i];
//			}
//		} else if (order == 0) {
//			if (size != 1) {
//				order = is.size();
//			}
//		}
//		if (os_.size() == 0) {
//			os = _shape(order - 1);
//			os[0] = is[0];
//			for (int i = 1; i < order - 1; ++i) {
//				os[i] = os[i - 1] * is[i];
//			}
//		}
//	}
//};
//
////template<class T, class U, template<class, class> class dual>
////struct shape_packet<dual<T, U>> {
////public:
////	using inner = typename T::get<_shape>::type;
////	using outer = typename U::get<_shape>::type;
////
////	const inner is;
////	const outer os;
////
////	int size;
////	int order;
////
////	shape_packet(const inner is_, const outer os_, int sz = 0, int order = 0) : is(is_), os(os_), order(order) {
////		if (sz == 0) {
////			size = 1;
////			for (int i = 0; i < is.size(); ++i) {
////				size *= is[i];
////			}
////		} else if (order == 0) {
////			if (size != 1) {
////				order = is.size();
////			}
////		}
////	}
////
////
////	shape_packet<dual<T, U>>(shape_packet<dual<T, U>>&& sh) : is(sh.is), os(sh.os), size(sh.size), order(sh.order) {}
////};
//
////template<class INNER, class OUTER>
//struct Shape { //: private INNER, private OUTER {
//public:
//	static constexpr int COMPILE_TIME_ROWS() { return 0; }
//	static constexpr int COMPILE_TIME_COLS() { return 0; }
//
//	_shape is;
//	_shape os;
//
//	int sz;
//	int order;
//
//	int rank() const { return order; }
//	int size() const { return sz;    }
//	int rows() const { return order > 0 ? is[0] : 1; }
//	int cols() const { return order > 1 ? is[1] : 1; }
//	int dimension(int i) const { return order > i ? is[i] : 1; }
//	void printDimensions() const { for (int i = 0; i < order; ++i) { std::cout << "["<< is[i] << "]"; } std::cout << std::endl; }
//
//	const auto InnerShape() const { return &is[0]; }
//
//	int LD_rows() const { return order > 1 ? os[0] : 1; }
//	int LD_cols() const { return order > 2 ? os[1] : 1; }
//	int LDdimension(int i) const { return order > i + 1 ? os[i] : 1; }
//
//	bool array_ownership;
//
//	auto expression_packet() const  { return shape_packet<_reference>(is, os, order, sz, false); }
//
//
//
//
//	auto shape_copy_packet() const 	{ return shape_packet<_reference>(is, os, order, sz, true); }
//
//	auto accessor_packet() const    { return shape_packet<dual<_value, _reference>>(is, os, order - 1, sz/is[order - 1]); }
//	auto transpose_packet() const   { return shape_packet<dual<_value, _reference>>({this->cols(), this->rows()}, os, 2, sz, false); }
//	auto dotproduct_packet(int eval_order, const Shape& sh) const {
//
//		return eval_order == 1 ?
//				shape_packet<_value>({this->rows()}) :
//				shape_packet<_value>({this->rows(), sh.cols()});
//	}
//
//	auto subAccessor_packet(std::vector<int> is) const  { return shape_packet<_value>(is, os, order, sz, false); }
//
//	const Shape& asShape() const { return *this; }
//	void ChangeShapeOwnership(bool swap = false) {
//		array_ownership = swap;
//	}
//
//
//	Shape(_shape param) : array_ownership(true) {
//		shape_packet<_value> sh(param);
//		is = sh.is;
//		os = sh.os;
//		sz = sh.size;
//		order = sh.order;
//	}
//
//	Shape() : array_ownership(false), is(_shape(0)), os(_shape(0)), order(0), sz(1) {}
//
//	template<class T>
//	Shape (shape_packet<T> sh) : is(sh.is), os(sh.os), order(sh.order), sz(sh.size), array_ownership(sh.ownership) {}
//
//	template<class T>
//
//	void resetShape(shape_packet<T> sh) {
//		is = sh.is;
//		os = sh.os;
//		order =sh.order;
//		sz = sh.size;
//		array_ownership = sh.ownership;
//	}
//
//	void resetShape(_shape sh) {
//		resetShape(shape_packet<_value>(sh));
//	}
//
////	template<class pass_type>
////	Shape(shape_packet<pass_type> exp) : INNER(exp.is, pass_type()), OUTER(exp.os, pass_type()) {}
////	Shape(shape_packet<_transpose> exp) : INNER(exp.order == 1 ? init(exp.col) : init(exp.row, exp.col)), //1== Vector, else Matrix order//
////											OUTER(exp.os) {
////	}
////	Shape(shape_packet<_dotproduct> exp) : INNER(exp.order == 1 ? init(exp.row) : init(exp.row, exp.col)), //1== Vector, else Matrix order//
////												OUTER(exp.order == 1 ? init(exp.row) : init(exp.row, exp.col)) {}
////
////	Shape(shape_packet<_subAccessor> exp) : INNER(exp.is), OUTER(exp.os) {}
////
////
////	Shape(shape_packet<_generic> exp) : INNER(exp.shape), OUTER(exp.shape) {}
////	bool resetShape(shape_packet<_generic> exp =  shape_packet<_generic>(_shape(0))) {
////		return this->inner_shape_override(exp.shape) && this->outer_shape_override(exp.shape);
////	}
//
//};
//
//}
//
//#endif /* SHAPE_H_ */
//
//
//

//-------
//
//
///*
// * Shape.h
// *
// *  Created on: Jan 18, 2018
// *      Author: joseph
// */
//
//#ifndef SHAPE_H_
//#define SHAPE_H_
//
//#include <vector>
//
//
//
////struct inner_shape {
////
////	static constexpr int COMPILE_TIME_ROWS() { return 0; }
////	static constexpr int COMPILE_TIME_COLS() { return 0; }
////
////
////	bool parent;
////	int sz = 1;
////	int *is = &sz;
////	int order = 0 ;
////	int rank() const { return order; }
////	int size() const { return sz; }
////	int rows() const { return order > 0  ? is[0] : 1; }
////	int cols() const { return order > 1  ? is[1] : 1; }
////	int dimension(int i) const { return order > i  ? is[i] : 1; }
////
////	const auto InnerShape() const { return is; }
////
////	inner_shape() : parent(false){}
////	inner_shape(std::initializer_list<int> sh) : order(sh.size()), parent(true) {
////		sz = 1;
////		is = new int[order];
////		for (int i = 0; i < order; ++i) {
////			sz *= sh.begin()[i];
////			is[i] =  sh.begin()[i];
////		}
////	}
////	inner_shape(_shape sh) : order(sh.size()), parent(true) {
////		sz = 1;
////		is = new int[order];
////		for (int i = 0; i < order; ++i) {
////			sz *= sh.begin()[i];
////			is[i] =  sh.begin()[i];
////		}
////	}
////	bool inner_shape_override(_shape sh) {
////		if (!parent) {
////			std::cout << " cannot alter non-parent tensor -- must create a deep copy --" << std::endl;
////			throw std::invalid_argument("Override Nested Shape Illegal");
//////			return false;
////		} else {
////			delete[] is;
////
////			is = new int[order];
////			for (int i = 0; i < order; ++i) {
////				sz *= sh.begin()[i];
////				is[i] =  sh.begin()[i];
////			}
////		}
////		return true;
////	}
////
////
////	inner_shape(const inner_shape&  sh, _expression) : parent(false), sz(sh.sz), order(sh.order), is(sh.is) {}
////	inner_shape(const inner_shape&  sh, _accessor  ) : parent(false), sz(sh.sz / sh.is[sh.order - 1]), order(sh.order - 1), is(sh.is) {}
////	~inner_shape() {
////		if (parent) {
////			delete[] is;
////		}
////	}
////
////	void printDimensions() const {
////		for (int i = 0; i < order; ++i) {
////			std::cout << "[" << is[i] << "]";
////		}
////		std::cout << std::endl;
////	}
////};
////
////
////
////struct outer_shape {
////
////	static constexpr int COMPILE_TIME_LD_ROWS() { return 0; }
////	static constexpr int COMPILE_TIME_LD_COLS() { return 0; }
////
////	int one = 1;
////	bool parent = false;
////	int * is = &one;
////	int order = 0;
////
////	int LD_rows() const { return order > 0  ? is[0] : 1; }
////	int LD_cols() const { return order > 1  ? is[1] : 1; }
////	int LD_dimension(int i) const { return order > i  ? is[i] : 1; }
////
////	const auto OuterShape() const { return is; }
////	outer_shape() : parent(false) {}
////	outer_shape(std::initializer_list<int> sh) : order(sh.size()), parent(true) {
////		is = new int[order];
////		for (int i = 0; i < order; ++i) {
////			is[i] =  sh.begin()[i];
////		}
////	}
////	outer_shape(std::vector<int> sh) : order(sh.size()), parent(true) {
////		is = new int[order];
////		for (int i = 0; i < order; ++i) {
////			is[i] =  sh.begin()[i];
////		}
////	}
////	bool outer_shape_override(_shape sh) {
////		if (!parent) {
////			std::cout << "attemping to override  non parent outershape. -- Create a deep copy" << std::endl;
////			throw std::invalid_argument("error");
//////			return false;
////		}
////
////		delete[] is;
////		is = new int[order];
////		for (int i = 0; i < order; ++i) {
////			is[i] =  sh.begin()[i];
////		}
////		return true;
////	}
////	outer_shape(const outer_shape& sh) : is(sh.is), parent(false), order(sh.order) {}
////	outer_shape(const outer_shape& sh, _expression) : is(sh.is), parent(false), order(sh.order) {}
////	outer_shape(const outer_shape& sh, _accessor  ) : is(sh.is), parent(false), order(sh.order) {}
////	~outer_shape() {
////		if (parent) {
////			delete[] is;
////		}
////	}
////};
//
//namespace BC {
//
//
//struct _reference { template<class B> struct get { using type = B&; }; };
//struct _value	 { template<class B> struct get { using type = B; }; };
//template<class, class> class dual {};
//
//typedef std::vector<int> _shape;
//
//template<class T>
//struct shape_packet {
//public:
//	_shape is;
//	_shape os;
//	int size;
//	int order;
//	bool ownership;
//
//	shape_packet(const _shape is_, const _shape os_ = _shape(0), int order = 0, int sz = 0, bool own = false) : is(is_), os(os_), order(order), ownership(own) {
//		if (sz == 0) {
//			size = 1;
//			for (int i = 0; i < is.size(); ++i) {
//				size *= is[i];
//			}
//		} else if (order == 0) {
//			if (size != 1) {
//				order = is.size();
//			}
//		}
//		if (os_.size() == 0) {
//			os = _shape(order - 1);
//			os[0] = is[0];
//			for (int i = 1; i < order - 1; ++i) {
//				os[i] = os[i - 1] * is[i];
//			}
//		}
//	}
//};
//
////template<class T, class U, template<class, class> class dual>
////struct shape_packet<dual<T, U>> {
////public:
////	using inner = typename T::get<_shape>::type;
////	using outer = typename U::get<_shape>::type;
////
////	const inner is;
////	const outer os;
////
////	int size;
////	int order;
////
////	shape_packet(const inner is_, const outer os_, int sz = 0, int order = 0) : is(is_), os(os_), order(order) {
////		if (sz == 0) {
////			size = 1;
////			for (int i = 0; i < is.size(); ++i) {
////				size *= is[i];
////			}
////		} else if (order == 0) {
////			if (size != 1) {
////				order = is.size();
////			}
////		}
////	}
////
////
////	shape_packet<dual<T, U>>(shape_packet<dual<T, U>>&& sh) : is(sh.is), os(sh.os), size(sh.size), order(sh.order) {}
////};
//
////template<class INNER, class OUTER>
//struct Shape { //: private INNER, private OUTER {
//public:
//	static constexpr int COMPILE_TIME_ROWS() { return 0; }
//	static constexpr int COMPILE_TIME_COLS() { return 0; }
//
//	_shape is;
//	_shape os;
//
//	int sz;
//	int order;
//
//	int rank() const { return order; }
//	int size() const { return sz;    }
//	int rows() const { return order > 0 ? is[0] : 1; }
//	int cols() const { return order > 1 ? is[1] : 1; }
//	int dimension(int i) const { return order > i ? is[i] : 1; }
//	void printDimensions() const { for (int i = 0; i < order; ++i) { std::cout << "["<< is[i] << "]"; } std::cout << std::endl; }
//
//	const auto InnerShape() const { return &is[0]; }
//
//	int LD_rows() const { return order > 1 ? os[0] : 1; }
//	int LD_cols() const { return order > 2 ? os[1] : 1; }
//	int LDdimension(int i) const { return order > i + 1 ? os[i] : 1; }
//
//	bool array_ownership;
//
//	auto expression_packet() const  { return shape_packet<_reference>(is, os, order, sz, false); }
//
//
//
//
//	auto shape_copy_packet() const 	{ return shape_packet<_reference>(is, os, order, sz, true); }
//
//	auto accessor_packet() const    { return shape_packet<dual<_value, _reference>>(is, os, order - 1, sz/is[order - 1]); }
//	auto transpose_packet() const   { return shape_packet<dual<_value, _reference>>({this->cols(), this->rows()}, os, 2, sz, false); }
//	auto dotproduct_packet(int eval_order, const Shape& sh) const {
//
//		return eval_order == 1 ?
//				shape_packet<_value>({this->rows()}) :
//				shape_packet<_value>({this->rows(), sh.cols()});
//	}
//
//	auto subAccessor_packet(std::vector<int> is) const  { return shape_packet<_value>(is, os, order, sz, false); }
//
//	const Shape& asShape() const { return *this; }
//	void ChangeShapeOwnership(bool swap = false) {
//		array_ownership = swap;
//	}
//
//
//	Shape(_shape param) : array_ownership(true) {
//		shape_packet<_value> sh(param);
//		is = sh.is;
//		os = sh.os;
//		sz = sh.size;
//		order = sh.order;
//	}
//
//	Shape() : array_ownership(false), is(_shape(0)), os(_shape(0)), order(0), sz(1) {}
//
//	template<class T>
//	Shape (shape_packet<T> sh) : is(sh.is), os(sh.os), order(sh.order), sz(sh.size), array_ownership(sh.ownership) {}
//
//	template<class T>
//
//	void resetShape(shape_packet<T> sh) {
//		is = sh.is;
//		os = sh.os;
//		order =sh.order;
//		sz = sh.size;
//		array_ownership = sh.ownership;
//	}
//
//	void resetShape(_shape sh) {
//		resetShape(shape_packet<_value>(s));
//	}
//
////	template<class pass_type>
////	Shape(shape_packet<pass_type> exp) : INNER(exp.is, pass_type()), OUTER(exp.os, pass_type()) {}
////	Shape(shape_packet<_transpose> exp) : INNER(exp.order == 1 ? init(exp.col) : init(exp.row, exp.col)), //1== Vector, else Matrix order//
////											OUTER(exp.os) {
////	}
////	Shape(shape_packet<_dotproduct> exp) : INNER(exp.order == 1 ? init(exp.row) : init(exp.row, exp.col)), //1== Vector, else Matrix order//
////												OUTER(exp.order == 1 ? init(exp.row) : init(exp.row, exp.col)) {}
////
////	Shape(shape_packet<_subAccessor> exp) : INNER(exp.is), OUTER(exp.os) {}
////
////
////	Shape(shape_packet<_generic> exp) : INNER(exp.shape), OUTER(exp.shape) {}
////	bool resetShape(shape_packet<_generic> exp =  shape_packet<_generic>(_shape(0))) {
////		return this->inner_shape_override(exp.shape) && this->outer_shape_override(exp.shape);
////	}
//
//};
//
//}
//
//#endif /* SHAPE_H_ */
//
//
//
