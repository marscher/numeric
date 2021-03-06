/**
 * \class GS
 *
 * \ingroup algorithms
 *
 * \brief uses the Gaus Seidel method to solve the linear system Ax = b.
 *
 * $Revision$
 *
 * $Id$
 * first created on 11:13:53 2009
 */
#include <iostream>
using namespace std;

#include "GS.h"
#include "../datastructures/VectorFunc.cpp"

GS::GS(const CRS& A, const vector<double>& b) :
	Solver(A, b) {
}

/**
 *  Solves the linear system Ax = b
 * \param epsilon if defect is smaller than this threshold, than the iterative method will stop
 * \param maxIterations the method will only iterate until maxIterations is reached
 * \param timeStepSize time steps (resolution)
 * \param checkInterval how often should be checked whether the convergence criterium is reached
 */
vector<double> GS::solveSystem(double epsilon, unsigned int maxIterations,
		double timeStepSize, unsigned int checkInterval) {

	unsigned int currentIteration = 0;
	int count = 1;
	double defect_old = -1, defect_new;

	const dvector & values = getA().getVal();
	const ivector & rowPtr = getA().getRowPtr();
	const ivector & col = getA().getCol();
	const dvector & b = getB();
	dvector x = dvector(b);
	double t;

	do {
		currentIteration++;
		for (unsigned int i = 0; i < getA().getDimension(); i++) {
			t = 0.0;
			/// for each entry != 0
			for (int j = rowPtr[i]; j < rowPtr[i + 1]; j++) {
				t += values[j] * x[col[j]];
			}
			/// substract with component of the right side of linear system
			t -= b[i];
			/// divide with diagonal coefficient
			t /= values[rowPtr[i]];
			/// adapt the new iterative value
			x[i] -= t;
		}

		/// after checkInterval iterations:
		if (currentIteration == count * checkInterval) {
			count++;
			defect_new = calcDefect(x);
			cout << "# defect: " << defect_new << endl;

			/// check, if we met the convergence criteria
			if (defect_new < epsilon) {
				cout << "# defect < epsilon after " << currentIteration << endl;
				break;
			}

			if (defect_old < 0)
				defect_old = defect_new;

			double c = defect_new / defect_old;
			cout << c << '\n';
			defect_old = defect_new;
		}
	} while (currentIteration < maxIterations);
	cout << "# needed iterations: = " << currentIteration << endl;
	return x;
}
