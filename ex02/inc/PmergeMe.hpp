#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>

class PmergeMe {
	public:
		static void	sort(std::vector<int>& main, size_t blockSize);
		static void	sort(std::deque<int>& in);
	
		bool	compLow(std::vector<int>& first, std::vector<int>& second);
	private:
		PmergeMe();										//Default constructor
		~PmergeMe();										//Destructor
		PmergeMe(const PmergeMe &other);				//Copy constructor
		PmergeMe &operator=(const PmergeMe &other);	//Copy operator
};

std::ostream&	operator<<(std::ostream& out, const std::vector<int>& v);
std::ostream&	operator<<(std::ostream& out, const std::deque<int>& d);

#endif
