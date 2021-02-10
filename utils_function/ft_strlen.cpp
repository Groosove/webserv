//
// WebServ
//
// Created by Артур Лутфуллин on 10.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include "utils.hpp"

size_t	ft_strlen(const char *str)
{
	int count;

	count = 0;
	while (str[count] != 0)
		count++;
	return (count);
}