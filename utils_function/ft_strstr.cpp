//
// Created by Freely Kathryne on 3/5/21.
//

#include "utils.hpp"

size_t ft_strnstr(char *s1, char *s2, size_t len)
{
	size_t	i;
	size_t	s2_len;
	s2_len = ft_strlen(s2);
	i = 0;
	while (i < len + 1)
	{
		if (strncmp((s1 + i), s2, s2_len) == 0)
			return (i);
		i++;
	}
	return (0);
}