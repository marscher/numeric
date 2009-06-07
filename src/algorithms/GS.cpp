/**
 * \class GS
 *
 * \ingroup algorithms
 *
 * \brief TODO describe me
 *
 * TODO detailed describtion
 * $Version: $
 *
 * $Id:  $
 * first created on 11:13:53 2009
 */
#include <iostream>

#include "GS.h"
#include "../datastructures/VectorFunc.cpp"

GS::GS(const vector<double>& b) {
	setB(b);
}

GS::~GS() {
	// TODO Auto-generated destructor stub
}

void GS::setB(const vector<double>& b) {
	this->b = b;
}

/**
 * solves the linear system
 * \param stepSize number of grid points
 * \param epsilon if defect is smaller than this threshold, than the iterative method will stop
 * \param maxIterations the method will only iterate until maxIterations is reached
 * \param timeStepSize time steps (resolution)
 * \param checkInterval how often should be checked whether the convergence criterium is reached
 */
vector<double> GS::solveSystem(int stepSize, double epsilon,
		const unsigned int maxIterations, double timeStepSize,
		unsigned int checkInterval = 15) {

	double h_square = 1.0 / (stepSize * stepSize);
	double theta = (timeStepSize / h_square);
	double diagonalCoefficient = 1 / (1 + (2 * theta));
	double factor = theta * diagonalCoefficient;

	/// we start with start values of vector b.
	vector<double> b = getB();
	vector<double> u = b;
	vector<double> u_new(u.size());
	double defect = 1;
	vector<double> convergenceRate;
	unsigned int currentIteration = 0;
	int count = 1;
	do {
		u_new.clear();

		u_new.push_back(diagonalCoefficient * ((theta * u[0]) + b[0]));

		for (size_t i = 1; i < u.size() - 1; i++) {
			u_new.push_back(diagonalCoefficient * ((theta * (u[i + 1] + u_new[i
					- 1])) + b[i]));
		}

		u_new.push_back(diagonalCoefficient * ((theta * (u[u.size()]
				+ u_new[u.size() - 1])) + b[b.size()]));

		if (currentIteration == count * checkInterval) {
			count++;
			//			cout << "u: " << u << endl << "u': " << u_new << endl << "u - u':"
			//					<< u - u_new << endl;
			double defect_new = norm(u - u_new);
			//cout << "defect: " << defect_new << endl;

			/// check, if we met the convergence criteria
			if (defect < epsilon) {
				cout << "defect < epsilon after " << currentIteration << endl;
				break;
			}

			if (currentIteration == 0) {
				defect = defect_new;
			}

			double c = defect_new / defect;
			convergenceRate.push_back(c);
			cout << c << endl;
			defect = defect_new;
		}

		currentIteration++;
		u = u_new;
	} while (currentIteration < maxIterations);
	cout << convergenceRate;
	return u;
}

inline vector<double>& GS::getB() {
	return b;
}
