/**
 * \class CG
 *
 * \ingroup algorithms
 *
 * \brief solves the linear system Ax = b using conjugated gradients
 *
 * \version $Revision$
 *
 * $Id$
 * first created on 15.06.2009
 */
#include <iostream>
#include <cmath>
#include "CG.h"
#include "../datastructures/VectorFunc.cpp"
using namespace std;

CG::CG(const CRS& A, const vector<double>& b) :
	Solver(A, b) {
}

CG::~CG() {
	// TODO Auto-generated destructor stub
}

dvector CG::solveSystem(double epsilon, const unsigned int maxIterations,
		double timeStepSize, unsigned int checkInterval) {

	CRS & A = getA(); /// system matrix A
	const dvector & b = getB(); /// right side of linear system

	dvector x(b.size()); /// iterative solution of x
	dvector r; ///
	dvector d;
	dvector Ad;
	double rNew, rOld, alpha, beta, defect_new, defect_old = -1;

	unsigned int currentIteration = 0, count = 1;

	/// init d, r with start vector values
	d = r = b;
	/// init rOld with skalar product of r
	rOld = r * r;

	/// while not reached convergence criterium or max iterations
	do {
		currentIteration++;

		Ad = A * d;

		alpha = rOld / (d * Ad);

		x = x + d * alpha;

		r = r - Ad * alpha;

		rNew = r * r;

		beta = rNew / rOld;

		d = d * beta + r;

		rOld = rNew;

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

	return x;
}
