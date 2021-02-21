//
// Created by Fenix Lavon on 2/21/21.
// Copyright (c) 2021 All rights reserved.
//

#include "utils.hpp"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	tmp1 = (unsigned char *)dst;
	tmp2 = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (0);
	while (n-- != 0)
		*tmp1++ = *tmp2++;
	return (dst);
}
