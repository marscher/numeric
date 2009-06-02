/*
 * JacobiMethod.cpp
 *
 *  Created on: 22.05.2009
 *      Author: marusha
 */

#include "JacobiMethod.h"
//TODO dont do that!
#include "../datastructures/VectorFunc.cpp"
#include <iostream>
using namespace std;
JacobiMethod::JacobiMethod(const CRS& A, const vector<double>& b) {
	setA(A);
	setB(b);
}

/**!\brief löst das system
 *
 */
vector<double> JacobiMethod::solveSystem(double epsilon,
		unsigned int iterations) {

	CRS & A = getA();
	vector<double> & b = getB();

	int timestepSize = 5; // zeit einheit?
	double h_square = 1.0 / (A.getStepSize() * A.getStepSize());
	double theta = (timestepSize / h_square);
	double diagonalCoefficient = 1 / (1 + (2 * theta));

	/// we start with start values of vector b.
	vector<double> u = b;
	vector<double> u_new(u.size());
	do {
		u_new.clear();
		u_new.push_back(diagonalCoefficient * theta * u[1] / 2);

		for (size_t i = 1; i < u.size() - 1; i++) {
			u_new.push_back(diagonalCoefficient * theta * (u[i + 1] + u[i - 1]));
		}

		u_new.push_back(diagonalCoefficient * theta * u[u.size() - 2] / 2);

		iterations--;
		u = u_new;
	} while (iterations > 0);

	return u;
}

inline void JacobiMethod::setA(const CRS& A) {
	this->A = A;
}

inline void JacobiMethod::setB(const vector<double>& b) {
	this->b = b;
}

CRS& JacobiMethod::getA() {
	return A;
}

vector<double>& JacobiMethod::getB() {
	return b;
}
