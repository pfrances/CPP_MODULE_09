/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:29:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/10 22:51:37 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <limits.h>
#include <stack>

std::stack<int> RPN::NbStack_;
std::stack<char> RPN::OpStack_;
std::ostringstream	RPN::OneLineCalculation_;
std::ostringstream	RPN::IntermediateCalculation_;

RPN::RPN( void ) {
	std::cout << "[RPN] default constructor called." << std::endl;
}

RPN::RPN(const RPN& other) {
	(void)other;
	std::cout << "[RPN] copy constructor called." << std::endl;
}

RPN&	RPN::operator=(const RPN& other) {
	(void)other;
	std::cout << "[RPN] asignment called." << std::endl;
	return *this;
}

RPN::~RPN( void ) {
	std::cout << "[RPN] destructor called." << std::endl;
}

bool RPN::is_operator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::is_digit(char c) {
	return (c >= '0' && c <= '9');
}

void	RPN::Reset(void) {
	while (!NbStack_.empty())
		NbStack_.pop();
	while (!OpStack_.empty())
		OpStack_.pop();
	OneLineCalculation_.str("");
	IntermediateCalculation_.str("");
}

int	RPN::DoDivide(int nb1, int nb2) {
	if (nb2 == 0)
		throw DivisionByZeroException();
	return (nb1 / nb2);
}

int RPN::DoMultiply(int nb1, int nb2) {
	int64_t result = static_cast<int64_t>(nb1) * nb2;
	if (result > INT_MAX || result < INT_MIN)
		throw OverFlowException();
	return (nb1 * nb2);
}

int RPN::DoAdd(int nb1, int nb2) {
	int64_t result = static_cast<int64_t>(nb1) + nb2;
	if (result > INT_MAX || result < INT_MIN)
		throw OverFlowException();
	return (nb1 + nb2);
}

int RPN::DoSubtract(int nb1, int nb2) {
	int64_t result = static_cast<int64_t>(nb1) - nb2;
	if (result > INT_MAX || result < INT_MIN)
		throw OverFlowException();
	return (nb1 - nb2);
}

void RPN::DoOperation(void) {
	int	result;
	int		nb2 = NbStack_.top();
	NbStack_.pop();
	int		nb1 = NbStack_.top();
	NbStack_.pop();
	char op = OpStack_.top();
	OpStack_.pop();

	if (op == '+')
		result = DoAdd(nb1, nb2);
	else if (op == '-')
		result = DoSubtract(nb1, nb2);
	else if (op == '*')
		result = DoMultiply(nb1, nb2);
	else if (op == '/')
		result = DoDivide(nb1, nb2);
	else
		throw InvalidExpressionException();
	OneLineCalculation_ <<  " " << op << " " << nb2;
	IntermediateCalculation_ << "	" << nb1 << " " << op << " " << nb2 << " = " << result << std::endl;
	NbStack_.push(result);
}

void	RPN::CalculateRpn(std::string& expression) {
	Reset();
	if (expression.length() == 0 || expression.find_first_not_of(" \t") == std::string::npos)
		throw EmptyExpressionException();
	for (size_t i = 0; i < expression.length(); i++) {
		if (expression.at(i) == ' ' || expression.at(i) == '\t') {
			continue ;
		} else if (is_operator(expression.at(i))) {
			OpStack_.push(expression.at(i));
		} else if (is_digit(expression.at(i))) {
			NbStack_.push(expression.at(i) - '0');
			if (OneLineCalculation_.str().length() == 0)
				OneLineCalculation_ << expression.at(i);
		} else {
			throw InvalidExpressionException();
		}
		if (NbStack_.size() >= 2 && OpStack_.size() >= 1) {
			DoOperation();
		}
	}
	if (NbStack_.size() != 1 || OpStack_.size() != 0)
		throw InvalidExpressionException();
	std::cout << "[One Line Calculation]: " << OneLineCalculation_.str() << std::endl;
	if (IntermediateCalculation_.str().length() != 0) {
		std::cout << "[Intermediate Calculation]:" << std::endl;
		std::cout << IntermediateCalculation_.str();
	}
	std::cout << "[Result]: " << NbStack_.top() << std::endl;
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
