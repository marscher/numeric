/**
 * \class Solver
 *
 * \ingroup algorithms
 *
 * \version $Revision$
 *
 * $Id$
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "../datastructures/CRS.h"

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

protected:
	double calcDefect(const vector<double>& x);
};

#endif /* SOLVER_H_ */
