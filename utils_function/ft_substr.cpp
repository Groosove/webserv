//
// WebServ
//
// Created by Артур Лутфуллин on 06.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include "utils.hpp"
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int				index;
	char			*dst;

	if (!s)
		return (0);
	if (ft_strlen(s) <= start || len == 0)
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	index = 0;
	if ((dst = (char *)malloc(sizeof(char) * (len + 1))) != 0)
		while (len-- != 0 && s[start] != 0)
			dst[index++] = s[start++];
	if (index == 0)
		return (0);
	dst[index] = 0;
	return (dst);
}