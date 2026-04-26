#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>

class PmergeMe {
	public:
		PmergeMe();										//Default constructor
		~PmergeMe();										//Destructor
		PmergeMe(const PmergeMe &other);				//Copy constructor
		PmergeMe &operator=(const PmergeMe &other);	//Copy operator
	private:

};
#endif
