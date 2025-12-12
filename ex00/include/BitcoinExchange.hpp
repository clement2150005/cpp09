#pragma once

#include <map>
#include <string>
#include <fstream>

class BitcoinExchange
{
    public:
        BitcoinExchange(char *arg);
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

    private:
        void parseDataBase(std::ifstream &dataBase);
        void processInput(std::ifstream &input);
        
        std::map<std::string, double> _db;
};
