/**
 * \class DimensionException
 *
 * \ingroup exceptions
 *
 * \brief This exceptions it thrown if the exists a runtime problem due to the dimension of used vectors and or matrices
 *
 * \version $Revision$
 *
 * $Id$
 *
 */
#include "DimensionException.h"
/// inits this exception with what() message msg
DimensionException::DimensionException(const string& msg) {
	// If no message was passed to the constructor, use the default message
	if (msg.size() == 0) {
		this->msg = "Interpreter Exception Detected.";
	} else {
		this->msg = msg;
	}
}

const char* DimensionException::what() const throw() {
	return msg.c_str();
}

// we have to overload destructor too, because def dest. doesnt call throw()
// see http://www.agapow.net/programming/cpp/looser-throw-specifier
DimensionException::~DimensionException() throw() {
	// does nothing
}
