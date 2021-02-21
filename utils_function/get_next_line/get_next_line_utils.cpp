#include "get_next_line.hpp"

char	*gnl_strdup(char *str, int f)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[len])
		len++;
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	if (f)
		free(str);
	return (res);
}

char	*gnl_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*gnl_join(char *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		++i;
	while (s2[j])
		++j;
	if (!(res = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		res[i] = s1[i];
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}
