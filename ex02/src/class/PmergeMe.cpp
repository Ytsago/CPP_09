#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
	std::cout << "Default constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &other) : /* copy field */{
	std::cout << "Copy constructor called" << std::endl;
}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		//copy field
	return (*this);
}

PmergeMe::~PmergeMe() {
	std::cout << "Destructor called" << std::endl;
}
