#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <fstream>
#include <sstream>


enum	e_month {
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,
	THIRTY,
	THIRTY_ONE,
};

const int	THIRTY_MONTH[] = {APRIL, JUNE, SEPTEMBER, NOVEMBER};
const std::map<std::string, float>&	BitcoinExchange::getDico() const {return _dico;}

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _dico(other._dico) {
}

int	whatMonth(const int& month) {
	for (size_t i = 0; i < sizeof(THIRTY_MONTH) / sizeof(int); i++) {
		if (month == THIRTY_MONTH[i])
			return THIRTY;
	}
	if (month == FEBRUARY)
		return FEBRUARY;
	return THIRTY_ONE;
}

void	checkValideDate(const std::string& date) {
	int		year = -1, month = -1, day = -1;
	char	sep[2];
	bool	isBissextile = false;
	std::stringstream	iss(date);

	iss >> year >> sep[0] >> month >> sep[1] >> day;
	if (sep[0] != sep[1] || sep[0] != '-')
		throw BitcoinExchange::ParsingException("Wrong date format");

	if (year == -1 || month == -1 || day == -1 || !iss.eof())
		throw BitcoinExchange::ParsingException("Wrong date value");

	if (year < 2009 || (year == 2009 && month == JANUARY && day < 2) || year > 9999 || day > 31 || month > 12 || day < 1 || month < 1)
		throw BitcoinExchange::ParsingException("Date does not exist");

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		isBissextile = true;

	int	months = whatMonth(month);
	if ((months == THIRTY && day > 30) || (months == FEBRUARY && day > (isBissextile ? 29 : 28))) 
		throw BitcoinExchange::ParsingException("Wrong date day value");
}

void	BitcoinExchange::loadDictionnary(const char* dicName) {
	std::ifstream		file(dicName);
	std::string	date, line, value;

	if (!file.is_open())
		throw BitcoinExchange::ParsingException("Failed to open dictionnary.");
	file >> line;
	while (!file.eof()) {
		file >> line;
		size_t	pos = line.find_first_of(',');
		if (pos == line.npos || pos != line.find_last_of(','))
			throw BitcoinExchange::ParsingException("CSV file is malformated.");
		date = line.substr(0, pos);
		value = line.substr(pos + 1, line.size() - pos);
		char*	endptr;
		float realValue = strtof(value.c_str(), &endptr);
		if (*endptr)
			throw BitcoinExchange::ParsingException("Incorrect value");
		checkValideDate(date);
		_dico[date] = realValue;
	}
}

void	BitcoinExchange::loadFile(std::ifstream& file) {
	std::string	date, sep;
	float		value;

	while(!file.eof()) {
		size_t pos;

		date.clear(), sep.clear(), value = 0;
		file >> date >> sep >> value;
		if (file.fail()) {
			std::cout << "Error\nSomething went wrong" << std::endl;
			return ;
		}
		if ((pos = date.find_last_of(',')) != date.npos)
			date.erase(pos);
		if (date.empty() || sep.empty() || sep != "|" || value < 0 || value > 1000) {
			std::cout << "Error\nWrong line format" << std::endl;
			continue;
		}
		try {checkValideDate(date);} catch (BitcoinExchange::ParsingException &e) {
			std::cout << date << " - ";
			std::cout << e.what() << std::endl;
			continue;
		}
		std::map<std::string, float>::iterator it = _dico.lower_bound(date);

		if (it != _dico.end()) {
			std::cout << date;
			std::cout << " - Conversion: " << value * it->second << std::endl;
		}
		else {
			std::cout << date;
			std::cout << " - Conversion: " << value * _dico.rbegin()->second << std::endl;
		}
	}
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other)
		_dico = other._dico;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {
}

BitcoinExchange::ParsingException::ParsingException(const char* errorLine) : status(errorLine) {}

const char*	BitcoinExchange::ParsingException::what() const throw() {
	return status;
}

std::ostream&	operator<<(std::ostream& out, const BitcoinExchange& el) {
	std::map<std::string, float>::const_iterator cit = el.getDico().begin();

	for (; cit != el.getDico().end(); cit++) {
		out << "Date: " << cit->first << ", Value: " << cit->second << "\n";
	}
	return out;
}
