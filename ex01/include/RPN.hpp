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
};
