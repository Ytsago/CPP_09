#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>

class BitcoinExchange {
	public:
		BitcoinExchange();										//Default constructor
		~BitcoinExchange();										//Destructor
		BitcoinExchange(const BitcoinExchange &other);				//Copy constructor
		BitcoinExchange &operator=(const BitcoinExchange &other);	//Copy operator

		void	loadDictionnary(const char* dicName);
		void	loadFile(std::ifstream& file);

		const std::map<std::string, float>&	getDico() const;
		class ParsingException {
				const char*	status;
			public:
				ParsingException(const char* errorLine);
				const char*	what() const throw();
		};
	private:
		std::map<std::string, float>	_dico;
};

std::ostream&	operator<<(std::ostream& out, const BitcoinExchange& el);
#endif
