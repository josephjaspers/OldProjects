#ifndef Matrix_h
#define Matrix_h
#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>

using namespace std;

class Matrix {
	int l;
	int w = 1;
	int n;

	double** theMatrix;
	bool initialized = true;

public:
	//Constructors
	Matrix();
	Matrix(unsigned int length, unsigned int width);
	Matrix(const vector<vector<double>>& m);
	Matrix(const Matrix& cpy);
	~Matrix();
	//simple accessors 
	int length() const;
	int width() const;
	int size() const;
	//operators 
	Matrix& operator=(const Matrix & m);
	bool operator== (const Matrix & m) const;
	inline double& operator()(int length, int width);
	Matrix operator^(const Matrix & m) const;
	Matrix operator*(const Matrix & m) const;
	Matrix operator/(const Matrix & m) const;
	Matrix operator+(const Matrix & m) const;
	Matrix operator-(const Matrix & m) const;
	Matrix operator&(const Matrix& m) const;
	Matrix& operator^=(const Matrix & m);
	Matrix& operator/=(const Matrix & m);
	Matrix& operator+=(const Matrix & m);
	Matrix& operator-=(const Matrix & m);
	Matrix& operator&=(const Matrix& m);
	
	Matrix operator^(const double& d) const;
	Matrix operator/(const double& d) const;
	Matrix operator+(const double& d) const;
	Matrix operator-(const double& d) const;
	Matrix operator&(const double& d) const;
	Matrix& operator^=(const double& d);
	Matrix& operator/=(const double& d);
	Matrix& operator+=(const double& d);
	Matrix& operator-=(const double& d);
	Matrix& operator&=(const double& d);

	bool isColumnVector() const;
	bool isRowVector() const;
	Matrix transpose() const;
	Matrix T() const {
		return transpose();
	}
	vector<vector<double>> getCpyVect() const;
	void print() const;
	void print(int p) const;
	static Matrix read(ifstream & f);
	void write(ofstream & o);

	const double& get(int x, int y) const;

private:
	void deleteMatrix();
	void initialize();

	inline void chkBounds(const Matrix& m) const;
	inline void chkBounds(int x, int y) const;
};

#endif