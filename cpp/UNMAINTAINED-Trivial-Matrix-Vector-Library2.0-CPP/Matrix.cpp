#include "Matrix.h"

Matrix::Matrix(unsigned int length, unsigned int width) {
    l = length;
    w = width;
    n = length * width;

    theMatrix = vector<double>(length * width);
}

Matrix::Matrix(const vector<double>& vect) {
    theMatrix = vect;
    l = vect.size();
    w = 1;
    n = l * w;
}

Matrix::Matrix(const vector<vector<double> > & m) {
    l = m.size();
    w = m[0].size();
    n = l * w;

    for (int L = 0; L < m.size(); ++L) {
        if (m[L].size() != w) {
            throw invalid_argument("ragged vector<vector<double>> not applicable");
        }
        for (int W = 0; W < m[L].size(); ++W) {
            theMatrix[index(L, W)] = m[L][W];
        }
    }
}

Matrix::Matrix(unsigned int length) {
    l = length;
    w = 1;
    n = l;
    theMatrix = vector<double>(l);
}

int Matrix::length() const {
    return l;
}

int Matrix::width() const {
    return w;
}

int Matrix::size() const {
    return n;
}

int Matrix::index(unsigned int length, unsigned int width) const {
    bool b = transposed; 
    return length * w + width;
}

Matrix::Matrix(const Matrix& m) {
    theMatrix = m.theMatrix;
    Matrix::l = m.l;
    Matrix::w = m.w;
    Matrix::n = m.n;
}

void Matrix::operator=(const Matrix& m) {
    l = m.l;
    w = m.w;
    n = m.n;
    theMatrix = m.theMatrix;
}

bool Matrix::operator==(const Matrix & m) const {
    if (l != m.l || w != m.w) {
        return false;
    }
    for (int i = 0; i < n; ++i) {
        if (theMatrix[i] != m.theMatrix[i]) {
            return false;
        }
    }
    return true;
}

double& Matrix::operator()(int length, int width) {
    return theMatrix[index(length, width)];
}

double& Matrix::operator[](int index) {
    return theMatrix[index];
}

Matrix Matrix::operator ^ (const Matrix& m) const {
    if (l != m.l || w != m.w) {
        throw invalid_argument("length / width mismatch");
    }
    Matrix mat = Matrix(l, w);
    for (int i = 0; i < n; ++i) {
        mat[i] = pow(theMatrix[i], m.theMatrix[i]);
    }
    return mat;
}

Matrix Matrix::operator*(const Matrix& m) const {
    if (w != m.l) {
        throw range_error("Dot Product length/width mismatch");
    }
    Matrix mat(l, m.w);

    double tmp;
    for (int l = 0; l < length(); ++l) {
        for (int w = 0; w < m.width(); ++w) {
            tmp = 0;
            for (int l2 = 0; l2 < m.length(); ++l2) {
                tmp += theMatrix[index(l, l2)] * m.theMatrix[m.index(l2, w)];
            }
            mat(l, w) = tmp;
        }
    }
    return mat;
}

Matrix Matrix::operator/(const Matrix& m) const {
    if (l != m.l || w != m.w) {
        throw invalid_argument("length / width mismatch");
    }
    Matrix mat = Matrix(l, w);
    for (int i = 0; i < n; ++i) {
        mat[i] = theMatrix[i] / m.theMatrix[i];
    }
    return mat;
}

Matrix Matrix::operator+(const Matrix& m) const {
    if (l != m.l || w != m.w) {
        throw invalid_argument("length / width mismatch");
    }
    Matrix mat = Matrix(l, w);
    for (int i = 0; i < n; ++i) {
        mat[i] = theMatrix[i] + m.theMatrix[i];
    }
    return mat;
}

Matrix Matrix::operator-(const Matrix& m) const {
    if (l != m.l || w != m.w) {
        throw invalid_argument("length / width mismatch");
    }
    Matrix mat = Matrix(l, w);
    for (int i = 0; i < n; ++i) {
        mat[i] = theMatrix[i] - m.theMatrix[i];
    }
    return mat;
}

