/*
 * JacobiMethod.cpp
 *
 *  Created on: 22.05.2009
 *      Author: marusha
 */

#include "JacobiMethod.h"
//TODO dont do that!
#include "../datastructures/VectorFunc.cpp"

JacobiMethod::JacobiMethod(const CRS& A, const std::vector<double>& b) {
	setA(A);
	setB(b);
}

vector<double> JacobiMethod::solveSystem(double epsilon) {
	CRS A = getA();
	vector<double> diag = A.getTrace();

	// invert diag
	for (unsigned int i = 0; i < diag.size(); ++i) {
		diag[i] = 1 / diag[i];
	}

	CRS D_inv = CRS(diag);
	CRS L = A.getLowerTriangular(), U = A.getUpperTriangular(); //TODO L, U erzeugen!
	vector<double> b = getB();
	//TODO abbruchbedingung?
	vector<double> x_m = D_inv * (b - ((L + U) * x_m));

	return x_m;
}

void JacobiMethod::setA(const CRS& A) {
	this->A = A;
}

void JacobiMethod::setB(const vector<double>& b) {
	this->b = b;
}

CRS& JacobiMethod::getA() {
	return A;
}

vector<double>& JacobiMethod::getB() {
	return b;
}
