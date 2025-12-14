#pragma once

#include <string>

class RPN
{
public:
	static int rpn(const std::string &expression);

private:
	RPN();
	RPN(const RPN &);
	RPN &operator=(const RPN &);
	~RPN();

	static bool isOperator(char c);
	static bool add_overflow(long long a, long long b, long long &res);
	static bool sub_overflow(long long a, long long b, long long &res);
	static bool mul_overflow(long long a, long long b, long long &res);
};
