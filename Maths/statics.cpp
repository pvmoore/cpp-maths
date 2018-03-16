#include "_pch.h"
#include "maths.h"

namespace maths {

std::vector<unsigned int> factorsOf(unsigned int n) {
	/// this is not the best way of doing this
	std::vector<unsigned int> factors;
	factors.reserve(n / 2);
	unsigned int i = n;
	while(i>0) {
		if((n%i) == 0) factors.push_back(i);
		i--;
	}
	return factors;
}

}