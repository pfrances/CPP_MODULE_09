/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:56:36 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/10 11:01:40 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# ifndef REVIEW
#  define REVIEW 0
# endif

# include <stack>
# include <string>
# include <sstream>

class RPN {
public:
	RPN(void);
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	virtual ~RPN(void);

	static void	calculateRpn(std::string& expression);

	class InvalidExpressionException : public std::exception {
		virtual const char* what() const throw();
	};
	class EmptyExpressionException : public std::exception {
		virtual const char* what() const throw();
	};
	class DivisionByZeroException : public std::exception {
		virtual const char* what() const throw();
	};
	class OverFlowException : public std::exception {
		virtual const char* what() const throw();
	};

private:
	static std::stack<int>		nbStack_;
	static std::stack<char>		opStack_;
	static std::ostringstream	intermediateCalculation_;

	static bool				isOperator(char c);
	static bool				isDigit(char c);
	static void				reset(void);

	static int				doDivide(int nb1, int nb2);
	static int				doMultiply(int nb1, int nb2);
	static int				doAdd(int nb1, int nb2);
	static int				doSubtract(int nb1, int nb2);
	static void				doOperation(void);
};

#endif
