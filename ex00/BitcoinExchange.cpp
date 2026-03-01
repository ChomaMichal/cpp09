#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::loadDatabase(const std::string &filename) {
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    return false;
  }

  std::string line;

  if (!std::getline(file, line) || line != "date,exchange_rate") {
    file.close();
    return false;
  }

  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    size_t commaPos = line.find(',');
    if (commaPos == std::string::npos)
      continue;

    std::string dateStr = line.substr(0, commaPos);
    std::string rateStr = line.substr(commaPos + 1);

    unsigned long date;
    if (!_parseDate(dateStr, date))
      continue;

    char *end;
    float rate = std::strtof(rateStr.c_str(), &end);
    _data[date] = rate;
  }

  file.close();
  return true;
}

bool BitcoinExchange::_parseDate(const std::string &dateStr,
                                 unsigned long &date) {
  if (dateStr.length() != 10)
    return false;
  if (dateStr[4] != '-' || dateStr[7] != '-')
    return false;

  char *end;
  unsigned long year = std::strtoul(dateStr.substr(0, 4).c_str(), &end, 10);
  unsigned long month = std::strtoul(dateStr.substr(5, 2).c_str(), &end, 10);
  unsigned long day = std::strtoul(dateStr.substr(8, 2).c_str(), &end, 10);

  if (month < 1 || month > 12 || day < 1 || day > 31)
    return false;

  date = year * 10000 + month * 100 + day;
  return true;
}

bool BitcoinExchange::_parseValue(const std::string &valueStr, float &value) {
  if (valueStr.empty())
    return false;

  char *end;
  value = std::strtof(valueStr.c_str(), &end);

  if (*end != '\0')
    return false;
  if (value < 0)
    return false;
  if (value > 1000)
    return false;

  return true;
}

void BitcoinExchange::processInput(const std::string &filename) {
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    std::cerr << "Error: could not open file." << std::endl;
    return;
  }

  std::string line;

  if (!std::getline(file, line) || line != "date | value") {
    std::cerr << "Error: bad input => " << line << std::endl;
    file.close();
    return;
  }

  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    size_t pipePos = line.find('|');
    if (pipePos == std::string::npos) {
      std::cerr << "Error: bad input => " << line << std::endl;
      continue;
    }

    std::string dateStr = line.substr(0, pipePos);
    std::string valueStr = line.substr(pipePos + 1);

    size_t endDate = dateStr.find_last_not_of(" \t");
    if (endDate != std::string::npos) {
      dateStr = dateStr.substr(0, endDate + 1);
    }
    size_t startValue = valueStr.find_first_not_of(" \t");
    if (startValue != std::string::npos) {
      valueStr = valueStr.substr(startValue);
    }
    size_t endValue = valueStr.find_last_not_of(" \t");
    if (endValue != std::string::npos) {
      valueStr = valueStr.substr(0, endValue + 1);
    }

    unsigned long date;
    if (!_parseDate(dateStr, date)) {
      std::cerr << "Error: bad input => " << line << std::endl;
      continue;
    }

    float value;
    if (!_parseValue(valueStr, value)) {
      if (valueStr.empty() || (valueStr[0] == '-' && valueStr.length() > 1)) {
        std::cerr << "Error: not a positive number." << std::endl;
      } else {
        char *end;
        std::strtof(valueStr.c_str(), &end);
        if (*end != '\0') {
          std::cerr << "Error: bad input => " << line << std::endl;
        } else {
          std::cerr << "Error: too large a number." << std::endl;
        }
      }
      continue;
    }

    std::map<unsigned long, float>::iterator it = _data.lower_bound(date);
    if (it == _data.begin()) {
      std::cerr << "Error: bad input => " << dateStr << std::endl;
      continue;
    }

    if (it->first != date) {
      --it;
    }

    unsigned long resultDate = it->first;
    float resultValue = value * it->second;

    unsigned long year = resultDate / 10000;
    unsigned long month = (resultDate / 100) % 100;
    unsigned long day = resultDate % 100;

    std::cout << year << "-";
    if (month < 10)
      std::cout << "0";
    std::cout << month << "-";
    if (day < 10)
      std::cout << "0";
    std::cout << day << " => " << value << " = " << resultValue << std::endl;
  }

  file.close();
}
