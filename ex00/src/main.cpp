#include "BitcoinExchange.hpp"
#include <fstream>

int main(int ac, char* av[]) {
	BitcoinExchange exc;
	if (ac == 2) {
		std::ifstream inFile(av[1]);
		if (!inFile.is_open()) {
			std::cout << "Error: File does not exist or can't be open" << std::endl;
			return 1;
		}
		try {
			exc.loadDictionnary("data.csv");	
		} catch (BitcoinExchange::ParsingException &e) {
			std::cout << e.what() << std::endl;
		}
		std::cout << exc << std::endl;
	}
	else {
		std::cout << "Usage: ./btc <filename>" << std::endl;
		return 1;
	}
	return 0;
}
