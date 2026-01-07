#include <fstream>
#include <string>
#include <iostream>
#include <map>

void	format_print(unsigned long date, float value, std::map<unsigned long, float> &data){
	unsigned long	year = date / 10000;
	unsigned long	month = (date / 100) % 100;
	unsigned long	day = date % 100;
	float			fin_value;
	std::map<unsigned long, float>::iterator it = data.lower_bound(date);
	if	(it == data.begin()){
		std::cerr << "Date before first trade" << std::endl;
		return;
	}
	it --;
	std::cout << date << "-" << month << "-" << year << " => " 
		<< value << " = " << value * it->second << std::endl;
}

int main(int argc, char** argv){
	if (argc != 2){
		std::cerr << "Invalid amount of arguments" << std::endl;
		return 1;
	}

	std::ifstream data_file("data.csv");
	if (!data_file.is_open()){
		std::cerr << "Database couldn't be opened" << std::endl;
		return 1;
	}
	
	std::map<unsigned long, float>	data;
	std::string						line;

	while (std::getline(data_file, line)){
		if (line == "date,exchange_rate"){
			continue;
		}
		char	*end;
		unsigned long	key = std::strtoul(line.substr(0, 4).c_str(), &end, 10) * 10000 + 
			std::strtoul(line.substr(6, 2).c_str(), &end, 10) * 100 +
			std::strtoul(line.substr(9, 2).c_str(), &end, 10);

		float	value = std::strtof(line.substr(line.find(','), line.length()).c_str(), &end);
		data[key] = value;
	}
	data_file.close();

	std::fstream	input_file(argv[1]);
	if (!data_file.is_open()){
		std::cerr << "Input file couldn't be opened" << std::endl;
		return 1;
	}
	std::getline(input_file, line);
	if (line != "date | value"){
		std::cerr << "Invalid input file format" << std::endl;
		return 1;
	}
	while (std::getline(input_file, line)){
		const char *str = line.c_str();
		char *next;
		unsigned long	date;
		unsigned long	tmp;
		date = std::strtoul(str, &next, 10) * 10000;
		if (*next!= '-'){
			std::cerr << "Invalid format\n";
			continue;
		}
		next ++;
		tmp = std::strtoul(next, &next, 10);
		if (*next!= '-' || tmp > 12){
			std::cerr << "Invalid format\n";
			continue;
		}
		date  += tmp * 100;
		next ++;
		tmp = std::strtoul(next, &next, 10);
		if (*next!= ' ' || tmp > 12){
			std::cerr << "Invalid format\n";
			continue;
		}
		date  += tmp;
		next ++;
		if (*next != ' '){
			std::cerr << "Invalid format\n";
			continue;

		}
		next ++;
		if (*next != '|'){
			std::cerr << "Invalid format\n";
			continue;

		}
		next ++;
		if (*next != ' '){
			std::cerr << "Invalid format\n";
			continue;

		}
		float	value = std::strtof(next, &next);
		if (*next != 0){
			std::cerr << "Invalid format\n";
			continue;
		}
		if (value < 0 || value > 1000){
			std::cerr << "Invalid value\n";
			continue;
		}
		format_print(date, value, data);
	}
	input_file.close();
}
