/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package artificalnetwork;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;
import matrices.Matrix;
import matrices.Vector;

/**
 *
 * @author Joseph
 * 
 * 
 * ** ^l = an index (not power of) **
 *
 * Forward propagation 
 * 
 * for inputLayer (vector / Matrix based algorithm)
 * a^0 = x;
 * for each other layer
 * z ^ L = W^L-1(T) * a^L-1
 * a ^ L = g(z^L)
 * 
 * BackPrpogation
 * 
 * for outputLayer
 * d ^ output = a - y; 
 * for each other layer
 * d ^ L = w ^ L(T) * d ^ L-1  --Note* Andrew Ng's algorithm states to multiply by derivatives, other implementations do not
 *                                              
 * updateWeights
 * W^l,i,j = w^l,i,j + learningRate * d^L+1,i * (derivative) 
 */
public class ArtificalNetwork {

    final int features;
    final int hiddenLayers;
    final int hiddenFeatures;
    final int outputs;
    final int layers;

    final int inputLayer = 0;

    final double tolerance = 1E-100; //if a number is this close to 0 or 1 we round it (in sigmoid and derivative functions)

    double learningRate = .003;
    double intertiaRate = 1E-5;
    private int dataIterations = 0;

    Layer[] network; //Output layer does not have a bias node
    //first is data, second is output
    HashMap<double[], double[]> trainingSet = new HashMap<>();

    public ArtificalNetwork(int features, int hiddenLayers, int hiddenFeatures, int outputs) {
        this.features = features;
        this.hiddenLayers = hiddenLayers;
        this.hiddenFeatures = hiddenFeatures;
        this.outputs = outputs;
        this.layers = hiddenLayers + 2;
        network = new Layer[layers];

        generateNetwork();
    }

    private final void generateNetwork() {
        //adding one to generate Bias unit
        network[0] = new Layer(features + 1, hiddenFeatures);
        for (int i = 1; i < network.length - 2; ++i) {
            network[i] = new Layer(hiddenFeatures + 1, hiddenFeatures);
        }
        network[layers - 2] = new Layer(hiddenFeatures + 1, outputs);        //last hidden layer
        network[layers - 1] = new Layer(outputs, 0);        //output layer
    }

    private void forwardPropagation(double[] data) {
        if (data.length != features) {
            throw new IndexOutOfBoundsException("data must equal features length");
        }
        //Input Layer
        network[0].setA(1, new Vector(data));

        for (int i = 1; i < network.length - 1; ++i) {
            //the first parameter in "set" is the offset - we offset by so we don't "erase" the bias unit
            network[i].setZ((Vector) network[i - 1].w().dotProduct(network[i - 1].a()));
            network[i].setA(1, (g(network[i].z())));
        }
        //For outputLayer
        network[layers - 1].setZ((Vector) network[layers - 2].w().dotProduct(network[layers - 2].a()));
        network[layers - 1].setA((g(network[layers - 1].z())));

        setBiasActivation(); //sets all the first (bias) nodes to 1
    }

    private void setBiasActivation() {
        for (int i = 0; i < network.length - 1; ++i) {
            network[i].a().set(0, 0, 1);
        }
    }

    private void backPropagation(double[] output) {
        //for the output layer ( d = a - y; // we don't need to offset here because output does not have a bias node
        network[layers - 1].setD((Vector) network[layers - 1].a().subtract(new Vector(output)));
        Vector deltaTmp;
        deltaTmp = (Vector) network[layers - 2].w().T().dotProduct(network[layers - 1].d());//for the last hidden layer
        network[layers - 2].setD(deltaTmp.multiply(gD((network[layers - 2].a())))); // multiply be derivative POSSIBLE ERROR?
        //for each hidden layer (exactly the same except we have an offset for the bias unit)

        for (int i = layers - 3; i > -1; --i) {
            deltaTmp = (Vector) network[i].w().T().dotProduct(network[i + 1].d(1)); //this d(1) is an offset so we don't take the dotproduct of the bias
            network[i].setD(deltaTmp.multiply(gD(network[i].a()))); //multiply  derivative POSSIBLE ERROR?
        }
    }

