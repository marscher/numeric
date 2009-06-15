/**
 * \class Solver
 *
 * \ingroup algorithms
 *
 * \brief parent class of algorithms solving a linear System Ax = b
 *
 * \version $Revision$
 *
 * $Id$
 */
#include <iostream>
#include "Solver.h"
#include "../datastructures/VectorFunc.cpp"

using std::cout;

Solver::Solver(const CRS& crs, const vector<double>& b) {
	setA(crs);
	setB(b);
}

Solver::~Solver() {

}

inline void Solver::setB(const vector<double>& b) {
	this->b = b;
}

inline void Solver::setA(const CRS& crs) {
	this->A = crs;
}

const vector<double>& Solver::getB() const {
	return b;
}

CRS& Solver::getA() {
	return A;
}

double Solver::calcDefect(const vector<double>& x) {
	double d = norm((getA() * x) - getB());
	cout << "# defect: " << d << '\n';
	return d;
}
