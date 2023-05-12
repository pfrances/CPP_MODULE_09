/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:29:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/12 14:09:44 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <limits.h>
#include <stack>

std::stack<int> RPN::nbStack_;
std::stack<char> RPN::opStack_;
std::ostringstream	RPN::intermediateCalculation_;

RPN::RPN( void ) {
	// std::cout << "[RPN] default constructor called." << std::endl;
}

RPN::RPN(const RPN& other) {
	(void)other;
	// std::cout << "[RPN] copy constructor called." << std::endl;
}

RPN&	RPN::operator=(const RPN& other) {
	(void)other;
	// std::cout << "[RPN] asignment called." << std::endl;
	return *this;
}

RPN::~RPN( void ) {
	// std::cout << "[RPN] destructor called." << std::endl;
}

bool RPN::isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isDigit(char c) {
	return (c >= '0' && c <= '9');
}

void	RPN::reset(void) {
	nbStack_ = std::stack<int>();
	opStack_ = std::stack<char>();
	intermediateCalculation_.str("");
}

int	RPN::doDivide(int nb1, int nb2) {
	if (nb2 == 0)
		throw DivisionByZeroException();
	return (nb1 / nb2);
}

int RPN::doMultiply(int nb1, int nb2) {
	int64_t result = static_cast<int64_t>(nb1) * nb2;
	if (result > INT_MAX || result < INT_MIN)
		throw OverFlowException();
	return (nb1 * nb2);
}

int RPN::doAdd(int nb1, int nb2) {
	int64_t result = static_cast<int64_t>(nb1) + nb2;
	if (result > INT_MAX || result < INT_MIN)
		throw OverFlowException();
	return (nb1 + nb2);
}

int RPN::doSubtract(int nb1, int nb2) {
	int64_t result = static_cast<int64_t>(nb1) - nb2;
	if (result > INT_MAX || result < INT_MIN)
		throw OverFlowException();
	return (nb1 - nb2);
}

void RPN::doOperation(void) {
	int		result;

	int		nb2 = nbStack_.top();
	nbStack_.pop();

	int		nb1 = nbStack_.top();
	nbStack_.pop();

	char op = opStack_.top();
	opStack_.pop();

	if (op == '+')
		result = doAdd(nb1, nb2);
	else if (op == '-')
		result = doSubtract(nb1, nb2);
	else if (op == '*')
		result = doMultiply(nb1, nb2);
	else if (op == '/')
		result = doDivide(nb1, nb2);
	else
		throw InvalidExpressionException();
	if (REVIEW) {
		intermediateCalculation_ << "	" << nb1 << " " << op << " " << nb2 << " = " << result << std::endl;
	}
	nbStack_.push(result);
}

void	RPN::calculateRpn(std::string& expression) {
	reset();
	if (expression.length() == 0)
		throw EmptyExpressionException();
	std::string::const_iterator it = expression.begin();
	for (; it != expression.end(); it++) {
		if (*it == ' ' || *it == '\t') {
			continue ;
		} else if (isOperator(*it)) {
			opStack_.push(*it);
			if (nbStack_.size() >= 2 && opStack_.size() >= 1) {
				doOperation();
			} else {
				throw InvalidExpressionException();
			}
		} else if (isDigit(*it)) {
			nbStack_.push(*it - '0');
		} else {
			throw InvalidExpressionException();
		}
	}
	if (nbStack_.size() != 1 || opStack_.size() != 0)
		throw InvalidExpressionException();
	if (REVIEW && intermediateCalculation_.str().length() != 0) {
		std::cout << "[Intermediate Calculation]:" << std::endl;
		std::cout << intermediateCalculation_.str();
		std::cout << "[Result]: " << nbStack_.top() << std::endl;
	} else {
		std::cout << nbStack_.top() << std::endl;
	}
}

const char* RPN::InvalidExpressionException::what() const throw() {
	return "Invalid expression";
}

const char* RPN::EmptyExpressionException::what() const throw() {
	return "Empty expression";
}

const char* RPN::DivisionByZeroException::what() const throw() {
	return "Division by zero";
}

const char* RPN::OverFlowException::what() const throw() {
	return "Overflow";
}
