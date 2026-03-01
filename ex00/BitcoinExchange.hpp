#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
	std::map<unsigned long, float> _data;

	bool _parseDate(const std::string &dateStr, unsigned long &date);
	bool _parseValue(const std::string &valueStr, float &value);
	BitcoinExchange(const BitcoinExchange &copy);
	BitcoinExchange &operator=(const BitcoinExchange &copy);

public:
	BitcoinExchange();
	~BitcoinExchange();

	bool loadDatabase(const std::string &filename);
	void processInput(const std::string &filename);
};

#endif
