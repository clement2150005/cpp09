#include "RPN.hpp"
#include <stack>
#include <stdexcept>
#include <cctype>
#include <iostream>

RPN::RPN() {}
RPN::RPN(const RPN &) {}
RPN &RPN::operator=(const RPN &) { return *this; }
RPN::~RPN() {}

bool RPN::isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::rpn(const std::string &expression)
{
	std::stack<int> stack;

	for (size_t i = 0; i < expression.size(); i++)
	{
		char c = expression[i];

		if (c == ' ')
			continue;

		if (std::isdigit(c))
		{
			stack.push(c - '0');
		}
		else if (isOperator(c))
		{
			if (stack.size() < 2)
			{
				std::cerr << "Error" << std::endl;
				return 1;
			}

			int b = stack.top();
            stack.pop();
			int a = stack.top();
            stack.pop();
			int res;

			if (c == '+') res = a + b;
			else if (c == '-') res = a - b;
			else if (c == '*') res = a * b;
			else
			{
				if (b == 0)
				{
					std::cerr << "Error" << std::endl;
					return 1;
				}
				res = a / b;
			}
			stack.push(res);
		}
		else
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}
	}

	if (stack.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

    std::cout << stack.top() << std::endl;
	return 0;
}
