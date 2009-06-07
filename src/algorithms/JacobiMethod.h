/**
 * \class JacobiMethod
 *
 * \ingroup algorithms
 * \defgroup algorithms Algorithms
 *
 * \brief implements the Jacobi method for the one dimensional heat conduction formula.
 *
 * This class is a datastructure for sparse matrices.
 *
 * \version $Revision$
 *
 * $Id$
 *
 */
#ifndef JACOBIMETHOD_H_
#define JACOBIMETHOD_H_
#include <vector>
#include "../datastructures/CRS.h"
using std::vector;

class JacobiMethod {
public:
	/// constructor
	JacobiMethod(const CRS& A, const vector<double>& b);

	/// Getter
	const vector<double>& getB() const;
	const CRS& getA() const;

	vector<double> solveSystem(double epsilon,
			const unsigned int maxIterations, double timeStepSize,
			unsigned int checkInterval = 15);

private:
	vector<double> b;
	CRS A;

	/// Setter
	void setB(const vector<double>&);
	void setA(const CRS&);
};

#endif /* JACOBIMETHOD_H_ */
