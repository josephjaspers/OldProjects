#ifndef BlackCat_Tensor_super_h
#define BlackCat_Tensor_super_h

#include "HelperFunctions.h"
#include "Scalar.h"
#include "CPU.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <sstream>
#include <initializer_list>
#include <unordered_map>
#include <map>
#include <vector>

typedef std::vector<unsigned> Shape;

template<typename number_type, class TensorOperations = CPU>
class Tensor  {

	//--------------------------------------------------------Members --------------------------------------------------------//
	const bool tensor_ownership;																		//Ownership - determines if Tensor controls life span of data
	const bool rank_ownership;
	const bool ld_ownership;
	const bool subTensor;

	number_type* tensor = nullptr;																		//tensor - the actual internal array of data
	unsigned* ranks = nullptr;																			//ranks -(dimensions) an array that stores the dimensions of the Tensor
	unsigned* ld = nullptr;																				//LeadingDimension - stores data regarding the leading_dimension

	unsigned sz = 0;																					//sz - total size of data [in non subTensors same as leading_dim]
	unsigned order = 0;																					//order - the number of degree in the matrix [dimensionality]


protected:
	//--------------------------------------------------------Private Constructors--------------------------------------------------------//

	Tensor<number_type, TensorOperations>(const Tensor<number_type, TensorOperations>& m1, const Tensor<number_type, TensorOperations>& m2);
	Tensor<number_type, TensorOperations>(const Tensor<number_type, TensorOperations>& super_tensor, unsigned index);									//Sub_Tensor constructor
	Tensor<number_type, TensorOperations>(const Tensor<number_type, TensorOperations>& super_tensor, Shape index, Shape shape);

	Tensor<number_type, TensorOperations>(const Tensor<number_type, TensorOperations>& cpy_tensor, bool copy_values);									//copy shape constructor
	Tensor<number_type, TensorOperations>(const Tensor<number_type, TensorOperations>& cpy_tensor, bool copy_values,bool transposed);					//copy shape transpose constructor


public:


	//--------------------------------------------------------Public Constructors--------------------------------------------------------//
	//Standard Constructors
	Tensor<number_type, TensorOperations>();																						//Empty initalize
	Tensor<number_type, TensorOperations>(Tensor<number_type, TensorOperations> && cpy);											//move constructor
	Tensor<number_type, TensorOperations>(const Tensor<number_type, TensorOperations>& cpy);									 	//copy constructor
	Tensor<number_type, TensorOperations>(const Shape& shape);																		//Shape constructor

	//Other Constructors
	Tensor<number_type, TensorOperations>(std::initializer_list<unsigned> ranks);													//scaleable shape constructor
	Tensor<number_type, TensorOperations>(unsigned m, unsigned n, unsigned k, unsigned p);
	Tensor<number_type, TensorOperations>(unsigned m, unsigned n, unsigned k);
	Tensor<number_type, TensorOperations>(unsigned m, unsigned n);
	explicit Tensor<number_type, TensorOperations>(unsigned m);

	virtual ~Tensor<number_type, TensorOperations>();

	//--------------------------------------------------------Basic Accessors--------------------------------------------------------//
	unsigned total_matrices()					const;
	bool isInitialized() 						const;
	unsigned matrix_size() 						const;
	unsigned size() 							const;
	unsigned rows() 							const;
	unsigned cols() 							const;
	unsigned pages()							const;
	bool isMatrix() 							const;
	bool isSquare() 							const;
	bool isVector()								const;
	bool isScalar() 							const;
	unsigned rank(unsigned rank_index) 			const;
	unsigned leading_dim(unsigned rank_index) 	const;
	unsigned degree() 							const;
	Shape getShape() 							const;
	unsigned outerLD() 							const;
	unsigned outerRank() 						const;

	//---- Accessors for internal data storage  ----//
	bool owns_ranks() 							const;
	bool owns_tensor() 							const;
	bool owns_LD() 								const;
	bool isSubTensor() 							const;


	//--------------------------------------------------------Simple Mutators--------------------------------------------------------//
	void zeros();
	void fill(number_type);
	void randomize(number_type lower_bound,number_type upper_bound);

