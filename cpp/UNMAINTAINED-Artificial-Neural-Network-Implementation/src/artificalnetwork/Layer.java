/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package artificalnetwork;

import matrices.Matrix;
import matrices.Vector;

/**
 *
 * @author Joseph
 */
public class Layer {

    private Vector a;//activation 
    private Vector d;//delta or Error
    private Vector z;//weight * activation
    private Matrix w; //weights
    private Matrix m; //momentum

    final int features;
    final int connections;

    public Layer(int features, int connections) {
        this.features = features;
        this.connections = connections;
        a = new Vector(features);
        d = new Vector(features);
        z = new Vector(features);
        w = new Matrix(connections, features);
        m = new Matrix(connections, features);
        randomize(w);
    }

    public Vector a() {
        return a;
    }

    public Vector a(int offset) {
        double[] offsetVect = new double[a.length() - offset];

        for (int i = offset; i < a.length(); ++i) {
            offsetVect[i - offset] = a.v(i, 0);
        }
        return new Vector(offsetVect);
    }

    public Vector d() {
        return d;
    }

    public Vector d(int offset) {
        double[] offsetVect = new double[d.length() - offset];

        for (int i = offset; i < d.length(); ++i) {
            offsetVect[i - offset] = d.v(i, 0);
        }
        return new Vector(offsetVect);
    }

    public Vector z() {
        return z;
    }

    public Matrix w() {
        return w;
    }

    public Matrix m() {
        return m;
    }

    public void setA(Vector a) {
        if (a.length() != this.a.length()) {
            throw new IndexOutOfBoundsException("length mismatch");
        }
        this.a = a;
    }

    public void setA(int offset, Vector a) {
        for (int i = offset; i < this.a.length(); ++i) {
            this.a.set(i, 0, a.v(i - offset, 0));
        }
    }

    public void setD(Vector d) {
        if (d.length() != this.d.length()) {
            throw new IndexOutOfBoundsException("length mismatch");
        }
        this.d = d;
    }

    public void setD(int offset, Vector d) {
        if (this.d.length() - offset != d.length()) {
            throw new IndexOutOfBoundsException("length offset mismatch");
        }
        for (int i = offset; i < this.d.length(); ++i) {
            this.d.set(i, 0, d.v(i - offset, 0));
        }
    }

    public void setZ(Vector a) {
        if (z.length() != this.z.length()) {
            throw new IndexOutOfBoundsException("length mismatch");
        }
        this.z = a;
    }

    public void setZ(int offset, Vector z) {
        for (int i = offset; i < this.z.length(); ++i) {
            this.z.set(i, 0, z.v(i - offset, 0));
        }
    }

    public void setW(Matrix w) {
        if (w.length() != this.w.length() || w.width() != this.w.width()) {
            throw new IndexOutOfBoundsException("length/width mismatch");
        }
        this.w = w;
    }

    public void setM(Matrix m) {
        if (m.length() != this.m.length() || m.width() != this.w.width()) {
            throw new IndexOutOfBoundsException("length/width mismatch");
        }
        this.m = m;
    }

    private void randomize(Matrix m) {
        for (int l = 0; l < m.length(); ++l) {
            for (int w = 0; w < m.width(); ++w) {
                int a;
                if (Math.round(Math.random()) == 0) {
                    a = -1;
                } else {
                    a = 1;
                }

                m.set(l, w, Math.random() * a * 10);
            }
        }
    }
}
