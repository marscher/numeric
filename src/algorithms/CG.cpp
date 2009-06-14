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

	CRS & A = getA();
	const dvector & b = getB();

	dvector x(b.size()), r, d, Ad;
	double rNew, rOld, alpha, beta, defect_new, defect_old;

	unsigned int currentIteration = 0, count = 0;

	d = r = b - A * x;
	rOld = r * r;

	while (currentIteration <= maxIterations) {
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
			defect_new = norm((getA() * x) - b);
			cout << "# defect: " << defect_new << endl;

			/// check, if we met the convergence criteria
			if (defect_new < epsilon) {
				cout << "# defect < epsilon after " << currentIteration << endl;
				//break;
			}

			if (defect_old < 0)
				defect_old = defect_new;

			double c = defect_new / defect_old;
			cout << c << '\n';
			defect_old = defect_new;
		}
	}
	return x;
}
