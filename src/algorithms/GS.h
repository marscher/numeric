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

#ifndef GS_H_
#define GS_H_
#include "Solver.h"

class GS : public Solver {
public:
	GS(const CRS& A, const vector<double>& b);
	vector<double> solveSystem(double epsilon, unsigned int maxIterations,
			double timeStepSize, unsigned int checkInterval);
};

#endif /* GS_H_ */