void Matrix::operator^=(const Matrix& m) {
    if (l != m.l || w != m.w) {
        throw invalid_argument("length / width mismatch");
    }
    for (int i = 0; i < n; ++i) {
        theMatrix[i] = pow(theMatrix[i], m.theMatrix[i]);
    }
}

void Matrix::operator*=(const Matrix& m) {
    if (l != m.l || w != m.w) {
        throw invalid_argument("length / width mismatch");
    }
    for (int i = 0; i < n; ++i) {
        theMatrix[i] *= m.theMatrix[i];
    }
}

void Matrix::operator/=(const Matrix& m) {
    if (l != m.l || w != m.w) {
        throw invalid_argument("length / width mismatch");
    }
    for (int i = 0; i < n; ++i) {
        theMatrix[i] = theMatrix[i] / m.theMatrix[i];
    }
}

void Matrix::operator+=(const Matrix& m) {
    if (l != m.l || w != m.w) {
        throw invalid_argument("length / width mismatch");
    }
    for (int i = 0; i < n; ++i) {
        theMatrix[i] += m.theMatrix[i];
    }
}

void Matrix::operator-=(const Matrix& m) {
    if (l != m.l || w != m.w) {
        throw invalid_argument("length / width mismatch");
    }
    for (int i = 0; i < n; ++i) {
        theMatrix[i] -= m.theMatrix[i];
    }
}

Matrix Matrix::getColumn(unsigned int col) const {
    Matrix m = Matrix(l);

    for (int W = 0; W < m.n; ++W) {
        m[W] = theMatrix[index(col, W)];
    }
    return m;
}

Matrix Matrix::getRow(unsigned int row) const {
    Matrix m = Matrix(w);

    for (int L = 0; L < m.n; ++L) {
        m[L] = theMatrix[index(L, row)];
    }
    return m;
}

bool Matrix::isColumnVector() const {
    return w == 1;
}

bool Matrix::isRowVector() const {
    return l == 1;
}

Matrix Matrix::transpose() const {
    Matrix m = Matrix(w, l);

    for (int L = 0; L < l; ++L) {
        for (int W = 0; W < w; ++W) {
            m(W, L) = theMatrix[index(L, W)];
        }
    }
    return m;
}

void Matrix::print() const {
    for (int l = 0; l < length(); ++l) {
        for (int w = 0; w < width(); ++w){ 
            cout << theMatrix[index(l, w)] << " ";
        }
        cout << endl;
    }
}
void Matrix::print(int p) const {
    cout.precision(p);
    for (int l = 0; l < length(); ++l) {
        for (int w = 0; w < width(); ++w){ 
            cout << theMatrix[index(l, w)] << " ";
        }
        cout << endl;
    }
}


//------------------------------------------------

int main() {
    cout << "Main method - Matrix test class" << endl;
    Matrix x = Matrix(2, 3);
    cout << "initialized x" << endl;
    x(0, 0) = 1;
    x(0, 1) = 2;
    x(0, 2) = 3;
    x(1, 0) = 4;
    x(1, 1) = 5;
    x(1, 2) = 6;

    x.print();

    cout << "x transposed " << endl;
    x.T().print();
    cout << "initialized y" << endl;
    Matrix y = Matrix(3, 2);
    y(0, 0) = 7;
    y(0, 1) = 8;
    y(1, 0) = 9;
    y(1, 1) = 10;
    y(2, 0) = 11;
    y(2, 1) = 12;
    y(2, 1) = 10000;
    y.print();

    Matrix xy = x * y;
    cout << "xy " << endl;
    xy.print();

    cout << " yT - x" << endl;
    xy = y.T() - x;
    Matrix xy2 = xy;
    xy.print();
    int a;
    cin >> a;


    cout << "inti a " << endl;
    //	Matrix a;

}
