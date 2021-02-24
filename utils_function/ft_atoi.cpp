//
// Created by Fenix Lavon on 2/20/21.
// Copyright (c) 2021 All rights reserved.
//

#include "utils.hpp"

int		ft_atoi(const char *src)
{
	long int	result;
	int			negative;

	result = 0;
	while (*src != 0 && ((*src >= 9 && *src <= 13) || *src == 32))
		src++;
	negative = (*src == '-') ? -1 : 1;
	if (*src == '+' || *src == '-')
		src++;
	while (*src != 0 && (*src >= 48 && *src <= 57))
		result = (result * 10) + *src++ - '0';
	return (result * negative);
}

int		ft_atoi_chunk(const char *src)
{
	long int	result;
	int			negative;

	result = 0;
	while (*src != 0 && ((*src >= 9 && *src <= 13) || *src == 32))
		src++;
	negative = (*src == '-') ? -1 : 1;
	if (*src == '+' || *src == '-')
		src++;
	while (*src != 0 && ((*src >= 48 && *src <= 57) || (*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z'))) {
		result *= 16;
		result += *src - ((*src >= 48 && *src <= 57) ? '0' : (*src >= 'a' && *src <= 'z') ? ('a' + 10) : ('A' + 10));
		src++;
	}
	return (result * negative);
}