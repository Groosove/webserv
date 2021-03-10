//
// WebServ
//
// Created by Артур Лутфуллин on 06.02.2021.
// Copyright (c) 2021 Артур Лутфуллин. All right reserved. 
//

#include "utils.hpp"
bool ft_compare(const std::string &dst, const std::string& src) {
	for (size_t i = 0; dst[i] || src[i]; ++i) {
		if (dst[i] != src[i])
			return false;
	}
	return true;
}

bool ft_compare(const char *dst, const char * src) {
	if (dst == nullptr)
		return false;
	if (src == nullptr)
		return false;
	for (size_t i = 0; dst[i] || src[i]; ++i) {
		if (dst[i] != src[i])
			return false;
	}
	return true;
}

//template <class InputIterator>
//bool ft_compare(InputIterator first, InputIterator last, const std::string& src,
//		typename std::enable_if<std::__is_input_iterator<InputIterator>::value>::type*) {
//	for (size_t i = 0; first != last || src[i]; ++i, ++first) {
//		if (*first != src[i])
//			return false;
//	}
//	return true;
//}

bool ft_compare(const std::string& dst, const std::string& src, size_t n) {
	for (size_t i = 0; i < n && (dst[i] || src[i]); ++i) {
		if (dst[i] != src[i])
			return false;
	}
	return true;
}