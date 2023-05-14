/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:29:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/14 11:22:49 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

BitcoinExchange::BitcoinExchange( void ) : data_() {
	//std::cout << "[BitcoinExchange] default constructor called." << std::endl;
}

BitcoinExchange::BitcoinExchange(std::string& dataFilename) {
	std::ifstream data(dataFilename.c_str());
	if (!data.is_open()) {
		throw BitcoinExchange::NoDatabaseException();
	}

	std::string	line;
	int			date;
	double		price;
	size_t		lineNum = 2;
	bool		error = false;

	std::getline(data, line);

	while (std::getline(data, line)) {
		try {
			parseLine(line, ',', date, price);
			data_[date] = price;
			latestDate_ = date;
			if (data_.size() == 1) {
				earliestDate_ = date;
			}
		} catch(const std::exception& e) {
			std::cout << "⚠ [" << dataFilename << ":l" << lineNum << "] Error: '" << line << "': " << e.what() << '\n';
			error = true;
		}
		lineNum++;
	}
	data.close();
	if (error) {
		throw BitcoinExchange::InvalidDataException();
	}
	//std::cout << "[BitcoinExchange] parameter constructor called." << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : data_(other.data_) {
	//std::cout << "[BitcoinExchange] copy constructor called." << std::endl;
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		data_ = other.data_;
	}
	//std::cout << "[BitcoinExchange] asignment called." << std::endl;
	return *this;
}

BitcoinExchange::~BitcoinExchange( void ) {
	//std::cout << "[BitcoinExchange] destructor called." << std::endl;
}

bool BitcoinExchange::checkDate(int year, int month, int day) const {
	if (year < 0) {
		return false;
	}
	if (month < 1 || month > 12) {
		return false;
	}
	if (day < 1 || day > 31) {
		return false;
	}
	if (month == 2 && day > 28) {
		if (day == 29 && year % 4 == 0) {
			if (year % 100 == 0 && year % 400 != 0) {
				return false;
			}
			return true;
		}
		return false;
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
		return false;
	}
	return true;
}

int BitcoinExchange::stringDateToInt(std::string& date) const {
	if (date.length() < 10) {
		throw BitcoinExchange::InvalidDateFormatException();
	}
	for (size_t i = 0; i < date.length(); i++) {
		if ((i == 4 || i == 7) && date.at(i) == '-') {
			continue;
		} else if (i >= 10) {
			if (date.at(i) == ' ') {
				continue;
			} else {
				throw BitcoinExchange::InvalidDateFormatException();
			}
		} else if (date.at(i) < '0' || date.at(i) > '9') {
			throw BitcoinExchange::InvalidDateFormatException();
		}
	}
	char *endPtr;
	int year = std::strtol(date.substr(0, 4).c_str(), &endPtr, 10);
	if (*endPtr != '\0') {
		throw BitcoinExchange::InvalidDateFormatException();
	}
	int month = std::strtol(date.substr(5, 2).c_str(), &endPtr, 10);
	if (*endPtr != '\0') {
		throw BitcoinExchange::InvalidDateFormatException();
	}
	int day = std::strtol(date.substr(8, 2).c_str(), &endPtr, 10);
	if (*endPtr != '\0') {
		throw BitcoinExchange::InvalidDateFormatException();
	}
	if (checkDate(year, month, day) == false) {
		throw BitcoinExchange::InvalidDateFormatException();
	}
	return year << 16 | month << 8 | day;
}

std::string BitcoinExchange::intDateToString(int date) const {
	int year = date >> 16;
	int month = (date >> 8) & 0xff;
	int day = date & 0xff;
	std::ostringstream ss;
	ss << year << "-";
	if (month < 10) {
		ss << "0";
	}
	ss << month << "-";
	if (day < 10) {
		ss << "0";
	}
	ss << day;
	std::string dateStr = ss.str();
	return dateStr;
}

void BitcoinExchange::parseLine(std::string& line, char delimiter, int& date, double& value) const {
	if (line.length() == 0) {
		throw BitcoinExchange::EmptyLineException();
	}
	std::string dateStr;
	std::string valueStr;
	size_t pos = line.find(delimiter);
	if (pos == std::string::npos) {
		throw BitcoinExchange::InvalidLineFormatException();
	}
	dateStr = line.substr(0, pos);
	valueStr = line.substr(pos + 1, line.length());
	date = stringDateToInt(dateStr);
	char *endPtr;
	value = std::strtod(valueStr.c_str(), &endPtr);
	if (*endPtr != '\0') {
		throw BitcoinExchange::InvalidValueFormatException();
	} else if (value < 0) {
		throw BitcoinExchange::NotPositiveNumberException();
	} else if (value > 1000 && delimiter == '|') {
		throw BitcoinExchange::TooLargeNumberException();
	}
}

void BitcoinExchange::printConvertion(int date, double amount) const {
	std::map<int, double>::const_iterator it_data_ = data_.lower_bound(date);
	if (it_data_ != data_.begin() && it_data_->first > date) {
		it_data_--;
	}
	std::cout << intDateToString(date) << " ==> " << amount << " = " << it_data_->second * amount;
	if (date < this->earliestDate_) {
		std::cout << " ⇦ Warning: earliest date is " << intDateToString(this->earliestDate_);
	} else if (date > this->latestDate_) {
		std::cout << " ⇦ Warning: latest date is " << intDateToString(this->latestDate_);
	} else if (date != it_data_->first) {
		std::cout << " ⇦ data from " << intDateToString(it_data_->first);
	}
	std::cout << std::endl;
}

void BitcoinExchange::convertFile(std::string filename) const {
	std::ifstream input(filename.c_str());
	if (!input.is_open()) {
		std::cout << "⚠ Failed to open " << filename << std::endl;
		return ;
	}
	std::cout << "	[Converting " << filename << "] start." << std::endl;

	std::string line;
	int		date;
	double	amount;
	int		lineNum = 2;
	std::getline(input, line);
	while (std::getline(input, line)) {
		try {
			parseLine(line, '|', date, amount);
			printConvertion(date, amount);
		} catch(const std::exception& e) {
			std::cout << "⚠ [" << filename << ":l" << lineNum << "] Error: '" << line << "': " << e.what() << '\n';
		}
		lineNum++;

	}
	input.close();
	std::cout << "	[Converting " << filename << "] done." << std::endl;
}

const char* BitcoinExchange::EmptyLineException::what() const throw() {
	return "Empty line";
}

const char* BitcoinExchange::InvalidLineFormatException::what() const throw() {
	return "Invalid line format";
}

const char* BitcoinExchange::InvalidDateFormatException::what() const throw() {
	return "Invalid date format";
}

const char* BitcoinExchange::InvalidValueFormatException::what() const throw() {
	return "Invalid value format";
}

const char* BitcoinExchange::NotPositiveNumberException::what() const throw() {
	return "Not positive number";
}

const char* BitcoinExchange::TooLargeNumberException::what() const throw() {
	return "Too large number";
}

const char* BitcoinExchange::NoDatabaseException::what() const throw() {
	return "⚠ Failed to open data.csv";
}

const char* BitcoinExchange::InvalidDataException::what() const throw() {
	return "	⚠ ⚠ ⚠ ⚠ 	data.csv is invalid	⚠ ⚠ ⚠ ⚠";
}
