//
// WebServ
//
// Created by Артур Лутфуллин on 06.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#pragma once
#include <iostream>

std::string	ft_strtrim(const std::string &s1, const std::string& set);
int			ft_strchr(const std::string& str, int ch);


template <class InputIterator>
bool ft_compare(InputIterator first, InputIterator last, const std::string& src,
				typename std::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0);
bool ft_compare(const std::string& dst, const std::string& src, size_t n);
bool ft_compare(const std::string &dst, const std::string& src);