#pragma once
#ifndef Kmeans_H
#define Kmeans_H
#include "Point.h"
#include <vector>
using namespace std; 

class Kmeans {
	vector<Point> dataSet; //set that holds all the points in the clustered data
	vector<Point> optimalClusters; //The best clusters calculuated so far 

	vector<Point> currCentroids; //current centroids being evaluated
	vector<int> tmpClusterTotals; //tmp cluster totals for averaging

	int clusters; //numb clusters
	int features; // numb features

public:
	Kmeans(int features, int clusters); 
	void addData(vector<double> data);
	void cluster();
	vector<vector<double>> getCentroids();

private:
	bool contains(vector<int> indexes, int cont);
	void initializeCentroids();
	bool assignPoints(); 
	void averagePoints();

};

#endif