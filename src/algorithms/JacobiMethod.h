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
	// constructor
	JacobiMethod(const CRS& A, const vector<double>& b);

	// Getter
	CRS& getA();
	vector<double>& getB();

	vector<double> solveSystem(double epsilon, unsigned int iterations);

private:
	/// Matrix A, storing
	CRS A;
	vector<double> b;

	/// Setter
	void setA(const CRS&);
	void setB(const vector<double>&);
};

#endif /* JACOBIMETHOD_H_ */
