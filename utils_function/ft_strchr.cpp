//
// WebServ
//
// Created by Артур Лутфуллин on 06.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include "utils.hpp"

int	ft_strchr(const std::string& str, int ch)
{
	char			*src;
	int	index;

	src = (char *)str.c_str();
	index = 0;
	while (src[index] != 0)
		if (src[index++] == ch)
			return (index);
	if (src[index] == ch)
		return (index);
	return (-1);
}

int ft_strchr(const char *str, int ch)
{
	char			*src;
	int	index;

	src = (char *)str;
	index = 0;
	while (src[index] != 0)
		if (src[index++] == ch)
			return (index);
	if (src[index] == ch)
		return (index);
	return (-1);
}
