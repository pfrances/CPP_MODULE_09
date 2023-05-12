/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:29:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/12 15:58:07 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

int	main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "usage: " << argv[0] << " [numbers list to sort]" << std::endl;
		return 1;
	}
	if (argc > 100001) {
		std::cout << "error: too many numbers to sort. [Max: 1 000 000]" << std::endl;
		return 1;
	}
	PmergeMe::mergeSort(&argv[1], argc - 1);
	return 0;
}
