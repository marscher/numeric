/*
 * testJacobi.cpp
 *
 *  Created on: 02.06.2009
 *      Author: marusha
 */
#include "datastructures/CRS.h"
#include "algorithms/JacobiMethod.h"
#include "datastructures/VectorFunc.cpp"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

double f(double x) {
	return -(x * x) + (100* x );
}

int main(int argc, char **argv) {
	int stepSize = 100;
	int dimension = 100;
	int iterations = 10000;
	double epsilon = 10E-8;

	CRS A(CRS::THREE_STAR_OPERATOR, dimension, stepSize);

	//CRS A;
	//A.setStepSize(stepSize);

	/// inits start vector at t = 0.
	/// b = [0, ..., 0] (Dirichlet)
	vector<double> b;

	for (int i = 0; i <= stepSize; i++) { //, x += (float) 1 / stepSize) {
		double y = f(i);
		b.push_back(y);
	}

	JacobiMethod jm(A, b);

	vector<double> result = jm.solveSystem(epsilon, iterations);
	cout<< "result: \n" << result << endl;
	cout << *max_element(result.begin(), result.end());
}
