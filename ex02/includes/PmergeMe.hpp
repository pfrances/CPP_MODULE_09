/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:47:07 by pfrances          #+#    #+#             */
/*   Updated: 2023/05/12 16:26:53 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_MERGE_ME_HPP
# define P_MERGE_ME_HPP

# ifndef UNIQ
#  define UNIQ 0
# endif

# include <vector>
# include <list>
# include <string>
# include <unistd.h>

class PmergeMe {
public:
	PmergeMe(void);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	virtual ~PmergeMe(void);

	static void				mergeSort(char **nbArr, int arrSize);

private:
	static std::vector<int>	vec_;
	static std::list<int>	lst_;

	static bool				ConvertNbWithCheck(char *nbStr, int *nb);

	static void				vectorMergeSort(std::vector<int>& vec);
	static void				vectorMerge(std::vector<int>& leftVector, std::vector<int>& rightVector, std::vector<int>& vec);

	static void				listMergeSort(std::list<int>& lst);
	static void				listMerge(std::list<int>& leftList, std::list<int>& rightList, std::list<int>& lst);

	static std::string		getVector(void);
	static std::string		getList(void);
	static std::string		printDuration(useconds_t duration);
};

#endif
