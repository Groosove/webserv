#pragma once

# include <stdlib.h>
# include <unistd.h>
#define BUFFER_SIZE 32
char	*gnl_strdup(char *str, int f);
char	*gnl_strchr(const char *str, int c);
char	*gnl_join(char *s1, char const *s2);
int		get_next_line(int fd, char **line);

