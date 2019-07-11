========================================================================
    CONSOLE APPLICATION : jANN Project Overview
========================================================================
Author Joseph Jaspers

This is an implementation of a feed forward Neural Network. The implementation is to be utilized as a framework.

Overview of FF Neural Network:
A Feed Forward Network requires 2 primary algorithms, forward propation and backward propagation. 

Forward Propagation is the method utilized to enable the Neural Network to proccess the data through it's trained weights. 

A single layer implementation is notated as:

a[l] = g(w[l-1] * a[l - 1] + b[l - 1]);

where 
"a" is a vector denoting activations
"w" is a matrix denoting weights.
"b" is a vector denoting bias
 g  is a nonlinearity function, generally the sigmoidFunction.

 *  is a the dot product of a the Matrix w and Vector a;
 +  is the pointwise summation of the vector b and the vector of (w * a)

The sigmoid function squashes the values of the w * a + b into the range of [0, 1].
It should be noted that the initial inputs of the NN should likewise be normalized into the range of [0, 1]. 

This forwardpass calculation is repeated for each layer of the NN. 

Backward Propagation, is the method for calculating the error of the Neural Network and updating the weights of the NN. 

The error of the output layer (the last layer) may be calculated as the hypothesis - expected value. 
Where hypothesis (h) and expected (e) are Vectors within a [0, 1] range. 

The hypothesis of the NN is the equivalent to the activations of the last layer of the NN. 

the output delta(error) is calculated as: 
d[output layer] = a[output layer] - expected output

for each of the hidden layers the error is calculated as follows: 
d[l] = (w[l].T() * d[l + 1]) x gD(a[l]); 

where:
 "d"  is the vector of deltas or error
 .T() is the transposition of the weight matrices.
  x   x is the pointwise multiplication of two vectors (or matrices) 
  gD(X) is the derivative of the nonlinearity function (in this case the sigmoid).

 The sigmoid functions derivative is multiplied as the delta is considered to be a function of a function. We may utilize the same activations that have already run through the sigmoid function. 

Sigmoid function 	= 1 / (1 + e^-x).
Derivative of Sigmoid 	= (1 / (1 + e^-x) * (1 - (1 / (1 + e^-x))
So.....  
we may use the old activations because.... gD(x) = g(x) * (1 - g(x))

For each layer we may calculate the delta.
From this we may update the weights with following calculation...
w[l]  = w[l] - (d[l + 1] * a[l]) x lr

where:
 * is the outer product of two Vectors 
 lr is the learning rate (Values generally range of [0, 1]).

This calculations takes the error of each activation and updates the weights according to its own activation and the delta. IE Larger activations contribute to the error more so then smaller values).
The lr is a small value that scales the shift into a range to avoid deconvergence of the NN during training. (Not covered in this). 

/////////////////////////////////////////////////////////////////////////////
