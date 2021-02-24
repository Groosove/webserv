//
// Created by Fenix Lavon on 2/24/21.
// Copyright (c) 2021 All rights reserved.
//

#include "utils.hpp"

void *ft_memjoin(char *dst, char *src, int &dst_size, int src_size)
{
	char *result;
	int count;

	if (!dst || !src || !(result = (char *)malloc((dst_size + src_size + 1))))
		return (nullptr);
	count = 0;
	while (dst_size--)
		result[count++] = *dst++;
	while (src_size--)
		result[count++] = *src++;
	result[count] = 0;
	dst_size = count;
	return (result);
}