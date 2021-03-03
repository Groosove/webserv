//
// WebServ
//
// Created by Артур Лутфуллин on 06.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include "utils.hpp"

int	ft_strchr(const std::string& str, int ch)
{
	int	index = -1;

	while (str[++index] != 0 && str[index] != ch);
	return (str[index] == ch) ? index : -1;
}

int	ft_strchr(const char *str, int ch)
{
	int	index = -1;

	while (str[++index] != 0 && str[index] != ch);
	return (str[index] == ch) ? index : -1;
}