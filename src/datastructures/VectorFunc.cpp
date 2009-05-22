// stolen from: http://www.cplusplus.com/forum/general/8493/

#ifndef _VECTORFUNC_H
#define	_VECTORRUNC_H

#include <cstdlib>
#include <cmath>
#include <vector>

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
template<class T>
T norm(const std::vector<T>& x, long double p = 2.0) {
	return pow((long double) norm2(x, p), 1 / p);
}

#endif	/* _VECTORFUNC_H */
