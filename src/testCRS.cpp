//============================================================================
// Name        : test.cpp
// Author      : Author: M. Luecke, M. Scherer
// Version     :
//============================================================================

#include "datastructures/CRS.h"
#include <iostream>
#include <vector>
using namespace std;

void pressEnter() {
	cin.clear(); // just to ensure there's no junk in the stream which
	cout << "Press Enter / Return to continue...\n";
	cin.ignore(1, 0);
}

int main(int argc, char** argv) {
	// set this to dimension of the three star operator and the unit vector
	const unsigned int dimension = 10000000;
	const unsigned int stepSize = 1;
	try {
		// inits the matrix stored by Compressed Row Storage (CRS)
		// with a three star operator and the given dimension.
		CRS crs = CRS(CRS::THREE_STAR_OPERATOR, dimension, stepSize);
		// inits the unit vector (1, ..., 1)
		vector<double> v(dimension, 1);
		//vector<double> t = crs.getTrace();


		cout << crs.getUpperTriangular().toString() << endl;
		pressEnter();

		// multiplies the matrix with the vector
		vector<double> r = crs * v;
		if (r[0] == 1 && r[r.size() - 1] == 1)
			cout << "test passed\n";

		// show result only for "small" vectors
		if (dimension < 100) {
			cout << "result:\n";
			for (unsigned int i = 0; i < r.size(); i++) {
				cout << '[' << r[i] << "]\n";
			}
			cout.flush();
		}

		//pressEnter();
	} catch (exception& e) {
		cerr << "Exception occured: " << e.what() << endl;
		pressEnter();
	}

	return 0;
}
