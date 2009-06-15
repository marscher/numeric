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

#include "Solver.h"
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
