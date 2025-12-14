#include "RPN.hpp"
#include <stack>
#include <stdexcept>
#include <cctype>
#include <iostream>
#include <string>
#include <climits>

RPN::RPN() {}
RPN::RPN(const RPN &) {}
RPN &RPN::operator=(const RPN &) { return *this; }
RPN::~RPN() {}

bool RPN::isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

bool RPN::add_overflow(long long a, long long b, long long &res) {
	if ((b > 0 && a > LLONG_MAX - b) || (b < 0 && a < LLONG_MIN - b))
		return true;
	res = a + b;
	return false;
}

bool RPN::sub_overflow(long long a, long long b, long long &res) {
	if ((b > 0 && a < LLONG_MIN + b) || (b < 0 && a > LLONG_MAX + b))
		return true;
	res = a - b;
	return false;
}

bool RPN::mul_overflow(long long a, long long b, long long &res) {
	if (a > 0) {
		if (b > 0 && a > LLONG_MAX / b) return true;
		if (b < 0 && b < LLONG_MIN / a) return true;
	} else {
		if (b > 0 && a < LLONG_MIN / b) return true;
		if (b < 0 && a != 0 && b < LLONG_MAX / a) return true;
	}
	res = a * b;
	return false;
}

int RPN::rpn(const std::string &expression)
{
	std::stack<long long> stack;

	for (size_t i = 0; i < expression.size(); i++)
	{
		char c = expression[i];
		if (c == ' ') continue;

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

			long long b = stack.top(); stack.pop();
			long long a = stack.top(); stack.pop();
			long long res;

			bool overflow = false;
			if (c == '+') overflow = add_overflow(a, b, res);
			else if (c == '-') overflow = sub_overflow(a, b, res);
			else if (c == '*') overflow = mul_overflow(a, b, res);
			else
			{
				if (b == 0) { std::cerr << "Error" << std::endl; return 1; }
				res = a / b;
			}

			if (overflow) { std::cerr << "Error" << std::endl; return 1; }

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
