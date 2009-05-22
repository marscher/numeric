//============================================================================
// Name        : DimensionException.cpp
// Author      : Author: M. Luecke, M. Scherer
// Version     :
//============================================================================
#include "DimensionException.h"
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
