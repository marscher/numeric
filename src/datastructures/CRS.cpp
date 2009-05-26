//============================================================================
// Name        : CRS.cpp
// Author      : Author: M. Luecke, M. Scherer
// Version     :
//============================================================================
#include <iostream>
#include <exception>
using namespace std;
#include "CRS.h"
#include "../exceptions/DimensionException.h"

/**
 * use this only for debug purposes!
 * i := row index
 * j := column index
 */
double CRS::getElement(int i, int j) {
	double m = 0;
	for (int k = 0; k < rowPtr[i + 1] - rowPtr[i]; k++) {
		if (col[rowPtr[i] + k] == j) {
			m = val[rowPtr[i] + k];
			break;
		}
	}
	return m;
}

/**
 * gets the trace of this matrix
 */
vector<double> CRS::getTrace() {
	vector<double> t = vector<double> (getDimension());

	for (unsigned int i = 0; i < getDimension(); i++) {
		t[i] = getVal()[getRowPtr()[i]];
	}

	return t;
}

/**
 * stores trace of this matrix in given vector t
 */
void CRS::getTrace(vector<double>& t) {
	t = vector<double> (getDimension());

	for (unsigned int i = 0; i < getDimension(); i++) {
		t[i] = getVal()[getRowPtr()[i]];
	}
}
/**
 * TODO impl me
 */
CRS CRS::operator+(const CRS& A) {
	if (A.getDimension() != getDimension())
		throw DimensionException("Dimensions of Argument does not match.");
	unsigned int N = getDimension();

	for (unsigned int i = 0; i < N; i++) {
		// for all entries (!=0) in this row
		for (int j = 0; j < N; j++) {

		}
	}

	CRS result;
	return result;
}

/**
 * TODO impl me
 */
CRS CRS::operator-(const CRS& A) {
	if (A.getDimension() != getDimension())
		throw DimensionException("Dimensions of Argument does not match.");
	unsigned int N = getDimension();
	for (unsigned int i = 0; i < N; i++) {
		// for all entries (!=0) in this row
		for (int j = rowPtr[i]; j < rowPtr[i + 1]; j++) {

		}
	}
	CRS result;
	return result;
}

/**
 * multipies the matrix with v in O(m) timesteps, where m is the number of entries != 0
 */
vector<double> CRS::operator *(const vector<double>& v) {
	unsigned int N = getDimension();
	if (v.size() != N) {
		throw DimensionException("Dimensions do not match each other.");
	}

	// inits N elements with 0.
	vector<double> result(N, 0.0);
	for (unsigned int i = 0; i < N; i++) {
		// for all entries (!=0) in this row
		for (int j = rowPtr[i]; j < rowPtr[i + 1]; j++) {
			// omits multiplication where Matrix[i, j] = 0.
			double c = val[j] * v[col[j]];
			result[i] += c;
		}
	}
	return result;
}

/**
 * multiplies the matrix with v, storing the result in the result reference.
 * actually slower than the overloaded * operator, which seems unlogical, because
 * vector result has to be copied. (perhaps some compiler optimisations...)
 */
void CRS::vektorMult(const vector<double>& v, vector<double>& result) {
	unsigned int N = getDimension();
	if (v.size() != N) {
		throw DimensionException("Dimensions do not match each other.");
	}

	// inits elements with 0.
	result = vector<double> (N, 0.0);
	for (unsigned int i = 0; i < N; i++) {
		// for all entries (!=0) in this row
		for (int j = rowPtr[i]; j < rowPtr[i + 1]; j++) {
			// omits multiplication where Matrix[i, j] = 0.
			double c = val[j] * v[col[j]];
			result[i] += c;
		}
	}
}

/**
 *  TODO Describe me
 */
CRS::CRS(const int operatorType, const unsigned int dimension,
		const unsigned int stepSize) {
	setDimension(dimension);
	setStepSize(stepSize);
	switch (operatorType) {
	case CRS::THREE_STAR_OPERATOR: {
		if (getDimension() < 2)
			throw DimensionException(
					"dimension of three star operator have to be greater than 2.");

		setNumberOfEntries((((dimension - 2) * 3) + 4));
		generateCol(operatorType);
		generateRowPtr(operatorType);
		generateVal(operatorType);
		break;
	}
	case CRS::FOUR_STAR_OPERATOR: {
		//TODO impl me
		break;
	}

	default: {
		cerr << "wrong operator parameter!\n";
		throw exception();
	}
	}
}

/**
 * generates the row ptr array for given operator type
 */
void CRS::generateRowPtr(const int operatorType) {
	int N = getDimension();
	vector<int> rowPtr(N + 1);

	if (operatorType == CRS::THREE_STAR_OPERATOR) {
		rowPtr[0] = 0; // no elements before first row
		rowPtr[1] = 2;
		for (int i = 2; i < N; i++) {
			rowPtr[i] = rowPtr[i - 1] + 3;
		}
		rowPtr[N] = rowPtr[N - 1] + 2;
	}
	setRowPtr(rowPtr);
}

/**
 * generates the val array for given operator type
 */
