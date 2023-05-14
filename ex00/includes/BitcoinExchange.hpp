/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:56:36 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/14 11:31:39 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange {
public:
	BitcoinExchange(void);
	BitcoinExchange(std::string& data_filename);
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	virtual ~BitcoinExchange(void);

	void			printConvertion(int date, double amount) const;
	void			convertFile(std::string filename) const;

private:
	std::map<int, double>	data_;
	int						earliestDate_;
	int						latestDate_;

	int				stringDateToInt(std::string& date) const;
	std::string		intDateToString(int date) const;
	bool			checkDate(int year, int month, int day) const;
	void			parseLine(std::string& line, char delimiter, int& date, double& value) const;

	class InvalidDateFormatException : public std::exception {
		virtual const char* what() const throw();
	};
	class InvalidValueFormatException : public std::exception {
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
	class NoDatabaseException : public std::exception {
		virtual const char* what() const throw();
	};
	class EmptyLineException : public std::exception {
		virtual const char* what() const throw();
	};
	class InvalidDataException : public std::exception {
		virtual const char* what() const throw();
	};
	class InvalidDataHeaderLine : public std::exception {
		virtual const char* what() const throw();
	};
	class InvalidInputFileHeaderLine : public std::exception {
		virtual const char* what() const throw();
	};
};

#endif
