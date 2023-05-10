/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:56:36 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/10 11:01:40 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <algorithm>
# include <map>
# include <string>

class BitcoinExchange {
public:
	BitcoinExchange(void);
	BitcoinExchange(std::string& data_filename);
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange(void);

	double			doConvertion(int date, double amount) const;
	void			ConvertFile(std::string filename) const;

private:
	std::map<int, double>	data_;
	int						earliest_date_;
	int						latest_date_;

	int				StringDateToInt(std::string& date) const;
	std::string		IntDateToString(int date) const;
	void			ParseLine(std::string& line, char delimiter, int& date, double& value) const;

	class InvalidDateFormatException : public std::exception {
		virtual const char* what() const throw();
	};
	class NotPositiveNumberException : public std::exception {
		virtual const char* what() const throw();
	};
	class TooLargeNumberException : public std::exception {
		virtual const char* what() const throw();
	};
	class InvalidLineFormatException : public std::exception {
		virtual const char* what() const throw();
	};
};

#endif
