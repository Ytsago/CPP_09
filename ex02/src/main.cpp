#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>

std::ostream&	out = std::cout;
std::vector<int>	vector;
std::deque<int>		deque;

std::ostream&	operator<<(std::ostream& cout, const std::vector<int>& c) {
	std::vector<int>::const_iterator it = c.begin();

	cout << "Value: ";
	for (; it != c.end(); it++) {
		cout << *it << " ";
	}
	return cout;
}

std::ostream&	operator<<(std::ostream& cout, const std::deque<int>& c) {
	std::deque<int>::const_iterator it = c.begin();

	cout << "Value: ";
	for (; it != c.end(); it++) {
		cout << *it << " ";
	}
	return cout;
}

void	printLogs(const char start[], const char end[]) {
	if (start)
		out << start << std::endl;
	out << "Vector " << vector << std::endl;
	out << "Deque " << deque << std::endl;
	if (end)
		out << end << std::endl;
}

bool	parseInput(char* const av[]) {
	for (int i = 1; av[i]; i++) {
		std::stringstream iss(av[i]);
		long val;
		
		while (iss >> val) {
			if (val < 0 || val > std::numeric_limits<int>::max()) {
				out << "Error.\nValue must be in range [0-INTMAX]" << std::endl;
				return 1;
			}
			vector.push_back(static_cast<int>(val));
			deque.push_back(static_cast<int>(val));
		}

		if (!iss.eof()) {
			out << "Error.\nFailed to read number" << std::endl;
			return 1;
		}
	}
	return 0;
}

template<typename T>
void	sort(T& c) {
	std::sort(c.begin(), c.end());
}

int main(int ac, char* const av[]) {
	if (ac < 2) {
		out << "Error.\nUsage: ./PmergeMe ..." << std::endl;
		return 1;
	}

	if (parseInput(av)) return 1;

	printLogs("Before -", " - end\n");
	sort(vector);
	sort(deque);
	printLogs("After -", " - end\n");
	return 0;
}
