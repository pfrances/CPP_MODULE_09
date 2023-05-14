/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:29:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/14 12:35:50 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>

int	main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "usage: " << argv[0] << " [input file]" << std::endl;
		return 1;
	}
	std::string dataFilename = "data.csv";
	try {
		BitcoinExchange btc(dataFilename);
		for (int i = 1; i < argc; i++) {
			btc.convertFile(argv[i]);
			if (i < argc - 1) {
				std::cout << std::endl;
			}
		}
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
