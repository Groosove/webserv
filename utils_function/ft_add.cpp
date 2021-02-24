//
// Created on 2/24/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//
#include "utils.hpp"

void	*ft_memjoin(void *dst, const void *src, size_t dst_size, size_t src_size)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	tmp1 = (unsigned char *)dst;
	tmp2 = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (0);
	unsigned char*  tmp3 = (unsigned char*)malloc(dst_size + src_size + 1);
	while (dst_size-- != 0)
		*tmp3++ = *tmp1++;
	while (src_size-- != 0)
		*tmp3++ = *tmp2++;
	return (tmp3);
}

void ft_add_bytess(char *&dst, char *src, int &dst_size, int src_size) {
	char *tmp = (char *)ft_memjoin(dst, src, dst_size, src_size);
	dst_size += src_size;
	dst = tmp;
}