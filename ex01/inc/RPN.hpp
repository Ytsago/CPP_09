#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>

class RPN {
	public:
		RPN();										//Default constructor
		~RPN();										//Destructor
		RPN(const RPN &other);				//Copy constructor
		RPN &operator=(const RPN &other);	//Copy operator

		bool	rpn(const char* arg);
		std::stack<int>	getNumbers() const;

	private:
		bool	processSign(char sign);
		std::stack<int>	_numbers;

};

std::ostream&	operator<<(std::ostream& out, const RPN& el);
#endif
