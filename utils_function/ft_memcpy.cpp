//
// Created by Fenix Lavon on 2/21/21.
// Copyright (c) 2021 All rights reserved.
//

#include "utils.hpp"

void	ft_memcpy(const void *dst, const void *src, size_t n)
{
	unsigned int* tmp1;
	unsigned int* tmp2;
	unsigned char *c_dst;
	unsigned char *c_src;

	tmp1 = (unsigned int *)dst;
	tmp2 = (unsigned int *)src;
	while (n > 4) {
		*tmp1++ = *tmp2++;
		n -= 4;
	}

	c_dst = reinterpret_cast<unsigned char *>(tmp1);
	c_src = reinterpret_cast<unsigned char *>(tmp2);
	while (n-- != 0)
		*c_dst++ = *c_src++;
}
