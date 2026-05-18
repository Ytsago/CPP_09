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

void	printPaired(size_t k, const std::vector<int>& main, const std::vector<int>& pend) {
	std::cout << "k = " << k << std::endl;
	std::cout << "mainCain: " << main << std::endl;
	std::cout << "pendCain: " << pend << std::endl;
}

size_t	jacobsthal(size_t t) {
	size_t	a, b ,c;
	if (t == 0)
		return 0;
	if (t == 1)
		return 1;
	a = 0;
	b = 1;
	for (size_t i = 0; i <= t; i++) {
		c = b + 2 * a;
		a = b, b = c;
	}
	return b;
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
	std::vector<int> mainChain, pendChain;

	mainChain.push_back(0), mainChain.push_back(1 * blockSize);
	size_t	k;
	size_t	nbBlock = main.size() / blockSize;

	for (k = 2; k + 1 < nbBlock; k += 2) {
		pendChain.push_back(k * blockSize);
		mainChain.push_back((k + 1) * blockSize);
	}
	
	if (nbBlock % 2 != 0)
		pendChain.push_back((nbBlock - 1) * blockSize);

	std::vector<int>	sorted;
	sorted.reserve(main.size());

	std::vector<int>::iterator itMain = mainChain.begin();

	for (; itMain != mainChain.end(); itMain++) {
		sorted.insert(sorted.end(), main.begin() + *itMain, main.begin() + *itMain + blockSize);
	}

	main.swap(sorted);
	sorted.clear();
	// std::vector<std::vector<int> >	pend;
	// std::vector<std::vector<int> >	mainChain;
	//
	// mainChain.push_back(extractBlock(main, 0, blockSize));
	// mainChain.push_back(extractBlock(main, blockSize, blockSize));
	//
	// for (size_t i = blockSize *2; i + blockSize * 2 <= main.size(); i += blockSize * 2) {
	// 	pend.push_back(extractBlock(main, i, blockSize));
	// 	mainChain.push_back(extractBlock(main, i + blockSize, blockSize));
	// }
}

// void	PmergeMe::sort(std::vector<int>& in);

bool	PmergeMe::compLow(const std::vector<int>& first, const std::vector<int>& second) {
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
