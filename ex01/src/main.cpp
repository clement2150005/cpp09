#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
        return (std::cerr << "Usage: ./RPN <mathematical expression>" << std::endl, 1);
    RPN::rpn((std::string(argv[1])));
    return 0;
}