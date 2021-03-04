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

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;

	if (set == 0 || s1 == 0)
		return (0);
	while (*s1 != 0 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	while (size && ft_strchr(set, s1[size]))
		size--;
	return (ft_substr((char *)s1, 0, size + 1));
}