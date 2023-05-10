/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:29:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/10 22:33:38 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <iostream>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <string>
#include <sstream>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

std::vector<int>	PmergeMe::vec_;
std::list<int>		PmergeMe::lst_;

PmergeMe::PmergeMe( void ) {
	std::cout << "[PmergeMe] default constructor called." << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
	std::cout << "[PmergeMe] copy constructor called." << std::endl;
}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other) {
	*this = other;
	std::cout << "[PmergeMe] asignment called." << std::endl;
	return *this;
}

PmergeMe::~PmergeMe( void ) {
	std::cout << "[PmergeMe] destructor called." << std::endl;
}

void	PmergeMe::Reset(void) {
	vec_.clear();
	lst_.clear();
}

bool	PmergeMe::IsValidNumber(char *nb_str) {
	double result = 0;
	int i = 0;
	int	sign = 1;
	if (nb_str[0] == '+' || nb_str[0] == '-') {
		if (nb_str[0] == '-') {
			sign = -1;
		}
		i++;
	}
	while (nb_str[i]) {
		if (nb_str[i] < '0' || nb_str[i] > '9')
			return false;
		result = result * 10 + (nb_str[i] - '0');
		if (result > INT_MAX)
			return false;
		i++;
	}
	if (i == 0)
		return false;
	return ((result * sign) >= 0);
}

bool	PmergeMe::HasDoublon(void) {
	std::vector<int>::iterator it = vec_.begin();
	std::vector<int>::iterator ite = vec_.end();
	while (it != ite) {
		if (std::count(vec_.begin(), vec_.end(), *it) > 1) {
			std::cout << "Error: " << *it << " is a doublon." << std::endl;
			return true;
		}
		it++;
	}
	return false;
}

std::string	PmergeMe::GetVector(void) {
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

std::string	PmergeMe::GetList(void) {
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

std::string	PmergeMe::PrintDuration(useconds_t duration) {
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

void	PmergeMe::MergeSort(char **argv) {

	Reset();

	int i = 1;
	while (argv[i]) {
		if (IsValidNumber(argv[i]) == false) {
			std::cout << "Error: '" << argv[i] << "' is not a valid number." << std::endl;
			return ;
		}
		vec_.push_back(atoi(argv[i]));
		lst_.push_back(atoi(argv[i]));
		i++;
	}
	if (HasDoublon() == true)
		return ;

	std::cout << "Before: " << GetVector() << std::endl;

	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);
	VectorMergeSort(vec_);
	gettimeofday(&end_time, NULL);
	useconds_t VectorDuration = (end_time.tv_sec - start_time.tv_sec) * 1000000
		+ (end_time.tv_usec - start_time.tv_usec);

	gettimeofday(&start_time, NULL);
	ListMergeSort(lst_);
	gettimeofday(&end_time, NULL);
	useconds_t ListDuration = (end_time.tv_sec - start_time.tv_sec) * 1000000
		+ (end_time.tv_usec - start_time.tv_usec);

	std::cout << "After:  " << GetList() << std::endl;
	std::cout << "Time to process a range of: " << vec_.size() << " elements with std::vector : " << PrintDuration(VectorDuration) << std::endl;
	std::cout << "Time to process a range of: " << lst_.size() << " elements with std::list   : " << PrintDuration(ListDuration) << std::endl;
}

void	PmergeMe::VectorMerge(std::vector<int> &leftVector, std::vector<int> &rightVector, std::vector<int> &vec) {
	while (leftVector.size() > 0 && rightVector.size() > 0) {
		if (leftVector.front() < rightVector.front()) {
			vec.push_back(leftVector.front());
			leftVector.erase(leftVector.begin());
		} else {
			vec.push_back(rightVector.front());
			rightVector.erase(rightVector.begin());
		}
	}
	while (leftVector.size() > 0) {
			vec.push_back(leftVector.front());
			leftVector.erase(leftVector.begin());
	}
	while (rightVector.size() > 0) {
			vec.push_back(rightVector.front());
			rightVector.erase(rightVector.begin());
	}
}

void	PmergeMe::VectorMergeSort(std::vector<int> &vec) {
		if (vec.size() <= 1)
			return	;

		int middle = vec.size() / 2;
		std::vector<int> leftVector = std::vector<int>(vec.begin(), vec.begin() + middle);
		std::vector<int> rightVector = std::vector<int>(vec.begin() + middle, vec.end());
		vec.clear();

		VectorMergeSort(leftVector);
		VectorMergeSort(rightVector);
		VectorMerge(leftVector, rightVector, vec);
}

void	PmergeMe::ListMerge(std::list<int> &leftList, std::list<int> &rightList, std::list<int> &lst) {
	while (leftList.size() > 0 && rightList.size() > 0) {
		if (leftList.front() < rightList.front()) {
			lst.push_back(leftList.front());
			leftList.erase(leftList.begin());
		} else {
			lst.push_back(rightList.front());
			rightList.erase(rightList.begin());
		}
	}
	while (leftList.size() > 0) {
			lst.push_back(leftList.front());
			leftList.erase(leftList.begin());
	}
	while (rightList.size() > 0) {
			lst.push_back(rightList.front());
			rightList.erase(rightList.begin());
	}
}

void	PmergeMe::ListMergeSort(std::list<int> &lst) {
		if (lst.size() <= 1)
			return	;

		int middle = lst.size() / 2;
		std::list<int>::iterator it = lst.begin();
		for (int i = 0; i < middle; ++i) {
			++it;
		}
		std::list<int> leftList(lst.begin(), it);
		std::list<int> rightList(it, lst.end());
		lst.clear();

		ListMergeSort(leftList);
		ListMergeSort(rightList);
		ListMerge(leftList, rightList, lst);
}
