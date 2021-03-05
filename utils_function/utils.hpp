//
// WebServ
//
// Created by Артур Лутфуллин on 06.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#pragma once
#include <iostream>
#include <cstdlib>
#include "unistd.h"
#include <vector>
#include "get_next_line.hpp"
int		get_next_line(int fd, char **line);
std::string					ft_strtrim(const std::string &s1, const std::string& set);
int							ft_strchr(const std::string& str, int ch);
int							ft_strchr(const char *str, int ch);
bool 	ft_compare(const char *dst, const char * src);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *src);
int		ft_atoi_chunk(const char *src);
size_t	ft_find(const char *str, const char *find);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strtrim(char *s1, char const *set);
void 	*ft_memjoin(char *dst, char *src, size_t &dst_size, size_t src_size);
char *ft_erase(char *&dst, int dst_size, int len);