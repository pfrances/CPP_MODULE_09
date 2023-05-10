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

# include <stack>
# include <string>
# include <sstream>

class RPN {
public:
	RPN(void);
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	virtual ~RPN(void);

	static void	CalculateRpn(std::string& expression);

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
	static std::stack<int>		NbStack_;
	static std::stack<char>		OpStack_;
	static std::ostringstream	OneLineCalculation_;
	static std::ostringstream	IntermediateCalculation_;

	static bool				is_operator(char c);
	static bool				is_digit(char c);
	static void				Reset(void);

	static int				DoDivide(int nb1, int nb2);
	static int				DoMultiply(int nb1, int nb2);
	static int				DoAdd(int nb1, int nb2);
	static int				DoSubtract(int nb1, int nb2);
	static void				DoOperation(void);
};

#endif