	Tensor<number_type, TensorOperations>& reshape(Shape new_shape);
	Tensor<number_type, TensorOperations>& flatten();

	//--------------------------------------------------------Movement Semantics--------------------------------------------------------//

	void reset();
	void reset_post_move();

	//--------------------------------------------------------Debugging Tools--------------------------------------------------------//

	void print() const;
	void printDimensions() const;

	//--------------------------------------------------------Transposition--------------------------------------------------------//

	const   Tensor<number_type, TensorOperations> T() const;
	Tensor<number_type, TensorOperations> transpose() const;

	//--------------------------------------------------------Data Acessors--------------------------------------------------------//
	//----------Access a Scalar----------//

			Scalar<number_type, TensorOperations> operator()(unsigned index);
	  const Scalar<number_type, TensorOperations> operator()(unsigned index) const;

	//----------Access Dimension at index----------//

	  	  Tensor<number_type, TensorOperations> operator[](unsigned index);
	const Tensor<number_type, TensorOperations> operator[](unsigned index) const;

	//----------Access/Generate a SubTensor----------//

	Tensor<number_type, TensorOperations> operator()(Shape index, Shape shape);
	const Tensor<number_type, TensorOperations> operator()(Shape index, Shape shape) const;

public:
	//--------------------------------------------------------Assignment Operators--------------------------------------------------------//

	virtual Tensor<number_type, TensorOperations>& operator=(const Tensor<number_type, TensorOperations>& t);
	virtual Tensor<number_type, TensorOperations>& operator=(Tensor<number_type, TensorOperations>&& t);
	virtual Tensor<number_type, TensorOperations>& operator=(const Scalar<number_type, TensorOperations>& s);
	virtual Tensor<number_type, TensorOperations>& operator=(number_type scalar);

	//--------------------------------------------------------Mathematics--------------------------------------------------------//

