#ifdef Matrix_h
#define Matrix_h
#endif
#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
using namespace std;

class Matrix {
    int l;
    int w;
    int n;
    vector<double> theMatrix;

public:
    Matrix(unsigned int length, unsigned int width);
    Matrix(unsigned int length);
    Matrix(const vector<double>& vect);
    Matrix(const vector<vector<double> >& m);
    //cpy constructor
    Matrix(const Matrix& m);
    //cpy assignment
    void operator=(const Matrix& m);
    //comparator
    bool operator==(const Matrix& m) const;
    //simple accessors
    int length() const;
    int width() const;
    int size() const;
    //mutator methods
    double& operator()(int length, int width);
    double& operator[](int index);
    void set(unsigned int lengthOffset, const Matrix& m); 
    void set(unsigned int lengthOffset, unsigned int widthOffset, const Matrix& m);
    //operations 
    Matrix operator ^ (const Matrix & m) const;
    Matrix operator*(const Matrix & m) const;
    Matrix operator/(const Matrix & m) const;
    Matrix operator+(const Matrix & m) const;
    Matrix operator-(const Matrix & m) const;
    //operations = 
    void operator^=(const Matrix & m);
    void operator*=(const Matrix & m);
    void operator/=(const Matrix & m);
    void operator+=(const Matrix & m);
    void operator-=(const Matrix & m);
    //utility methods
    //* getColumn and getRow both return column vectors opposed to a single column matrix and a single row matrix
    Matrix getColumn(unsigned int col) const;
    Matrix getRow(unsigned int row) const;
    bool isColumnVector() const;
    bool isRowVector() const;
    Matrix transpose() const;

    Matrix T() const {
        return transpose();
    }

    Matrix cpy() const;
    Matrix cpy(int rowOffset, int columnOffset) const;
    Matrix cpy(int rowOffset) const;
    
    void print() const;
    void print(int p) const;
private:
    int index(unsigned int l, unsigned int w) const;
};