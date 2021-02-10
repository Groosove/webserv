//
// WebServ
//
// Created by Артур Лутфуллин on 10.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include "utils.hpp"
char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		i;

	i = -1;
	if (!(dst = (char*)malloc((ft_strlen(s1) + 1))))
		return (0);
	while (s1[++i] != 0)
		dst[i] = s1[i];
	dst[i] = 0;
	return (dst);
}