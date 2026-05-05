#include "PmergeMe.hpp"
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>

std::ostream&	out = std::cout;

void	printLogs(const char start[], const char end[], std::vector<int>& vector, std::deque<int>& deque) {
	if (start)
		out << start << std::endl;
	out << "Vector " << vector << std::endl;
	out << "Deque " << deque << std::endl;
	if (end)
		out << end << std::endl;
}

bool	parseInput(char* const av[], std::vector<int>& vector, std::deque<int>& deque) {
	for (int i = 1; av[i]; i++) {
		std::stringstream iss(av[i]);
		long val;
		
		while (iss >> val) {
			if (val < 0 || val > std::numeric_limits<int>::max()) {
				std::cout << "Error.\nValue must be in range [0-INTMAX]" << std::endl;
				return 1;
			}
			vector.push_back(static_cast<int>(val));
			deque.push_back(static_cast<int>(val));
		}

		if (!iss.eof()) {
			std::cout << "Error.\nFailed to read number" << std::endl;
			return 1;
		}
	}
	return 0;
}

int main(int ac, char* const av[]) {
	std::vector<int>	vector;
	std::deque<int>		deque;
	if (ac < 2) {
		out << "Error.\nUsage: ./PmergeMe ..." << std::endl;
		return 1;
	}

	if (parseInput(av, vector, deque)) return 1;

	printLogs("Before -", " - end\n", vector, deque);
	PmergeMe::sort(vector, 1);
	// sort(deque);
	printLogs("After -", " - end\n", vector, deque);
	return 0;
}
