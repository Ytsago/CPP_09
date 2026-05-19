#include "PmergeMe.hpp"
#include <algorithm>

struct Block {
	size_t	id;
	size_t	offset;
	Block(size_t i, size_t of) : id(i), offset(of) {}
};

struct MatchId {
	size_t	targetId;
	MatchId(size_t id) : targetId(id) {}
	bool	operator()(const Block& b) const {return b.id == targetId;}
};

struct	CompBlock {
	const std::vector<int>&	mainRef;
	const size_t	blockSize;
	CompBlock(const std::vector<int>& main, size_t blockSize) : mainRef(main), blockSize(blockSize) {}
	bool	operator()(const Block& a, const Block& b) const {
		return mainRef[a.offset + blockSize -1] < mainRef[b.offset + blockSize -1];
	}
};

struct	CompDequeBlock {
	const std::deque<int>&	mainRef;
	const size_t	blockSize;
	CompDequeBlock(const std::deque<int>& main, size_t blockSize) : mainRef(main), blockSize(blockSize) {}
	bool	operator()(const Block& a, const Block& b) const {
		return mainRef[a.offset + blockSize -1] < mainRef[b.offset + blockSize -1];
	}
};

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

void	printPaired(size_t k, const std::vector<Block>& main, const std::vector<Block>& pend) {
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
	for (size_t i = 2; i <= t; i++) {
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

	// std::cout << main << std::endl;
	sort(main, blockSize * 2);
	std::vector<Block> mainChain, pendChain;

	mainChain.push_back(Block(0,0)), mainChain.push_back(Block(0, 1 * blockSize));
	size_t	k;
	size_t	nbBlock = main.size() / blockSize;
	size_t	currentId = 1;

	for (k = 2; k + 1 < nbBlock; k += 2) {
		pendChain.push_back(Block(currentId, k * blockSize));
		mainChain.push_back(Block(currentId, (k + 1) * blockSize));
		currentId++;
	}
	
	if (nbBlock % 2 != 0)
		pendChain.push_back(Block(static_cast<size_t>(-1), (nbBlock - 1) * blockSize));

	std::vector<int>	sorted;
	sorted.reserve(main.size());

	// printPaired(k, mainChain, pendChain);
	size_t	currJ, lastJ;

	lastJ = 0;
	for (size_t t = 3; lastJ <= pendChain.size(); t++) {
		currJ = jacobsthal(t);
		size_t	end = std::min(currJ, pendChain.size());
		for (size_t i = end; i > lastJ; --i) {
			std::vector<Block>::iterator searchEnd = mainChain.end();
			Block toInsert = pendChain[i - 1];
			// std::cout << "Block: " << toInsert.id << ", " << toInsert.offset << std::endl; 
			if (toInsert.id != static_cast<size_t>(-1)) {
				searchEnd = std::find_if(mainChain.begin(), mainChain.end(), MatchId(toInsert.id));
				if (searchEnd != mainChain.end())
					searchEnd += 1;
			}
			std::vector<Block>::iterator binaryInsert = std::lower_bound(mainChain.begin(), searchEnd, toInsert, CompBlock(main, blockSize));
			mainChain.insert(binaryInsert, toInsert);
		}
		lastJ = currJ;
	}

	// printPaired(k, mainChain, pendChain);
	for (size_t i = 0; i < mainChain.size(); i++) {
		sorted.insert(sorted.end(), main.begin() + mainChain[i].offset, main.begin() + mainChain[i].offset + blockSize);
	}

	if (nbBlock * blockSize < main.size()) {
		sorted.insert(sorted.end(), main.begin() + nbBlock * blockSize, main.end());
	}

	main.swap(sorted);
}


void	PmergeMe::sort(std::deque<int>& main, size_t blockSize) {
	if (main.size() < 2 * blockSize) return;
	std::deque<int>::iterator it;

	for (it = main.begin(); it + blockSize * 2 <= main.end(); it += 2 * blockSize) {
		if (*(it + blockSize -1) > *(it + 2 * blockSize -1)) {
			std::swap_ranges(it, it + blockSize, it + blockSize);
		}
	}

	sort(main, blockSize * 2);
	std::deque<Block> mainChain, pendChain;

	mainChain.push_back(Block(0,0)), mainChain.push_back(Block(0, 1 * blockSize));
	size_t	k;
	size_t	nbBlock = main.size() / blockSize;
	size_t	currentId = 1;

	for (k = 2; k + 1 < nbBlock; k += 2) {
		pendChain.push_back(Block(currentId, k * blockSize));
		mainChain.push_back(Block(currentId, (k + 1) * blockSize));
		currentId++;
	}
	
	if (nbBlock % 2 != 0)
		pendChain.push_back(Block(static_cast<size_t>(-1), (nbBlock - 1) * blockSize));

	std::deque<int>	sorted;

	size_t	currJ, lastJ;

	lastJ = 0;
	for (size_t t = 3; lastJ <= pendChain.size(); t++) {
		currJ = jacobsthal(t);
		size_t	end = std::min(currJ, pendChain.size());
		for (size_t i = end; i > lastJ; --i) {
			std::deque<Block>::iterator searchEnd = mainChain.end();
			Block toInsert = pendChain[i - 1];
			if (toInsert.id != static_cast<size_t>(-1)) {
				searchEnd = std::find_if(mainChain.begin(), mainChain.end(), MatchId(toInsert.id));
				if (searchEnd != mainChain.end())
					searchEnd += 1;
			}
			std::deque<Block>::iterator binaryInsert = std::lower_bound(mainChain.begin(), searchEnd, toInsert, CompDequeBlock(main, blockSize));
			mainChain.insert(binaryInsert, toInsert);
		}
		lastJ = currJ;
	}

	for (size_t i = 0; i < mainChain.size(); i++) {
		sorted.insert(sorted.end(), main.begin() + mainChain[i].offset, main.begin() + mainChain[i].offset + blockSize);
	}

	if (nbBlock * blockSize < main.size()) {
		sorted.insert(sorted.end(), main.begin() + nbBlock * blockSize, main.end());
	}

	main.swap(sorted);
}

std::ostream&	operator<<(std::ostream& out, const std::vector<int>& v) {
	std::vector<int>::const_iterator it = v.begin();

	out << "Value: ";
	for (; it != v.end(); it++) {
		out << *it << " ";
	}
	return out;
}

std::ostream&	operator<<(std::ostream& out, const std::vector<Block>& v) {
	std::vector<Block>::const_iterator it = v.begin();

	out << "Value: ";
	for (; it != v.end(); it++) {
		out << "id: " << it->id << ", " << it->offset << " ";
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
