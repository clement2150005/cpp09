#include "BitcoinExchange.hpp"
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <cctype>

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

    std::string header;
    std::getline(input, header);
    (void)header;
    processInput(input);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _db(other._db) {}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {if (this != &other) {_db = other._db;} return *this;}
BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::parseDataBase(std::ifstream &dataBase)
{
	std::string line;
	std::getline(dataBase, line);

	while (std::getline(dataBase, line))
	{
		size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;

		_db[line.substr(0, comma)] = std::strtod(line.substr(comma + 1).c_str(), NULL);
	}
}

void BitcoinExchange::processInput(std::ifstream &input)
{
	std::string date;
	double value;

    while (true)
    {
        try
        {
            if (!getNextInput(input, date, value))
                break;
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            continue;
        }

        std::map<std::string, double>::iterator it = _db.lower_bound(date);

        if (it == _db.end() || it->first != date)
        {
            if (it == _db.begin())
            {
                std::cout << "Error: no matching or earlier date => " << date << std::endl;
                continue;
            }
            --it;
        }

        std::cout << date << " => " << value << " = " << value * it->second << std::endl;
    }
}

bool BitcoinExchange::getNextInput(std::ifstream &input, std::string &date, double &value)
{
	std::string line;

	if (!std::getline(input, line))
    return false;
    
	size_t sep = line.find(" | ");
	if (sep == std::string::npos)
        throw std::runtime_error("Error: bad input => " + line);

	date = line.substr(0, sep);
    std::string valueStr = line.substr(sep + 3);
	value = std::strtod(valueStr.c_str(), NULL);

    checkDate(date);
	checkValue(date, valueStr, value);

	return true;
}

void BitcoinExchange::checkDate(const std::string &date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		throw std::runtime_error("Error: bad input => " + date);

	for (size_t i = 0; i < date.size(); i++)
	{
		if (i != 4 && i != 7 && !std::isdigit(date[i]))
			throw std::runtime_error("Error: bad input => " + date);
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		throw std::runtime_error("Error: bad input => " + date);

	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (leap)
		daysInMonth[1] = 29;

	if (day < 1 || day > daysInMonth[month - 1])
		throw std::runtime_error("Error: bad input => " + date);
}

void BitcoinExchange::checkValue(const std::string &date, const std::string &valueStr, double value)
{
	char *end;
	std::strtod(valueStr.c_str(), &end);
	if (*end)
		throw std::runtime_error("Error: bad input => " + date);

	if (value < 0)
		throw std::runtime_error("Error: not a positive number.");

	if (value > 1000)
		throw std::runtime_error("Error: too large a number.");
}