    public void updateWeights() {
        Matrix wTmp;
        for (int i = 0; i < network.length - 2; ++i) {
            wTmp = new Matrix(network[i].w().length(), network[i].w().width());
            wTmp.vertAdd(network[i + 1].d(1));
            wTmp.scale(learningRate, '*');
            wTmp.horzMultiply((network[i].a()));
            network[i].w().addEqual(network[i].m()); // momentum
            network[i].setM(network[i].w().subtract(wTmp).add(network[i].m())); //Momentum 
            network[i].m().scale(intertiaRate, '*'); //momentum
            network[i].w().subtractEqual(wTmp); //Add equal causes deconvergence
        }
        wTmp = new Matrix(network[layers - 2].w().length(), network[layers - 2].w().width());
        wTmp.vertAdd(network[layers - 1].d());
        wTmp.horzMultiply(network[layers - 2].a());
        wTmp.scale(learningRate, '*');
        network[layers - 2].w().addEqual(network[layers - 2].m()); // momentum
        network[layers - 2].setM(network[layers - 2].w().subtract(wTmp).add(network[layers - 2].m())); //Momentum 
        network[layers - 2].m().scale(intertiaRate, '*'); // momentum
        network[layers - 2].w().subtractEqual(wTmp);
    }

    public void setWeight(int layer, int from, int to, double w) {
        network[layer].w().set(to, from, w);
    }

    public void setLearningRate(double d) {
        learningRate = d;
    }

    public void addTrainingData(double[] data, int output) {
        if (data.length != features || output < 0 || output > outputs) {
            throw new IllegalArgumentException();
        }
        double[] yAns = new double[outputs];
        if (output != 0) {
            yAns[output - 1] = 1;
        }
        trainingSet.put(data, yAns);
        forwardPropagation(data);
        backPropagation(yAns);
        updateWeights();

    }

    public void reTrain() {
        for (HashMap.Entry<double[], double[]> entry : trainingSet.entrySet()) {
            forwardPropagation(entry.getKey());
            backPropagation(entry.getValue());
            updateWeights();
        }
        ++dataIterations;
    }

    public void reTrain(int times) {
        for (int i = 0; i < times; ++i) {
            reTrain();
        }
    }

    public double[] Hypothesis(double[] data) {
        if (data.length != features) {
            throw new IllegalArgumentException("Asdfsdd");
        }
        forwardPropagation(data);
        return network[layers - 1].a().toArray();
    }

    private Vector g(Vector v) {
        //returns a new vector scaled to the sigmoid Function (1 / (1 + E^-z))
        double[] vect = new double[v.length()];
        double tmp;
        for (int i = 0; i < v.length(); ++i) {
            tmp = g(v.v(i, 0));
            if (tmp > 1 - tolerance && tmp < 1) {
                tmp = 1;
            } else if (tmp < 0 + tolerance && tmp > 0) {
                tmp = 0;
            }
            vect[i] = tmp;
        }
        return new Vector(vect);
    }

    private Vector gD(Vector gZ) {
        double[] vect = new double[gZ.length()];
        for (int i = 0; i < gZ.length(); ++i) {
            vect[i] = gD(gZ.v(i, 0));
        }
        return new Vector(vect);
    }

    private double g(double z) {
        double tmp = 1 / (1 + Math.pow(2.71828, -z));
        if (tmp > 1 - tolerance && tmp < 1) {
            tmp = 1;
        } else if (tmp < 0 + tolerance && tmp > 0) {
            tmp = 0;
        }
        return tmp;
    }

    private double gD(double gZ) {
        return gZ * (1 - gZ);
    }

    private double getDataIterations() {
        return dataIterations;
    }

    public void printActivations() {
        for (int i = 0; i < network.length; ++i) {
            System.out.println("layer " + i);
            for (int l = 0; l < network[i].a().length(); ++l) {
                for (int w = 0; w < network[i].a().width(); ++w) {
                    System.out.print(network[i].a().v(l, w) + " ");
                }
                System.out.println();
            }
        }
    }

    public void printBackError() {
        for (int i = 1; i < network.length; ++i) {
            System.out.println("layer " + (i + 1));
            for (int l = 0; l < network[i].d().length(); ++l) {
                for (int w = 0; w < network[i].d().width(); ++w) {
                    System.out.print(network[i].d().v(l, w) + " ");
                }
                System.out.println();
            }
        }
    }

    public static void main(String[] args) {
        //oddEvenTest();
        XORTest();
    }