void CRS::generateVal(const int operatorType) {
	int m = getNumberOfEntries();
	vector<double> val(m);
	double h = getStepSize() * getStepSize();

	if (operatorType == CRS::THREE_STAR_OPERATOR) {
		val[0] = 2 / h;
		val[1] = -1 / h;
		for (int i = 2; i < m - 2;) {
			val[i++] = 2 / h;
			val[i++] = -1 / h;
			val[i++] = -1 / h;
		}
		val[m - 1] = -1 / h;
		val[m - 2] = 2 / h;
	}
	setVal(val);
}
/**
 * generates the col array for given operator type
 */
void CRS::generateCol(const int operatorType) {
	int m = getNumberOfEntries();
	vector<int> col(m);
	if (operatorType == CRS::THREE_STAR_OPERATOR) {
		col[0] = 0;
		col[1] = 1;
		int i = 2;
		int dim = 1;
		while (i < (m - 4)) {
			col[i++] = dim;
			col[i++] = dim - 1;
			col[i++] = dim + 1;
			dim++;
		}
		col[m - 1] = dim - 1;
		col[m - 2] = dim;
	}
	setCol(col);
}

CRS::CRS(double* val, int* col, int* rowPtr, unsigned int dimension,
		unsigned int stepSize) {
	/* // the iterator constructor can also be used to construct from arrays:
	 int myints[] = {16,2,77,29};
	 vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
	 */
	setStepSize(stepSize);
	setDimension(dimension);
	setVal(vector<double> (val, val + sizeof(val) / sizeof(double)));
	setCol(vector<int> (col, col + sizeof(col) / sizeof(int)));
	setRowPtr(vector<int> (rowPtr, rowPtr + sizeof(rowPtr) / sizeof(int)));
}

/**
 * default constructor
 */
CRS::CRS(const vector<double>& val, const vector<int>& col,
		const vector<int>& rowPtr, unsigned int dimension,
		unsigned int stepSize) {
	setVal(val);
	setCol(col);
	setRowPtr(rowPtr);

	setStepSize(stepSize);
	setDimension(dimension);
}

/**
 * copy constructor
 */
CRS::CRS(const CRS& crs) {
	setCol(crs.getCol());
	setRowPtr(crs.getRowPtr());
	setVal(crs.getVal());

	setDimension(crs.getDimension());
	setStepSize(crs.getStepSize());
}

/**
 * creates CRS diagonal matrix out of vector diag
 */
CRS::CRS(vector<double>& diag, unsigned int dimension) {
	setVal(diag);
	setDimension(dimension);

	vector<int> col = vector<int> (diag.size());
	vector<int> rowPtr = vector<int> (diag.size() + 1);

	unsigned int i;
	for (i = 0; i < col.size(); i++) {
		col[i] = i;
		rowPtr[i] = i;
	}
	// TODO test
	rowPtr[i++] = i;

	setCol(col);
	setRowPtr(rowPtr);
}

/**
 * TODO describe me, fix this method!
 */
CRS CRS::getUpperTriangular() {
	unsigned int N = getDimension();
	vector<double> val;
	vector<int> col;
	vector<int> rowPtr;

	for (unsigned int i = 0; i < N; ++i) {
		for (int j = getRowPtr()[i]; j < getRowPtr()[i + 1]; j++) {
			val.push_back(getVal()[j]);
			col.push_back(getCol()[j]);
			rowPtr.push_back(getRowPtr()[j]);
		}
	}
	CRS result = CRS(val, col, rowPtr);
	return result;
}

/**
 * TODO describe me
 */
CRS CRS::getLowerTriangular() {
	CRS result;
	return result;
}

/**
 * do not use this animal!
 */
string CRS::toString() {
	string result = "";
	for (int i = 0; i < getDimension(); i++) {
		for (int j = 0; j < getDimension(); j++) {
			result += getElement(i, j);
		}
	}
	return result;
}

// getter + setter
const long CRS::getNumberOfEntries() const {
	return numberOfEntries;
}

inline void CRS::setNumberOfEntries(const long numberOfEntries) {
	this->numberOfEntries = numberOfEntries;
}

const unsigned int CRS::getDimension() const {
	return dimension;
}

inline void CRS::setDimension(const unsigned int dimension) {
	this->dimension = dimension;
}

const vector<double>& CRS::getVal() const {
	return val;
}

/**
 * sets the value storage and the internal count of entries
 */
inline void CRS::setVal(const vector<double>& val) {
	this->val = val;
	setNumberOfEntries(val.size());
}

const vector<int>& CRS::getCol() const {
	return col;
}

inline void CRS::setCol(const vector<int>& col) {
	this->col = col;
}

const vector<int>& CRS::getRowPtr() const {
	return rowPtr;
}

inline void CRS::setRowPtr(const vector<int>& rowPtr) {
	this->rowPtr = rowPtr;
}

const unsigned int CRS::getStepSize() const {
	return stepSize;
}

inline void CRS::setStepSize(const unsigned int stepSize) {
	this->stepSize = stepSize;
}