	//Mathematics ----- advanced //
	Tensor<number_type, TensorOperations> operator*  			(const Tensor<number_type, TensorOperations>& t) 						   const;
	Tensor<number_type, TensorOperations> operator->*			(const Tensor<number_type, TensorOperations>& t)						   const; //outer product (vector only)
	Scalar<number_type, TensorOperations> corr					(const Tensor<number_type, TensorOperations>& t) 						   const;
	Tensor<number_type, TensorOperations> x_corr				(unsigned move_dimensions, const Tensor<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> x_corr_FilterError	(unsigned move_dimensions, const Tensor<number_type, TensorOperations>& t) const; //accepts the error of the output and returns the error of the filter
	Tensor<number_type, TensorOperations> x_corr_SignalError	(unsigned move_dimensions, const Tensor<number_type, TensorOperations>& t) const; //accepts the error of the output and returns the error of the filter

	Tensor<number_type, TensorOperations> x_corr_full			(unsigned move_dimensions, const Tensor<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> x_corr_stack			(unsigned move_dimensions, const Tensor<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> x_corr_full_stack		(unsigned move_dimensions, const Tensor<number_type, TensorOperations>& t) const;


	//ADJUSTED X CORR IS MY OWN MATHEMATICAL CREATION --> error is calculated with the same function as x_corr filter error and x_corr signal error however
	//the weights must be reconstrained to the range of [0,1] after updating
	Tensor<number_type, TensorOperations> ADJUSTED_x_corr_stack			(unsigned move_dimensions, const Tensor<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> ADJUSTED_x_corr_FilterError	(unsigned move_dimensions, const Tensor<number_type, TensorOperations>& t) const; //accepts the error of the output and returns the error of the filter
	Tensor<number_type, TensorOperations> AdJUSTED_x_corr_SignalError	(unsigned move_dimensions, const Tensor<number_type, TensorOperations>& t) const; //accepts the error of the output and returns the error of the filter


	//Mathematics ----- minimum/maximum
	Scalar<number_type, TensorOperations> max() const;
	Scalar<number_type, TensorOperations> min() const;
	std::pair<Scalar<number_type, TensorOperations>,Tensor<unsigned, CPU>> max_index() const;
	std::pair<Scalar<number_type, TensorOperations>,Tensor<unsigned, CPU>> min_index() const;

	//Mathematics ----- pointwise //
	Tensor<number_type, TensorOperations> operator^(const Tensor<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> operator/(const Tensor<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> operator+(const Tensor<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> operator-(const Tensor<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> operator%(const Tensor<number_type, TensorOperations>& t) const;

	Tensor<number_type, TensorOperations>& operator^=(const Tensor<number_type, TensorOperations>& t);
	Tensor<number_type, TensorOperations>& operator/=(const Tensor<number_type, TensorOperations>& t);
	Tensor<number_type, TensorOperations>& operator+=(const Tensor<number_type, TensorOperations>& t);
	Tensor<number_type, TensorOperations>& operator-=(const Tensor<number_type, TensorOperations>& t);
	Tensor<number_type, TensorOperations>& operator%=(const Tensor<number_type, TensorOperations>& t);

	//--------------------------------------------------------Mathematics (Scalar)--------------------------------------------------------//

	Tensor<number_type, TensorOperations> operator^(number_type scal) const;
	Tensor<number_type, TensorOperations> operator/(number_type scal) const;
	Tensor<number_type, TensorOperations> operator+(number_type scal) const;
	Tensor<number_type, TensorOperations> operator-(number_type scal) const;
	Tensor<number_type, TensorOperations> operator%(number_type scal) const;

	Tensor<number_type, TensorOperations>& operator^=(number_type scal);
	Tensor<number_type, TensorOperations>& operator/=(number_type scal);
	Tensor<number_type, TensorOperations>& operator+=(number_type scal);
	Tensor<number_type, TensorOperations>& operator-=(number_type scal);
	Tensor<number_type, TensorOperations>& operator%=(number_type scal);

	Tensor<number_type, TensorOperations> operator^(const Scalar<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> operator/(const Scalar<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> operator+(const Scalar<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> operator-(const Scalar<number_type, TensorOperations>& t) const;
	Tensor<number_type, TensorOperations> operator%(const Scalar<number_type, TensorOperations>& t) const;

	Tensor<number_type, TensorOperations>& operator^=(const Scalar<number_type, TensorOperations>& t);
	Tensor<number_type, TensorOperations>& operator/=(const Scalar<number_type, TensorOperations>& t);
	Tensor<number_type, TensorOperations>& operator+=(const Scalar<number_type, TensorOperations>& t);
	Tensor<number_type, TensorOperations>& operator-=(const Scalar<number_type, TensorOperations>& t);
	Tensor<number_type, TensorOperations>& operator%=(const Scalar<number_type, TensorOperations>& t);


	//--------------------------------------------------------Boundry Checking--------------------------------------------------------//

	bool same_dimensions				(const Tensor<number_type, TensorOperations>& t) const;
	void assert_same_dimensions			(const Tensor<number_type, TensorOperations>& t) const;

	bool valid_dotProduct				(const Tensor<number_type, TensorOperations>& t) const;
	void assert_dotProduct_dimensions	(const Tensor<number_type, TensorOperations>& t) const;

	bool same_size						(const Tensor<number_type, TensorOperations>& t) const;
	void assert_same_size				(const Tensor<number_type, TensorOperations>& t) const;

	bool valid_convolution_target		(const Tensor<number_type, TensorOperations>& t) const;
	bool valid_correlation_target		(const Tensor<number_type, TensorOperations>& t) const;

	void assert_valid_convolution_target(const Tensor<number_type, TensorOperations>& t) const;
	void assert_valid_correlation_target(const Tensor<number_type, TensorOperations>& t) const;

	static void assert_isVector			(const Tensor<number_type, TensorOperations>& t);
	static void assert_isMatrix			(const Tensor<number_type, TensorOperations>& t);

	//--------------------------------------------------------Get Internal Data--------------------------------------------------------//

	void read		(std::ifstream& is);
	void readCSV	(std::ifstream& is);
	void readCSV	(std::ifstream& is , unsigned numb_values);
	void write		(std::ofstream& os);

	const number_type* data() const { return tensor; }
		  number_type* data() 		{ return tensor; }

	const unsigned* leading_dims() const { return ld; }
		  unsigned* leading_dims() 		 { return ld; }

};
#endif
