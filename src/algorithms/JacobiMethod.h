/*
 * JacobiMethod.h
 *
 *  Created on: 22.05.2009
 *      Author: marusha
 */

#ifndef JACOBIMETHOD_H_
#define JACOBIMETHOD_H_
#include <vector>
#include "../datastructures/CRS.h"
using std::vector;
class JacobiMethod {
public:
	JacobiMethod(const CRS& A, const vector<double>& b);

	CRS getA() const {
		return A;
	}

	vector<double> getB() const {
		return b;
	}

	vector<double> solveSystem(double epsilon);

private:
	CRS A;
	vector<double> b;
	void setA(CRS A) {
		this->A = A;
	}
	void setB(vector<double> b) {
		this->b = b;
	}
};

#endif /* JACOBIMETHOD_H_ */
