/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:47:07 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/12 12:39:05 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_MERGE_ME_HPP
# define P_MERGE_ME_HPP

# include <vector>
# include <list>
# include <string>
# include <unistd.h>

class PmergeMe {
public:
	PmergeMe(void);
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	virtual ~PmergeMe(void);

	static void				MergeSort(char **argc);

private:
	static std::vector<int>	vec_;
	static std::list<int>	lst_;

	static bool				IsValidNumber(char *nb_str);
	static bool				HasDoublon(void);
	static void				reset(void);

	static void				VectorMergeSort(std::vector<int> &vec);
	static void				VectorMerge(std::vector<int> &leftVector, std::vector<int> &rightVector, std::vector<int> &vec);

	static void				ListMergeSort(std::list<int> &lst);
	static void				ListMerge(std::list<int> &leftList, std::list<int> &rightList, std::list<int> &lst);

	static std::string		GetVector(void);
	static std::string		GetList(void);
	static std::string		PrintDuration(useconds_t duration);
};

#endif
