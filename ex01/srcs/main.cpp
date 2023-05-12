/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:29:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/12 12:40:04 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int	main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "usage: " << argv[0] << " [inverted Polish mathematical expression]" << std::endl;
		return 1;
	}
	for (int i = 1; i < argc; i++) {
		std::string rpnExpression = argv[i];
		try {
			RPN::calculateRpn(rpnExpression);
		} catch (std::exception& e) {
			std::cout <<  "[Error]: " << e.what() << std::endl;
		}
		if (i < argc - 1) {
			std::cout << std::endl;
		}
	}
	return 0;
}
