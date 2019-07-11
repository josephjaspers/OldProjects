package matrices;

import java.util.Arrays;

public class Matrix extends Matrices {

    final double[][] theMatrix;
    final int length;
    final int width;

    public Matrix(double[][] mat) {
        theMatrix = mat;
        length = mat.length;
        width = mat[0].length;
    }

    public Matrix(int length, int width) {
        theMatrix = new double[length][width];

        this.length = length;
        this.width = width;
    }

    public Matrix(int length, int width, double fill) {
        theMatrix = new double[length][width];
        Arrays.fill(theMatrix, fill);

        this.length = length;
        this.width = width;
    }

    @Override
    public void addEqual(Matrices m) {
        if (m.length() != this.length() || m.width() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch");
        }

        for (int l = 0; l < m.length(); ++l) {
            for (int w = 0; w < m.width(); ++w) {
                this.set(l, w, this.v(l, w) + m.v(l, w));
            }
        }
    }

    public void addEqual(int lengthOffset, Matrices m) {
        if (m.length() != this.length() - lengthOffset || m.width() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch" + "\n"
                    + "this: " + this.length + " " + this.width + " param: " + m.length() + " " + m.width());
        }

        for (int l = lengthOffset; l < m.length(); ++l) {
            for (int w = 0; w < m.width(); ++w) {
                this.set(l, w, this.v(l, w) + m.v(l - lengthOffset, w));
            }
        }
    }

    @Override
    public void subtractEqual(Matrices m) {
        if (m.length() != this.length() || m.width() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch");
        }
        for (int l = 0; l < m.length(); ++l) {
            for (int w = 0; w < m.width(); ++w) {
                this.set(l, w, this.v(l, w) - m.v(l, w));
            }
        }
    }

    @Override
    public void timesEqual(Matrices m) {
        if (m.length() != this.length() || m.width() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch");
        }
        for (int l = 0; l < m.length(); ++l) {
            for (int w = 0; w < m.width(); ++w) {
                this.set(l, w, this.v(l, w) * m.v(l, w));
            }
        }
    }

    @Override
    public void divideEqual(Matrices m) {
        if (m.length() != this.length() || m.width() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch");
        }
        for (int l = 0; l < m.length(); ++l) {
            for (int w = 0; w < m.width(); ++w) {
                this.set(l, w, this.v(l, w) / m.v(l, w));
            }
        }
    }

    @Override
    public Matrix add(Matrices m) {
        if (m.length() != this.length() || m.width() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch");
        }

        double[][] newMatrix = new double[this.length()][this.width()];
        for (int l = 0; l < this.length(); ++l) {
            for (int w = 0; w < this.width(); ++w) {
                newMatrix[l][w] = this.v(l, w) + m.v(l, w);
            }
        }
        return new Matrix(newMatrix);
    }

    public Matrix add(int lOffset, Matrices m) {
        if (m.length() != this.length() - lOffset || m.width() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch");
        }

        double[][] newMatrix = new double[this.length()][this.width()];
        for (int l = lOffset; l < this.length(); ++l) {
            for (int w = 0; w < this.width(); ++w) {
                newMatrix[l - lOffset][w] = this.v(l, w) + m.v(l, w);
            }
        }
        return new Matrix(newMatrix);
    }

    @Override
    public Matrix subtract(Matrices m) {
        if (m.length() != this.length() || m.width() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch");
        }

        double[][] newMatrix = new double[this.length()][this.width()];
        for (int l = 0; l < this.length(); ++l) {
            for (int w = 0; w < this.width(); ++w) {
                newMatrix[l][w] = this.v(l, w) - m.v(l, w);
            }
        }
        return new Matrix(newMatrix);
    }

    @Override
    public Matrix divide(Matrices m) {
        if (m.length() != this.length() || m.width() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch");
        }

        double[][] newMatrix = new double[this.length()][this.width()];
        for (int l = 0; l < this.length(); ++l) {
            for (int w = 0; w < this.width(); ++w) {
                newMatrix[l][w] = this.v(l, w) / m.v(l, w);
            }
        }
        return new Matrix(newMatrix);
    }

    @Override
    public Matrix multiply(Matrices m) {
        if (m.length() != this.length() || m.width() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch");
        }

        double[][] newMatrix = new double[this.length()][this.width()];
        for (int l = 0; l < this.length(); ++l) {
            for (int w = 0; w < this.width(); ++w) {
                newMatrix[l][w] = theMatrix[l][w] * m.v(l, w);
            }
        }
        return new Matrix(newMatrix);
    }

    public void vertMultiply(Matrices m) {
        if (!m.isColumnVector()) {
            throw new IllegalArgumentException("vertical multiply can only be applied to column Vectors");
        }
        for (int w = 0; w < this.width(); ++w) {
            for (int l = 0; l < this.length(); ++l) {
                theMatrix[l][w] *= m.v(l, 0);
            }
        }
    }

    public void vertAdd(Matrices m) {
        if (!m.isColumnVector()) {
            throw new IllegalArgumentException("vertical multiply can only be applied to column Vectors");
        }
        for (int w = 0; w < this.width(); ++w) {
            for (int l = 0; l < this.length(); ++l) {
                theMatrix[l][w] += m.v(l, 0);
            }
        }
    }

    public void horzMultiply(Matrices m) {
        if (!m.isColumnVector()) {
            throw new IllegalArgumentException("vertical multiply can only be applied to column Vectors");
        }
        if (m.length() != this.width) {
            throw new IllegalArgumentException("length / width mismatch - param length must equal this width");
        }
        for (int w = 0; w < this.width(); ++w) {
            for (int l = 0; l < this.length(); ++l) {
                theMatrix[l][w] *= m.v(w, 0);
            }
        }
    }

    public void horzAdd(Matrices m) {
        if (!m.isColumnVector()) {
            throw new IllegalArgumentException("vertical add can only be applied to column Vectors");
        }
        if (m.length() != this.width) {
            throw new IllegalArgumentException("length / width mismatch - param length must equal this width");
        }
        for (int w = 0; w < this.width(); ++w) {
            for (int l = 0; l < this.length(); ++l) {
                theMatrix[l][w] += m.v(w, 0);
            }
        }
    }

    @Override
    public Matrices dotProduct(Matrices m) {
        if (m.length() != this.width()) {
            throw new IllegalArgumentException("Matrix length/width mismatch - thisWidth: " + this.width + " mLength: " + m.length());
        }

        double[][] dotP = new double[this.length][m.width()];
        double tmp;

        for (int l = 0; l < this.length; ++l) {
            for (int w = 0; w < m.width(); ++w) {
                tmp = 0;
                for (int l2 = 0; l2 < m.length(); ++l2) {
                    tmp += v(l, l2) * m.v(l2, w);
                }
                dotP[l][w] = tmp;
            }
        }
        if (dotP[0].length == 1) { //Checks if its a column vector if it is we make it into a vector 
            return new Matrix(dotP).vectorSum(); //(vector sum just sums each row but each row has 1 element //possibly a bit slower but easier than adding code)
        } else {
            return new Matrix(dotP);
        }
    }

    @Override
    public double v(int l, int w) {
        return theMatrix[l][w];
    }

    @Override
    public boolean isColumnVector() {
        return this.width() == 1;
    }

    @Override
    public boolean isRowVector() {
        return this.length() == 1;
    }

    @Override
    public int length() {
        return length;
    }

    @Override
    public int width() {
        return width;
    }

    @Override
    public Matrix Transpose() {
        double[][] t = new double[width][length];
        for (int l = 0; l < length; ++l) {
            for (int w = 0; w < width; ++w) {
                t[w][l] = theMatrix[l][w];
            }
        }
        return new Matrix(t);
    }

    @Override
    public void scale(double number, char oper) {
        for (int l = 0; l < length; ++l) {
            for (int w = 0; w < width; ++w) {
                theMatrix[l][w] = calculate(theMatrix[l][w], oper, number);
            }
        }
    }

    @Override
    public double sum() {
        double total = 0;
        for (int l = 0; l < length; ++l) {
            for (int w = 0; w < width; ++w) {
                total += theMatrix[l][w];
            }
        }
        return total;
    }

    public Matrix getColumnVector(int index) {
        double[][] vect = new double[length][1];
        for (int i = 0; i < length; ++i) {
            vect[i][0] = theMatrix[i][index];
        }
        return new Matrix(vect);
    }

    public Matrix getRowVector(int index) {
        double[][] vect = new double[1][width];
        for (int i = 0; i < width; ++i) {
            vect[i][0] = theMatrix[index][i];
        }
        return new Matrix(vect);
    }

    @Override
    public Matrix clone() {
        double[][] mat = new double[length][width];
        for (int l = 0; l < length; ++l) {
            for (int w = 0; w < width; ++w) {
                mat[l][w] = theMatrix[l][w];
            }
        }
        return new Matrix(mat);
    }

    @Override
    public Vector vectorSum() {
        double[] vect = new double[this.length];
        double total = 0;
        for (int l = 0; l < length; ++l) {
            total = 0;
            for (int w = 0; w < width; ++w) {
                total += theMatrix[l][w];
            }
            vect[l] = total;
        }
        return new Vector(vect);
    }

    @Override
    public Vector vectorSumRow() {
        double[] vect = new double[this.width];
        double total = 0;
        for (int w = 0; w < width; ++w) {
            total = 0;
            for (int l = 0; l < length; ++l) {
                total += theMatrix[l][w];
            }
            vect[w] = total;
        }
        return new Vector(vect);
    }

    @Override
    public void set(int l, int w, double value) {
        theMatrix[l][w] = value;
    }

    @Override
    public void print() {
        String border = "     ";
        String p;
        for (int l = 0; l < length; ++l) {
            for (int w = 0; w < width; ++w) {
                p = (theMatrix[l][w] + border);
                System.out.print(p.substring(0, 5) + " ");
            }
            System.out.println();
        }
    }

    public void print(int spacing, int trunc) {
        String border = "";

        int append = 0;
        while (append++ < spacing) {
            border += " ";
        }

        String p;
        for (int l = 0; l < length; ++l) {
            for (int w = 0; w < width; ++w) {
                p = (theMatrix[l][w] + border);
                System.out.print(p.substring(0, Math.min(trunc, p.length())) + " ");
            }
            System.out.println();
        }
    }

    public double[][] toArray() {
        double[][] ary = new double[length][length];

        for (int l = 0; l < length; ++l) {
            for (int w = 0; w < width; ++w) {

                ary[l][w] = theMatrix[l][w];
            }
        }
        return ary;
    }

}
