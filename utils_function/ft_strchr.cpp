//
// WebServ
//
// Created by Артур Лутфуллин on 06.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include "utils.hpp"

int	ft_strchr(const std::string& str, int ch)
{
	int	index;

	index = -1;
	while (str[++index] != 0)
		if (str[index] == ch)
			return (index);
	if (str[index] == ch)
		return (index);
	return (-1);
}