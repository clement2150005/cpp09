#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    if (argc != 2)
        return (std::cerr << "Error: could not open file." << std::endl, 1);

    try {BitcoinExchange btc(argv[1]);}
    catch(const std::exception& e) {std::cerr << e.what() << '\n';}

    return 0;
}