    public static void XORTest() {
        // TODO code application logic here
        Scanner n = new Scanner(System.in);
        ArtificalNetwork ann = new ArtificalNetwork(2, 1, 10, 1);

//        ann.setWeight(0, 0, 0, -3);
//        ann.setWeight(0, 0, 1, 1);
//        ann.setWeight(0, 1, 0, 2);
//        ann.setWeight(0, 1, 1, -2);
//        ann.setWeight(0, 2, 0, 2);
//        ann.setWeight(0, 2, 1, -2);
//        ann.setWeight(1, 0, 0, -1);
//        ann.setWeight(1, 1, 0, 2);
//        ann.setWeight(1, 2, 0, 2);
        double a = 0;
        double b = 0;

        int output;
        String confirm = "";
        while (!confirm.equals("n")) {
            //ann.print();
            System.out.println("-------------------------------------------");
            for (int i = 0; i < 1; ++i) { //30130 iterations 01 is - 9.9E-5 // very close // at 301140 it completely deconverges
                ann.addTrainingData(new double[]{0, 0}, 1); //deconverges at 30300 with learning rate 1.5
                ann.addTrainingData(new double[]{1, 0}, 0);

                ann.addTrainingData(new double[]{0, 1}, 0);
                ann.addTrainingData(new double[]{1, 1}, 1);
                //ann.printBackError();

            }
            //ann.print();
            double[] prediction;

            System.out.println("testing " + 0 + " " + 0);
            prediction = ann.Hypothesis(new double[]{0, 0});
            for (int i = 0; i < prediction.length; ++i) {
                System.out.println(prediction[i] + " ");
            }
            System.out.println("testing " + 0 + " " + 1);
            prediction = ann.Hypothesis(new double[]{0, 1});
            for (int i = 0; i < prediction.length; ++i) {
                System.out.println(prediction[i] + " ");
            }
            System.out.println("testing " + 1 + " " + 0);
            prediction = ann.Hypothesis(new double[]{1, 0});
            for (int i = 0; i < prediction.length; ++i) {
                System.out.println(prediction[i] + " ");
            }
            System.out.println("testing " + 1 + " " + 1);
            prediction = ann.Hypothesis(new double[]{1, 1});
            for (int i = 0; i < prediction.length; ++i) {
                System.out.println(prediction[i] + " ");
            }

            System.out.println("\n DataIterations: " + ann.getDataIterations() + "\n");
//            System.out.println("new learningRate?");
//            confirm = "";
//            while (!confirm.equals("y") && !confirm.equals("n")) {
//                System.out.println("y / n");
//                confirm = n.nextLine();
//            }
//            if (confirm.equals("y")) {
//                ann.setLearningRate(n.nextDouble());
//            }
            System.out.println("Would you like to retrain?");
            confirm = n.nextLine();
            while (!confirm.equals("y") && !confirm.equals("n")) {
                System.out.println("y / n");
                confirm = n.nextLine();
            }
            if (confirm.equals("y")) {
                System.out.println("retrain how many times");
                ann.reTrain(n.nextInt());
            }

        }
    }

    public static void oddEvenTest() {
        System.out.println("----------------Odd Even Test---------------");
        ArtificalNetwork ann = new ArtificalNetwork(3, 1, 300, 1);
        Scanner n = new Scanner(System.in);

//        ann.print();
        double a, b, c;
        a = 0;
        b = 0;
        c = 0;

        for (int i = 0; i < 1000; ++i) {
            ann.addTrainingData(new double[]{0, 0, 0}, 1);
            ann.addTrainingData(new double[]{0, 1, 1}, 1);
            ann.addTrainingData(new double[]{1, 0, 0}, 0);
            ann.addTrainingData(new double[]{1, 1, 1}, 0);
            ann.addTrainingData(new double[]{0, 0, 1}, 0);
            ann.addTrainingData(new double[]{0, 1, 0}, 0);
            ann.addTrainingData(new double[]{1, 0, 1}, 1);
            ann.addTrainingData(new double[]{1, 1, 0}, 1);
        }

        double[] prediction;

        String input = "";
        while (!input.equals("exit")) {
            System.out.println("testing  0 0 0");
            prediction = ann.Hypothesis(new double[]{0, 0, 0});
            for (int i = 0; i < prediction.length; ++i) {
                System.out.println(prediction[i] + " ");
            }
            System.out.println("testing 001");
            prediction = ann.Hypothesis(new double[]{0, 0, 1});
            for (int i = 0; i < prediction.length; ++i) {
                System.out.println(prediction[i] + " ");
            }
            System.out.println("testing 110");
            prediction = ann.Hypothesis(new double[]{1, 1, 0});
            for (int i = 0; i < prediction.length; ++i) {
                System.out.println(prediction[i] + " ");
            }
            System.out.println("testing 111");
            prediction = ann.Hypothesis(new double[]{1, 1, 1});
            for (int i = 0; i < prediction.length; ++i) {
                System.out.println(prediction[i] + " ");
            }
            System.out.println("\n input number of times to to retrain");
            int repeat = n.nextInt();
            if (repeat == 0) {
                System.exit(0);
            } else {
                ann.reTrain(repeat);
            }
        }
    }
}
