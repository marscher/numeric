/**
 * \class Solver
 *
 * \ingroup algorithms
 *
 * $Version: $
 *
 * $Id$
 * first created on 12:52:18 2009
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include <vector>
#include "../datastructures/CRS.h"
using std::vector;

class Solver {
public:
	/// constructor
	Solver(const CRS& A, const vector<double>& b);
	virtual ~Solver();

	/// Getter
	const vector<double>& getB() const;
	CRS& getA();

	/// solveSystem() should be implemented by sub classes.
	virtual vector<double> solveSystem(double epsilon,
			const unsigned int maxIterations, double timeStepSize,
			unsigned int checkInterval) = 0;
private:
	vector<double> b;
	CRS A;

	/// Setter
	void setB(const vector<double>&);
	void setA(const CRS&);
};

#endif /* SOLVER_H_ */
