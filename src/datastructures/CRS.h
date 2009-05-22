//============================================================================
// Name        : CRS.h
// Author      : Author: M. Luecke, M. Scherer
// Version     :
//============================================================================

#ifndef CRS_H_
#define CRS_H_
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::vector;

class CRS {
public:
	// constructors
	CRS();
	CRS(const int operatorType, const unsigned int dimension, const unsigned int stepSize);
	CRS(double* val, int* col, int* rowPtr);
	CRS(vector<double>& val, vector<int>& col, vector<int>& rowPtr);
	CRS(const CRS&);

	// constants defining standard operator matrices
	static const int THREE_STAR_OPERATOR = 0x0;
	static const int FOUR_STAR_OPERATOR = 0x1;

	double getElement(int i, int j);

	// Matrix + Matrix
	CRS operator+(const CRS&);

	// Matrix * Vector (Very slow...)
	vector<double> operator*(const vector<double>&);
	void vektorMult(const vector<double>& arg, vector<double>& result);


	vector<double> getTrace();
	void getTrace(vector<double>&);

	// Getter
	const long getNumberOfEntries() const;
	const unsigned int getDimension() const;
	const unsigned int getStepSize() const;

	const vector<int>& getCol() const;
	const vector<int>& getRowPtr() const;
	const vector<double>& getVal() const;

private:
	// containers
	vector<double> val;
	vector<int> col;
	vector<int> rowPtr;

	// stores dimension of this matrix
	unsigned int dimension;
	
	// stores how much entries differing from 0 this matrix has
	long numberOfEntries;
	
	// stores stepSize of grid
	unsigned int stepSize;

	// Setter
	void setDimension(const unsigned int);
	void setNumbersOfEntries(const long);
	void setStepSize(const unsigned int);
	void setCol(const vector<int>&);
	void setRowPtr(const vector<int>&);
	void setVal(const vector<double>&);

	// initialize the containers
	void generateVal(const int operatorType);
	void generateCol(const int operatorType);
	void generateRowPtr(const int operatorType);
};

#endif /* CRS_H_ */
