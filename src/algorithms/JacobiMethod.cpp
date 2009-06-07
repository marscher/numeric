/**
 * \class JacobiMethod
 *
 * \ingroup algorithms
 *
 * \brief implements the Jacobi method for the one dimensional heat conduction formula.
 *
 * This class is a datastructure for sparse matrices.
 *
 * \author $Author: Author: M. Luecke, M. Scherer $
 *
 * \version $Revision$
 *
 * \date $Date: $
 *
 * $Id$
 *
 */

#include "JacobiMethod.h"
//TODO dont do that!
#include "../datastructures/VectorFunc.cpp"
#include <iostream>
using namespace std;

/**
 * \param A system matrix of the linear system.
 * \param b start vector of system.
 */
JacobiMethod::JacobiMethod(const CRS& A, const vector<double>& b) {
	setA(A);
	setB(b);
}

/**
 * Solves the linear system Ax = b
 *
 * \param epsilon if defect is smaller than this threshold, than the iterative method will stop
 * \param maxIterations the method will only iterate until maxIterations is reached
 * \param timeStepSize time steps (resolution)
 * \param checkInterval how often should be checked whether the convergence criterium is reached
 */
vector<double> JacobiMethod::solveSystem(double epsilon,
		const unsigned int maxIterations, double timeStepSize,
		unsigned int checkInterval) {

	vector<double> convergenceRate;
	unsigned int currentIteration = 0;
	int count = 1;
	double defect_old = -1, defect_new;

	const dvector & values = getA().getVal();
	const ivector & rowPtr = getA().getRowPtr();
	const ivector & col = getA().getCol();

	cout << "val: " << values << endl << "row: " << rowPtr << endl << "col: " << col << endl;

	const dvector & b = getB();

	dvector x = dvector(b), y(b.size());

	do {
		currentIteration++;

		for (unsigned int i = 0; i < getA().getDimension(); i++) {

			double t = 0.0;

			/// for each entry != 0
			for (int j = rowPtr[i]; j < rowPtr[i + 1]; j++) {
				t += values[j] * x[col[j]];
			}

			t -= b[i];
			t /= values[rowPtr[i]]; /// divide with diagonal coefficient
			y[i] = x[i] - t;
		}

		/// after checkInterval iterations:
		if (currentIteration == count * checkInterval) {
			count++;
			defect_new = norm(y - x);
			//cout << "defect: " << defect_new << endl;

			/// check, if we met the convergence criteria
			if (defect_new < epsilon) {
				cout << "defect < epsilon after " << currentIteration << endl;
				break;
			}

			if (defect_old < 0)
				defect_old = defect_new;

			double c = defect_new / defect_old;
			convergenceRate.push_back(c);
			//cout << c << endl;
			defect_old = defect_new;
		}

		///
		cout << "x_i: " << x << endl;
		cout << "x_i+1: " << y << endl;
		x = y;
	} while (currentIteration < maxIterations);

	return y;
}

inline void JacobiMethod::setB(const vector<double>& b) {
	this->b = b;
}

inline void JacobiMethod::setA(const CRS& crs) {
	this->A = crs;
}

const vector<double>& JacobiMethod::getB() const {
	return b;
}

const CRS& JacobiMethod::getA() const {
	return A;
}
