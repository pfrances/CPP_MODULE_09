/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:29:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/10 12:16:42 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

BitcoinExchange::BitcoinExchange( void ) : data_() {
	std::cout << "[BitcoinExchange] default constructor called." << std::endl;
}

BitcoinExchange::BitcoinExchange(std::string& data_filename) {
	std::ifstream data(data_filename.c_str());
	if (!data.is_open()) {
		std::cerr << "⚠ Failed to open " << data_filename <<std::endl;
		throw std::exception();
	}

	std::string	line;
	int			date;
	double		price;

	std::getline(data, line);
	while (std::getline(data, line)) {
		try {
			ParseLine(line, ',', date, price);
			data_[date] = price;
			latest_date_ = date;
			if (data_.size() == 1) {
				earliest_date_ = date;
			}
		} catch(const std::exception& e) {
			std::cerr << "⚠ [" << data_filename << "] Error: '" << line << "': " << e.what() << '\n';
		}
	}
	data.close();
	std::cout << "[BitcoinExchange] parameter constructor called." << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : data_(other.data_) {
	std::cout << "[BitcoinExchange] copy constructor called." << std::endl;
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		data_ = other.data_;
	}
	std::cout << "[BitcoinExchange] asignment called." << std::endl;
	return *this;
}

BitcoinExchange::~BitcoinExchange( void ) {
	std::cout << "[BitcoinExchange] destructor called." << std::endl;
}

int BitcoinExchange::StringDateToInt(std::string& date) const {
	if (date.length() < 10) {
		throw BitcoinExchange::InvalidDateFormatException();
	}
	for (size_t i = 0; i < date.length(); i++) {
		if ((i == 4 || i == 7) && date.at(i) == '-') {
			continue;
		} else if (i >= 10 && date.at(i) == ' ') {
			continue;
		} else if (date.at(i) < '0' || date.at(i) > '9') {
			throw BitcoinExchange::InvalidDateFormatException();
		}
	}
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	return year << 16 | month << 8 | day;
}

std::string BitcoinExchange::IntDateToString(int date) const {
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
	std::string date_str = ss.str();
	return date_str;
}

void BitcoinExchange::ParseLine(std::string& line, char delimiter, int& date, double& value) const {
	std::string date_str;
	std::string value_str;
	size_t pos = line.find(delimiter);
	if (pos == std::string::npos) {
		throw BitcoinExchange::InvalidLineFormatException();
	}
	date_str = line.substr(0, pos);
	value_str = line.substr(pos + 1, line.length());
	date = StringDateToInt(date_str);
	value = std::atof(value_str.c_str());
	if (value < 0) {
		throw BitcoinExchange::NotPositiveNumberException();
	} else if (value > 1000 && delimiter == '|') {
		throw BitcoinExchange::TooLargeNumberException();
	}
}

double BitcoinExchange::doConvertion(int date, double amount) const {
	if (date <= earliest_date_) {
		return data_.at(earliest_date_) * amount;
	}
	else if (date >= latest_date_) {
		return data_.at(latest_date_) * amount;
	}
	while (data_.find(date) == data_.end()) {
		date--;
	}
	return data_.at(date) * amount;
}

void BitcoinExchange::ConvertFile(std::string filename) const {
	std::ifstream input(filename.c_str());
	if (!input.is_open()) {
		std::cerr << "⚠ Failed to open " << filename << std::endl;
		return ;
	}
	std::cout << "	[Converting " << filename << "] start." << std::endl;

	std::string line;
	int		date;
	double	amount;
	std::getline(input, line);
	while (std::getline(input, line)) {
		try {
			ParseLine(line, '|', date, amount);
			std::cout << IntDateToString(date) << " ==> " << amount << " = " << doConvertion(date, amount);
			if (date < this->earliest_date_) {
				std::cout << " ⇦ Warning: earliest date is " << IntDateToString(this->earliest_date_);
			} else if (date > this->latest_date_) {
				std::cout << " ⇦ Warning: latest date is " << IntDateToString(this->latest_date_);
			}
			std::cout << std::endl;
		} catch(const std::exception& e) {
			std::cerr << "⚠ [" << filename << "] Error: '" << line << "': " << e.what() << '\n';
		}
	}
	input.close();
	std::cout << "	[Converting " << filename << "] done." << std::endl;
}


const char* BitcoinExchange::InvalidLineFormatException::what() const throw() {
	return "Invalid line format";
}

const char* BitcoinExchange::InvalidDateFormatException::what() const throw() {
	return "Invalid date format";
}

const char* BitcoinExchange::NotPositiveNumberException::what() const throw() {
	return "Not positive number";
}

const char* BitcoinExchange::TooLargeNumberException::what() const throw() {
	return "Too large number";
}
