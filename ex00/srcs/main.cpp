/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:29:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/10 11:27:24 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>

int	main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "usage: ./btc [input file]" << std::endl;
		return 1;
	}
	std::string data_filename = "data.csv";
	BitcoinExchange btc(data_filename);
	for (int i = 1; i < argc; i++) {
		btc.ConvertFile(argv[i]);
		std::cout << std::endl;
	}
	return 0;
}
