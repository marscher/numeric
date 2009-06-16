/**
 * \class JacobiMethod
 *
 * \ingroup algorithms
 * \defgroup algorithms Algorithms
 *
 * \brief implements the Jacobi method for the one dimensional heat conduction formula.
 *
 * Jacobi "is a" Solver
 *
 * \version $Revision$
 *
 * $Id$
 *
 */
#ifndef JACOBIMETHOD_H_
#define JACOBIMETHOD_H_

#include "Solver.h"

class JacobiMethod: public Solver {
public:
	/// constructor
	JacobiMethod(const CRS& A, const vector<double>& b);

	vector<double> solveSystem(double epsilon,
			const unsigned int maxIterations, double timeStepSize,
			unsigned int checkInterval = 15);
};

#endif /* JACOBIMETHOD_H_ */
