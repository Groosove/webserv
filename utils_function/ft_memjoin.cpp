//
// Created by Fenix Lavon on 2/24/21.
// Copyright (c) 2021 All rights reserved.
//

#include "utils.hpp"

void *ft_memjoin(char *dst, char *src, size_t &dst_size, size_t src_size)
{
	char *result;
	int count;

	if (!dst || !src || !(result = (char *)malloc((dst_size + src_size + 1))))
		return (nullptr);
	count = 0;
	ft_memcpy(result + count, dst, dst_size);
	count += dst_size;
	ft_memcpy(result + count, src, src_size);
	count += src_size;
	result[count] = 0;
	dst_size = count;
	free(dst);
	return (result);
}