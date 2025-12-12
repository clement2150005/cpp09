#include "BitcoinExchange.hpp"
#include <stdexcept>

BitcoinExchange::BitcoinExchange(char *arg)
{
    std::ifstream dataBase("data.csv");
    if (!dataBase.is_open())
        throw std::runtime_error("Error: could not open data.csv");

    std::ifstream input(arg);
    if (!input.is_open())
    {
        std::string msg = std::string("Error: could not open ") + arg;
        throw std::runtime_error(msg);
    }

    parseDataBase(dataBase);
    processInput(input);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    //WIP
    (void)other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    //WIP
    (void)other;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
    //WIP
}

void BitcoinExchange::parseDataBase(std::ifstream &dataBase)
{
    //WIP
    (void)dataBase;
}

void BitcoinExchange::processInput(std::ifstream &input)
{
    //WIP
    (void)input;
}
