/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:29:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/13 21:52:02 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <climits>
#include <cstdlib>
#include <string>
#include <sstream>
#include <time.h>
#include <sys/time.h>

std::vector<int>	PmergeMe::vec_;
std::list<int>		PmergeMe::lst_;

PmergeMe::PmergeMe( void ) {
	// std::cout << "[PmergeMe] default constructor called." << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& other) {
	(void)other;
	// std::cout << "[PmergeMe] copy constructor called." << std::endl;
}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other) {
	(void)other;
	// std::cout << "[PmergeMe] asignment called." << std::endl;
	return *this;
}

PmergeMe::~PmergeMe( void ) {
	// std::cout << "[PmergeMe] destructor called." << std::endl;
}

bool	PmergeMe::ConvertNbWithCheck(char *nbStr, int *nb) {
	char *endPtr;
	*nb = std::strtol(nbStr, &endPtr, 10);
	if (*endPtr != '\0') {
		return false;
	}
	return (*nb >= 0);
}

std::string	PmergeMe::getVector(void) {
	std::ostringstream VectorContent;
	std::vector<int>::iterator it = vec_.begin();
	std::vector<int>::iterator ite = vec_.end();
	while (it != ite) {
		VectorContent << *it;
		it++;
		if (it != ite)
			VectorContent << " ";
	}
	return VectorContent.str();
}

std::string	PmergeMe::getList(void) {
	std::ostringstream ListContent;
	std::list<int>::iterator it = lst_.begin();
	std::list<int>::iterator ite = lst_.end();
	while (it != ite) {
		ListContent << *it;
		it++;
		if (it != ite)
			ListContent << " ";
	}
	return ListContent.str();
}

std::string	PmergeMe::printDuration(useconds_t duration) {
	std::ostringstream duration_stream;
	if (duration < 1000) {
		duration_stream << duration << " us";
	} else if (duration < 1000000) {
		duration_stream << duration / 1000 << " ms";
	} else {
		duration_stream << duration / 1000000 << " s";
	}
	return duration_stream.str();
}

void	PmergeMe::mergeSort(char **nbArr, int arrSize) {

	vec_ = std::vector<int>(arrSize);
	lst_ = std::list<int>(arrSize);

	int i = 0;
	int nb;

	std::vector<int>::iterator itVec = vec_.begin();
	std::list<int>::iterator itLst = lst_.begin();
	while (nbArr[i]) {
		if (ConvertNbWithCheck(nbArr[i], &nb) == false) {
			std::cout << "Error: '" << nbArr[i] << "' is not a valid number." << std::endl;
			return ;
		}
		if (UNIQ && std::find(vec_.begin(), itVec, nb) != itVec) {
				std::cout << "Error: " << nb << " is a duplicate." << std::endl;
				return ;
		}
		*itVec = nb;
		*itLst = nb;
		itVec++;
		itLst++;
		i++;
	}

	std::cout << "Before: " << getVector() << std::endl;

	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);
	vectorMergeSort(vec_);
	gettimeofday(&end_time, NULL);
	useconds_t VectorDuration = (end_time.tv_sec - start_time.tv_sec) * 1000000
		+ (end_time.tv_usec - start_time.tv_usec);

	gettimeofday(&start_time, NULL);
	listMergeSort(lst_);
	gettimeofday(&end_time, NULL);
	useconds_t ListDuration = (end_time.tv_sec - start_time.tv_sec) * 1000000
		+ (end_time.tv_usec - start_time.tv_usec);

	std::cout << "After:  " << getVector() << std::endl;
	std::cout << "Time to process a range of: " << vec_.size() << " elements with std::vector : " << printDuration(VectorDuration) << std::endl;
	std::cout << "Time to process a range of: " << lst_.size() << " elements with std::list   : " << printDuration(ListDuration) << std::endl;
}

void	PmergeMe::vectorMerge(std::vector<int>& leftVector, std::vector<int>& rightVector, std::vector<int>& vec) {
	std::vector<int>::iterator vecIt = vec.begin();
	std::vector<int>::iterator leftVecIt = leftVector.begin();
	std::vector<int>::iterator rightVecIt = rightVector.begin();

	while (leftVecIt != leftVector.end() && rightVecIt != rightVector.end()) {
		if (*leftVecIt < *rightVecIt) {
			*vecIt = *leftVecIt;
			leftVecIt++;
		} else {
			*vecIt = *rightVecIt;
			rightVecIt++;
		}
		vecIt++;
	}
	while (leftVecIt != leftVector.end()) {
		*vecIt = *leftVecIt;
		leftVecIt++;
		vecIt++;
	}
	while (rightVecIt != rightVector.end()) {
		*vecIt = *rightVecIt;
		rightVecIt++;
		vecIt++;
	}
}

void	PmergeMe::vectorMergeSort(std::vector<int>& vec) {
		if (vec.size() <= 1)
			return ;
		if (vec.size() < 16) {
			for(size_t i = 0; i < vec.size(); i++) {
				for(size_t j = i; j > 0 && vec[j - 1] > vec[j]; j--) {
					std::swap(vec[j], vec[j - 1]);
				}
			}
		}

		int middle = vec.size() / 2;
		std::vector<int> leftVector = std::vector<int>(vec.begin(), vec.begin() + middle);
		std::vector<int> rightVector = std::vector<int>(vec.begin() + middle, vec.end());

		vectorMergeSort(leftVector);
		vectorMergeSort(rightVector);
		vectorMerge(leftVector, rightVector, vec);
}

void	PmergeMe::listMerge(std::list<int>& leftList, std::list<int>& rightList, std::list<int>& lst) {
	std::list<int>::iterator lstIt = lst.begin();
	std::list<int>::iterator leftListIt = leftList.begin();
	std::list<int>::iterator rightListIt = rightList.begin();

	while (leftListIt != leftList.end() && rightListIt != rightList.end()) {
		if (*leftListIt < *rightListIt) {
			*lstIt = *leftListIt;
			leftListIt++;
		} else {
			*lstIt = *rightListIt;
			rightListIt++;
		}
		lstIt++;
	}
	while (leftListIt != leftList.end()) {
		*lstIt = *leftListIt;
		leftListIt++;
		lstIt++;
	}
	while (rightListIt != rightList.end()) {
		*lstIt = *rightListIt;
		rightListIt++;
		lstIt++;
	}
}

void	PmergeMe::listMergeSort(std::list<int>& lst) {
		if (lst.size() <= 1)
			return ;

		if (lst.size() < 16) {
			for(std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
				std::list<int>::iterator min = it;
				for(std::list<int>::iterator it2 = it; it2 != lst.end(); ++it2) {
					if (*it2 < *min)
						min = it2;
				}
				std::swap(*it, *min);
			}
			return;
		}

		int middle = lst.size() / 2;
		std::list<int>::iterator it = lst.begin();
		for (int i = 0; i < middle; ++i) {
			++it;
		}
		std::list<int> leftList(lst.begin(), it);
		std::list<int> rightList(it, lst.end());

		listMergeSort(leftList);
		listMergeSort(rightList);
		listMerge(leftList, rightList, lst);
}
