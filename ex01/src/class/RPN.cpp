#include "RPN.hpp"
#include <limits>

RPN::RPN() {
}

RPN::RPN(const RPN &other) : _numbers(other._numbers) {
}

RPN	&RPN::operator=(const RPN &other) {
	if (this != &other)
		_numbers = other._numbers;
	return (*this);
}

RPN::~RPN() {
}

std::stack<int>	RPN::getNumbers() const {return _numbers;}

bool	RPN::processSign(char sign) {
	long x, y;

	if (_numbers.size() < 2)
		return 1;
	y = static_cast<int>(_numbers.top());
	_numbers.pop();
	x = static_cast<int>(_numbers.top());
	_numbers.pop();
	long value;
	switch (sign) {
		case '+':
			value = x + y;
			break;
		case '-':
			value = x - y;
			break;
		case '*':
			value = x * y;
			break;
		case '/':
			if (y == 0) {
				std::cout << "Trying to divide by 0\n";
				return 1;
			}
			value = x / y;
			break;
		default:
			return 1;
	}

	if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min()) {
		std::cout << "Overflow\n";
		return 1;
	}
	_numbers.push(static_cast<int>(value));
	return 0;
}

std::ostream&	operator<<(std::ostream& out, const RPN& el) {
	std::stack<int>	numbers = el.getNumbers();

	out << "Value: ";
	while (!numbers.empty()) {
		out << numbers.top();
		numbers.pop();
		if (!numbers.empty())
			out << ", ";
	}
	return out;
}

bool	RPN::rpn(const char* arg) {
	for (size_t i = 0; arg[i] != '\0'; i++) {
		if (std::isdigit(arg[i])) {
			_numbers.push(arg[i] - '0');
		}
		else if (std::isspace(arg[i])) {
			continue;
		}
		else if (arg[i] == '-' || arg[i] == '+' || arg[i] == '*' || arg[i] == '/') {
			if (processSign(arg[i])) {
				std::cout << "Error\nCan't do the operation" << std::endl;
				return 1;
			}
		}
		else {
			std::cout << "Error\nUnknow character" << std::endl;
			return 1;
		}
	}
	if (_numbers.size() > 1) {
		std::cout << "Error\nNot enough operation\n" << *this << std::endl;
		return 1;
	}
	std::cout << *this << std::endl;
	return 0;
}
