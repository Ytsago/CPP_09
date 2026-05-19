#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>

struct Block;

class PmergeMe {
	public:
		static void	sort(std::vector<int>& main, size_t blockSize);
		static void	sort(std::deque<int>& in, size_t blockSize);
	
	private:
		PmergeMe();										//Default constructor
		~PmergeMe();										//Destructor
		PmergeMe(const PmergeMe &other);				//Copy constructor
		PmergeMe &operator=(const PmergeMe &other);	//Copy operator
		bool	compLow(const std::vector<int>& first, const std::vector<int>& second);
};

std::ostream&	operator<<(std::ostream& out, const std::vector<int>& v);
std::ostream&	operator<<(std::ostream& out, const std::deque<int>& d);
std::ostream&	operator<<(std::ostream& out, const std::vector<Block>& v);

#endif
