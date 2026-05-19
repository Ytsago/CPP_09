#include "PmergeMe.hpp"
#include <ctime>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include <deque>

std::ostream&	out = std::cout;

enum	e_time {
	HOUR,
	MINUTE,
	SECOND,
	MILI,
	MICRO,
	NANO
};

void	printLogs(const char start[], const char end[], std::vector<int>& vector) {
	if (start)
		out << start << std::endl;
	out << "Vector " << vector << std::endl;
	if (end)
		out << end << std::endl;
}

void	printLogs(const char start[], const char end[], std::deque<int>& deque) {
	if (start)
		out << start << std::endl;
	out << "Deque " << deque << std::endl;
	if (end)
		out << end << std::endl;
}

bool	parseInput(char* const av[], std::deque<int>& deque) {
	for (int i = 1; av[i]; i++) {
		std::stringstream iss(av[i]);
		long val;
		
		while (iss >> val) {
			if (val < 0 || val > std::numeric_limits<int>::max()) {
				std::cerr << "Error.\nValue must be in range [0-INTMAX]" << std::endl;
				return 1;
			}
			deque.push_back(static_cast<int>(val));
		}

		if (!iss.eof()) {
			std::cerr << "Error.\nFailed to read number" << std::endl;
			return 1;
		}
	}
	return 0;
}

bool	parseInput(char* const av[], std::vector<int>& vector) {
	for (int i = 1; av[i]; i++) {
		std::stringstream iss(av[i]);
		long val;
		
		while (iss >> val) {
			if (val < 0 || val > std::numeric_limits<int>::max()) {
				std::cerr << "Error.\nValue must be in range [0-INTMAX]" << std::endl;
				return 1;
			}
			vector.push_back(static_cast<int>(val));
		}

		if (!iss.eof()) {
			std::cerr << "Error.\nFailed to read number" << std::endl;
			return 1;
		}
	}
	return 0;
}

void	printTime(const std::clock_t& start, const std::clock_t& end) {
	double timeDif = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::string	unitStr[] = {"h", "mn", "sec", "ms", "µs", "ns"};
	int	unit = SECOND;

	while (timeDif < 1 || timeDif > 1000) {
		if (timeDif < 1 && unit < NANO) {
			timeDif *= 1000;
			++unit;
		}
		if (timeDif > 1000 && unit > HOUR) {
			timeDif /= 1000;
			--unit;
		}
	}

	std::cout << timeDif << " " << unitStr[unit] << std::endl;
}

int main(int ac, char* const av[]) {
	std::vector<int>	vector;
	std::deque<int>		deque;
	std::clock_t		start, end;

	if (ac < 2) {
		std::cerr << "Error.\nUsage: ./PmergeMe ..." << std::endl;
		return 1;
	}

	start = std::clock();
	if (parseInput(av, vector)) return 1;
	printLogs("Before -", " - end\n", vector);
	PmergeMe::sort(vector, 1);
	end = std::clock();
	printLogs("After -", " - end\n", vector);
	std::cout << "Vector: "; printTime(start, end);

	std::cout << std::endl << std::endl;
	start = std::clock();
	if (parseInput(av, deque)) return 1;
	printLogs("Before -", " - end\n", deque);
	PmergeMe::sort(deque, 1);
	end = std::clock();
	printLogs("After -", " - end\n", deque);
	std::cout << "Deque: "; printTime(start, end);

	return 0;
}
