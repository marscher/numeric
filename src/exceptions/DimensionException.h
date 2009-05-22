//============================================================================
// Name        : DimensionException.h
// Author      : Author: M. Luecke, M. Scherer
// Version     :
//============================================================================
#ifndef _DIMENSIONEXCEPTION_
#define _DIMENSIONEXCEPTION_
#include <exception>
#include <string>
using namespace std;

class DimensionException: public exception {
public:
	DimensionException(const string&);
	const char* what() const throw();
	~DimensionException() throw();
private:
	string msg;
};
#endif
