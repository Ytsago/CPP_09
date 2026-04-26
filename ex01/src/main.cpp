#include "RPN.hpp"

int main(int ac, char* const av[]) {
	RPN	converter;

	if (ac != 2) {
		std::cout << "Error\nUsage: ./RPN <\"operation\">" << std::endl;
		return 1;
	} else
		return converter.rpn(av[1]);
}
