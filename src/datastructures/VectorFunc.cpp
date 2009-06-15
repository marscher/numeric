/**
 *
 * \ingroup datastructures
 *
 * \brief implements some functions on vectors
 *
 * \version $Revision$
 *
 * $Id$
 * stolen from: http://www.cplusplus.com/forum/general/8493/
 */
#ifndef _VECTORFUNC_CPP
#define	_VECTORRUNC_CPP

#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

/// no need for so long declarations...
typedef std::vector<double> dvector;
typedef std::vector<int> ivector;

template<class T>
std::vector<T>& operator+=(std::vector<T>& x, const std::vector<T>& y) {
	size_t n = x.size();
	for (size_t i = 0; i < n; i++) {
		x[i] += y[i];
	}
	return x;
}

template<class T>
std::vector<T> operator+(const std::vector<T>& x, const std::vector<T>& y) {
	std::vector<T> temp(x);
	temp += y;
	return temp;
}

template<class T>
std::vector<T>& operator-=(std::vector<T>& x, const std::vector<T>& y) {
	size_t n = x.size();
	for (size_t i = 0; i < n; i++) {
		x[i] -= y[i];
	}
	return x;
}

template<class T>
std::vector<T> operator-(const std::vector<T>& x, const std::vector<T>& y) {
	std::vector<T> temp(x);
	temp -= y;
	return temp;
}

/**
 * skalar product
 */
template<class T>
T operator*(const std::vector<T>& x, const std::vector<T>& y) {
	size_t n = y.size();
	T sum = 0;
	for (size_t i = 0; i < n; i++) {
		sum += x[i] * y[i];
	}
	return sum;
}

template<class T>
std::vector<T>& operator*=(std::vector<T>& x, const std::vector<T>& y) {
	size_t n = x.size();
	for (size_t i = 0; i < n; i++) {
		x[i] *= y[i];
	}
	return x;
}

/**
 * vektor * skalar
 */
template<class T>
std::vector<T>& operator*(std::vector<T>& x, T skalar) {
	size_t n = x.size();
	for (size_t i = 0; i < n; i++) {
		x[i] *= skalar;
	}
	return x;
}

template<class T>
T operator/(const std::vector<T>& x, const std::vector<T>& y) {
	size_t n = y.size();
	T sum = 0;
	for (size_t i = 0; i < n; i++) {
		sum += x[i] / y[i];
	}
	return sum;
}

template<class T>
std::vector<T>& operator/=(std::vector<T>& x, const std::vector<T>& y) {
	size_t n = x.size();
	for (size_t i = 0; i < n; i++) {
		x[i] /= y[i];
	}
	return x;
}

template<class T>
T norm2(const std::vector<T>& x, long double p = 2) {
	T sum = 0;
	size_t n = x.size();
	for (size_t i = 0; i < n; i++) {
		sum += abs(pow((long double) x[i], p));
	}
	return sum;
}

/**
 * calcs the p-norm of given vector. If p is not specified euclidian (p = 2) is assumed.
 */
template<class T>
T norm(const std::vector<T>& x, long double p = 2.0) {
	return pow((long double) norm2(x, p), 1 / p);
}

/**
 * writes a string representation of given vector x to given ostream os.
 * It allows calls like std::cout << vector1;
 */
template<class T> std::ostream& operator <<(std::ostream& os,
		const std::vector<T>& x) {
	size_t n = x.size();
	os << '[';
	for (size_t i = 0; i < n; i++) {
		bool b = (i == (n - 1));
		os << x[i] << (b ? "" : ", ");
	}
	os << ']';
	return os;
}

#endif	/* _VECTORFUNC_CPP */
