/**
 * \class CG
 *
 * \ingroup algorithms
 *
 * \version $Revision$
 *
 * $Id$
 * first created on 15.06.2009
 */

#ifndef CG_H_
#define CG_H_

/**
 *
 */
#include "Solver.h"
#include "../datastructures/CRS.h"

class CG: public Solver {
public:
	CG(const CRS& A, const vector<double>& b);
	virtual ~CG();
	vector<double> solveSystem(double epsilon,
			const unsigned int maxIterations, double timeStepSize,
			unsigned int checkInterval);
};

#endif /* CG_H_ */
