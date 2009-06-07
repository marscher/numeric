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
#include <vector>
using namespace std;

class GS {
public:
	GS(const vector<double>& b);
	virtual ~GS();
	vector<double>& getB();
	vector<double> solveSystem(int stepSize, double epsilon,
			unsigned int iterations, double timeStepSize,
			unsigned int checkInterval);
private:
	vector<double> b;
	/// Setter
	void setB(const vector<double>&);
};

#endif /* GS_H_ */
