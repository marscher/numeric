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
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;

#include "../datastructures/CRS.h"
#include "../algorithms/JacobiMethod.h"
#include "../datastructures/VectorFunc.cpp"
#include "../algorithms/GS.h"

double PI = 3.14159265;

double f(double x) {

	return (-(x * x) + 100* x ) * (rand() % 3 + 1);
	//return 100 * (sin((PI / 2) * ((16* x / 100) - 1)) + 1);
}

/**
 * generates the matrix for solving the one dimensional heat conduction
 * \param stepSize number of grid points
 * \param timeStepSize number of time steps
 */
CRS generateSystemMatrix(int stepSize, double timeStepSize) {
	/// h is equal to the dimension of vector
	double h_square = 1.0 / stepSize * stepSize;
	double theta = (timeStepSize / h_square);
	double diagonalCoefficient = 1 / (1 + (2 * theta));

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

int main(int argc, char **argv) {
	int stepSize = 100;
	double timeStepSize = 0.9;
	unsigned int maxIterations = 10;
	int checkInterval = 1;
	double epsilon = 10E-8;

	/// inits start vector at t = 0.
	/// b = [0, ..., 0] (Dirichlet)
	dvector b;
	b.reserve(stepSize);

	for (int i = 0; i < stepSize; i++) {
		double y = f(i);
		b.push_back(y);
	}

	CRS A = generateSystemMatrix(stepSize, timeStepSize);
	//cout << A.toString() << endl;

	JacobiMethod jm(A, b);
	GS gs(A, b);

	dvector result = jm.solveSystem(epsilon, maxIterations, timeStepSize,
			checkInterval);
	dvector result_gs = gs.solveSystem(epsilon, maxIterations, timeStepSize,
			checkInterval);

	cout << "# result: " << result << endl;

	return 0;
}
