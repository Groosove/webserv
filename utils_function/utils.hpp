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
std::string					ft_strtrim(const std::string &s1, const std::string& set);
int							ft_strchr(const std::string& str, int ch);
int							ft_strchr(const char *str, int ch);
std::vector<std::string>	ft_parse_spaces(const std::string& line);


//template <class InputIterator>
//bool ft_compare(InputIterator first, InputIterator last, const std::string& src,
//				typename std::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0);
bool ft_compare(const std::string& dst, const std::string& src, size_t n);
bool ft_compare(const std::string &dst, const std::string& src);
bool ft_compare(const char *dst, const char * src);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_read_line(void);
char	**ft_split(char const *s, char c);
std::vector<std::string> ft_split(const std::string &s, const std::string& c, size_t i);
