/**
 * generates the system matrix A and the start vector b
 * and solves the linear system using the parameters stepSize and timeStepSize.
 *
 * \version $Revision$
 * *
 * $Id$
 *
 * Created on: 02.06.2009
 */
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

#include "../datastructures/CRS.h"
#include "../algorithms/JacobiMethod.h"
#include "../datastructures/VectorFunc.cpp"
#include "../algorithms/GS.h"
#include "../algorithms/CG.h"

double PI = 3.14159265;

double f(double x) {
	return (sin(x * 100 - PI / 2) + 1) * 100;
}

/**
 * generates the matrix for solving the one dimensional heat conduction
 * \param stepSize number of grid points
 * \param timeStepSize number of time steps
 */
CRS generateSystemMatrix(int stepSize, double timeStepSize) {
	/// h is equal to the dimension of vector
	double h_square = 1.0 / stepSize * stepSize;
	double theta = timeStepSize / h_square;
	double diagonalCoefficient = 1.0 + 2 * theta;

	/// number of entries
	int m = ((stepSize - 2) * 3) + 4;

	/// init value array
	dvector values;
	values.reserve(m);

	values.push_back(diagonalCoefficient);
	values.push_back(-theta);
	int i;
	for (i = 2; i < m - 2;) {
		values.push_back(diagonalCoefficient);
		values.push_back(-theta);
		values.push_back(-theta);
		i += 3;
	}

	values.push_back(diagonalCoefficient);
	values.push_back(-theta);

	ivector col(m);

	col[0] = 0;
	col[1] = 1;

	i = 2;
	int dim = 1;

	while (i < (m - 4)) {
		col[i++] = dim;
		col[i++] = dim - 1;
		col[i++] = dim + 1;
		dim++;
	}

	col[m - 1] = dim - 1;
	col[m - 2] = dim;

	/// generate RowPtr Array
	ivector rowPtr(stepSize + 1);

	rowPtr[0] = 0; /// no elements before first row
	rowPtr[1] = 2;
	for (int i = 2; i < stepSize; i++) {
		rowPtr[i] = rowPtr[i - 1] + 3;
	}

	rowPtr[stepSize] = rowPtr[stepSize - 1] + 2;

	CRS A(values, col, rowPtr, stepSize, stepSize);

	return A;
}

void printHelp() {
	cout << "-h step size of 2D-Grid" << endl << "-t time step size" << endl
			<< "-c how much iterations should be made before defect is calculated"
			<< endl << "-m method to use (int) 0, 1, 2" << endl
			<< "-i maximum iterations (int)" << endl << "--help this message"
			<< endl;
}

int main(int argc, char **argv) {
	/// Default values
	int stepSize = 100;
	double timeStepSize = 1.0;
	unsigned int maxIterations = 1000;
	int checkInterval = 1;
	double epsilon = 10E-8;
	int method = 0; /// Jacobi

	/// check arguments of program for overwriting default values
	vector<const char*> v(argv, argv + argc);
	vector<const char*>::iterator i;
	cout << "# command line: ";
	for (i = v.begin(); i != v.end(); i++) {
		cout << *i << ' ';
		if (strcmp(*i, "-m") == 0) {
			method = atoi(*(i + 1));
			continue;
		}
		if (strcmp(*i, "-h") == 0) {
			stepSize = atoi(*(i + 1));
			continue;
		}
		if (strcmp(*i, "-t") == 0) {
			timeStepSize = atof(*(i + 1));
			continue;
		}
		if (strcmp(*i, "-c") == 0) {
			checkInterval = atoi(*(i + 1));
			continue;
		}
		if (strcmp(*i, "-i") == 0) {
			maxIterations = atoi(*(i + 1));
			continue;
		}
		if (strcmp(*i, "--help") == 0) {
			printHelp();
			return 0;
		}
	}

	cout << "\n\n# using following values:\n" << "# stepSize: " << stepSize
			<< "\n# timeStepSize: " << timeStepSize << "\n# checkInterval: "
			<< checkInterval << "\n# maxIterations: " << maxIterations
			<< "\n# method : " << method << endl;

	/// init start vector at t = 0.
	/// b = [0, x1, x2, ..., xn-1, 0] (Dirichlet)
	dvector b;
	b.reserve(stepSize + 1);

	double arg = 0.0;
	for (int i = 0; i <= stepSize; i++) {
		double y = f(arg);
		b.push_back(y);
		//cout << "f(" << x << ") = " << y << endl;
		arg += 1.0 / stepSize + 1;
	}

	cout << "# start vector:\n" << b << endl;

	/// init system matrix A
	CRS A = generateSystemMatrix(stepSize + 1, timeStepSize);

	dvector x;

	switch (method) {
	case 0: {
		JacobiMethod jm(A, b);
		cout << "# starting calculation using Jacobi...\n";
		x = jm.solveSystem(epsilon, maxIterations, timeStepSize, checkInterval);
		break;
	}
	case 1: {
		GS gs(A, b);
		cout << "# starting calculation using Gaus Seidel...\n";
		x = gs.solveSystem(epsilon, maxIterations, timeStepSize, checkInterval);
		break;
	}
	case 2: {
		CG cg(A, b);
		cout << "# starting calculation using CG (Conjugated Gradients)...\n";
		x = cg.solveSystem(epsilon, maxIterations, timeStepSize, checkInterval);
		break;
	}
	default:
		cerr << "No valid method specified!" << endl;
		break;
	}
	cout << "# result: \n" << "\n# " << x << endl;
	return 0;
}
