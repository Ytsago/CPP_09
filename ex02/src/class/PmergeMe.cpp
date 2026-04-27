#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(const PmergeMe &other) : /* copy field */{
}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other)
		//copy field
	return (*this);
}

PmergeMe::~PmergeMe() {
}
