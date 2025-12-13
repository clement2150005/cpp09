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
    bool getNextInput(std::ifstream &input, std::string &date, double &value);
    void checkInput(const std::string &date, const std::string &valueStr, double value);
        
    std::map<std::string, double> _db;
};
