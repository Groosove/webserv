//
// WebServ
//
// Created by Артур Лутфуллин on 06.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include "utils.hpp"
std::string	ft_strtrim(const std::string &s1, const std::string& set)
{
	size_t	start;
	size_t	end;
	size_t	index = 0;

	while (s1[index] && ft_strchr(set, s1[index]) != -1)
		index++;
	start = index;
	end = s1.length();
	while (end && ft_strchr(set, s1[end]) != -1)
		--end;
	return s1.substr(start, end + 1);
}