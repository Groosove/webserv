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

int ft_hex2dec(char c) {
	if (('0' <= c && c <= '9'))
		return (c - '0');
	else if (('a' <= c && c <= 'f'))
		return (c - 'a' + 10);
	else
		return (c - 'A' + 10);
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
		result = result * 16 + ft_hex2dec(*src);
		src++;
	}
	return (result * negative);
}