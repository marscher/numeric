/**
 * \class DimensionException
 *
 * \ingroup exceptions
 * \defgroup exceptions Exceptions
 *
 * \brief This exceptions it thrown if the exists a runtime problem due to the dimension of used vectors and or matrices
 *
 * \version $Revision$
 *
 * $Id$
 *
 */
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
