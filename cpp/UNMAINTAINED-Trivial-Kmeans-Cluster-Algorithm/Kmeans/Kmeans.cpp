// Kmeans.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Kmeans.h"
#include <iostream>

Kmeans::Kmeans(int features, int clusters)
{
	Kmeans::features = features;
	Kmeans::clusters = clusters; 
	dataSet = vector<Point>();
}
void Kmeans::addData(vector<double> data)
{
	if (data.size() != features) {
		throw exception("data length input mismatch");
	}
	dataSet.push_back(data);
}
void Kmeans::cluster()
{
	initializeCentroids();
	while (assignPoints()) {
		averagePoints();
	}
}
vector<vector<double>> Kmeans::getCentroids()
{
	vector<vector<double>> returnVal = vector<vector<double>>(clusters);
	for (int i = 0; i < currCentroids.size(); ++i) {
		returnVal[i] = currCentroids[i].getData();
	}
	return returnVal;
}
bool Kmeans::contains(vector<int> indexes, int cont) {
	for (int i = 0; i < indexes.size(); ++i) {
		if (indexes[i] == cont) {
			return true;
		}
	}
	return false; 
}
void Kmeans::initializeCentroids()
{
	currCentroids = vector<Point>(clusters);
	vector<int> index = vector<int>(clusters); 
	for (int i = 0; i < currCentroids.size(); ++i) {
		int a;
		//do while ensures unique point for each 	
		do {
			a = rand() % (dataSet.size() - 1);
		}
			while (contains(index, a));
		currCentroids[i] = Point(dataSet[a]);
	}
}
bool Kmeans::assignPoints() {
	tmpClusterTotals = vector<int>(clusters);
	int index;
	double dist;
	double tmpDist;
	bool update = false;

	for (int i = 0; i < dataSet.size(); ++i) {
		index = 0;
		dist = dataSet[0].distance(currCentroids[0]);
		for (int f = 0; f < features; ++f) { //start at 1?	
			tmpDist = dataSet[i].distance(currCentroids[f]);		
			if (tmpDist < dist) {
				dist = tmpDist;
				index = f;
			}
		}
		if (dataSet[i].getClusterIndex() != index) {
		dataSet[i].setClusterIndex(index);
		update = true;
		}
		++tmpClusterTotals[index];
	}
	return update;
}
void Kmeans::averagePoints() {
	for (int i = 0; i < clusters; ++i) {
		currCentroids[i] = Point(features);
	}
	bool modified = false;

	for (int i = 0; i < dataSet.size(); ++i) {
		for (int j = 0; j < features; ++j) {
			currCentroids[dataSet[i].getClusterIndex()].getData()[j] += 
				dataSet[i].getData()[j] / (tmpClusterTotals[dataSet[i].getClusterIndex()]);
		}
	}
	cout << "printing avg points " << endl;
		for (int i = 0; i < currCentroids.size(); ++i) {
			for (int j = 0; j < currCentroids[i].getData().size(); ++j) {
				cout << currCentroids[i].getData()[j] << " ";
			}
			cout << endl;
		}
}

int main() {
	Kmeans k = Kmeans(2, 2);

	k.addData(vector<double> {0, 0});
	k.addData(vector<double> {-1, 1});
	k.addData(vector<double> {1, -1});
	k.addData(vector<double> {10, 10});
	k.addData(vector<double> {9, 11});
	k.addData(vector<double> {11, 9});
	k.addData(vector<double> {.5, .5});
	k.addData(vector<double> {-1, 2});
	k.addData(vector<double> {1, -1});
	k.addData(vector<double> {10, 11});
	k.addData(vector<double> {8, 11});
	k.addData(vector<double> {8, 8});


	k.cluster();

	vector<vector<double>> centroids = k.getCentroids();

	cout << "the evaluated points were " << endl;
	for (int l = 0; l < centroids.size(); ++l) {
		for (int w = 0; w < centroids[l].size(); ++w) {
			cout << centroids[l][w] << " ";
		}
		cout << endl;
	}

	int wait;
	cin >> wait;
}