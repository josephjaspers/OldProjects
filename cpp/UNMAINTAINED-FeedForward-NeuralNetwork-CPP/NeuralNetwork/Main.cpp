/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   main.cpp
* Author: joeyj
*
* Created on December 26, 2016, 2:22 PM
*/
#include "stdafx.h"
#include <cstdlib>
#include "NeuralNetwork.h"
#include "Matrix.h"
using namespace std;

/*
*
*/
void print(const vector<double>& v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << endl;
	}
}
int main() {
	NeuralNetwork ann(2, 1, 4, 1);
	ann.addTrainingData(vector<double> {0, 0}, vector<double> {1});
	ann.addTrainingData(vector<double> {1, 0}, vector<double> {0});
	ann.addTrainingData(vector<double> {0, 1}, vector<double> {0});
	ann.addTrainingData(vector<double> {1, 1}, vector<double> {1});
	int retrain = 1;

	while (retrain > 0) {
		std::cout << "retrain how many times" << endl;
		std::cin >> retrain;

		ann.train(retrain);

		std::vector<double> prediction = ann.predict(std::vector<double>{ 1, 1 });
		std::cout << " testing  1 , 1 " << endl;
		for (int i = 0; i < prediction.size(); ++i) {
			std::cout << std::fixed << prediction[i] << " " << std::endl;
		}
		prediction = ann.predict(std::vector<double>{ 0, 0 });
		std::cout << " testing  0 , 0 " << endl;
		for (int i = 0; i < prediction.size(); ++i) {
			std::cout << std::fixed << prediction[i] << " " << std::endl;
		}
		prediction = ann.predict(std::vector<double>{ 0, 1 });
		std::cout << " testing  0 , 1 " << endl;
		for (int i = 0; i < prediction.size(); ++i) {
			std::cout << std::fixed << prediction[i] << " " << std::endl;
		}
		prediction = ann.predict(std::vector<double>{ 1, 0 });
		std::cout << " testing  1 , 0  " << endl;
		for (int i = 0; i < prediction.size(); ++i) {
			std::cout << std::fixed << prediction[i] << " " << std::endl;
		}
		//ann.printNetwork();
	}

	int wait;
	std::cin >> wait;
}