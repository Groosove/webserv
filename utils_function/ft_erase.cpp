//
// Created by Fenix Lavon on 2/25/21.
// Copyright (c) 2021 All rights reserved.
//

#include "utils.hpp"

char *ft_erase(char *&dst, int dst_size, int len) {
	char *result = (char *)malloc(len + 1);
	int index = 0;
	int start = 0;
	int size = dst_size - index;
	char *copy_dst = (char *)malloc(size);

	while (len-- && dst[start])
		result[index++] = dst[start++];
	result[index] = '\0';
	index = 0;
	while (dst[start])
		copy_dst[index++] = dst[start++];
	copy_dst[index] = '\0';
	dst = copy_dst;
	return result;
}