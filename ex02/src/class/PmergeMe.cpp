#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(const PmergeMe &other) {
	(void) other;
}

PmergeMe	&PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other) {
	}
	return (*this);
}

PmergeMe::~PmergeMe() {
}

std::vector<int>	extractBlock(std::vector<int>& main, size_t start, size_t size) {
	std::vector<int>::iterator	itStart = main.begin() + start;
	std::vector<int>::iterator	itEnd = main.begin() + start + size;
	return std::vector<int>(itStart, itEnd);
}

void	PmergeMe::sort(std::vector<int>& main, size_t blockSize) {
	if (main.size() < 2 * blockSize) return;
	std::vector<int>::iterator it;

	for (it = main.begin(); it + blockSize * 2 <= main.end(); it += 2 * blockSize) {
		if (*(it + blockSize -1) > *(it + 2 * blockSize -1)) {
			std::swap_ranges(it, it + blockSize, it + blockSize);
		}
	}

	std::cout << main << std::endl;
	sort(main, blockSize * 2);
	std::vector<std::vector<int> >	pend;
	std::vector<std::vector<int> >	mainChain;
	
	mainChain.push_back(extractBlock(main, 0, blockSize));
	mainChain.push_back(extractBlock(main, blockSize, blockSize));

	for (size_t i = blockSize *2; i + blockSize * 2 <= main.size(); i += blockSize * 2) {
		pend.push_back(extractBlock(main, i, blockSize));
		mainChain.push_back(extractBlock(main, i + blockSize, blockSize));
	}
}

// void	PmergeMe::sort(std::vector<int>& in);

bool	PmergeMe::compLow(std::vector<int>& first, std::vector<int>& second) {
	if (*first.rbegin() < *second.rbegin())
		return true;
	return false;
}

std::ostream&	operator<<(std::ostream& out, const std::vector<int>& v) {
	std::vector<int>::const_iterator it = v.begin();

	out << "Value: ";
	for (; it != v.end(); it++) {
		out << *it << " ";
	}
	return out;
}

std::ostream&	operator<<(std::ostream& out, const std::deque<int>& d) {
	std::deque<int>::const_iterator it = d.begin();

	out << "Value: ";
	for (; it != d.end(); it++) {
		out << *it << " ";
	}
	return out;
}
