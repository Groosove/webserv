//
// Created by Fenix Lavon on 2/20/21.
// Copyright (c) 2021 All rights reserved.
//

#include "utils.hpp"

size_t ft_find(const char *str, const char *find) {
	size_t size = ft_strlen(str);
	int j;
	for (size_t i = 0; i < size; ++i) {
		if (str[i] == *find) {
			j = 0;
			for (; find[j]; ++j)
				if (str[i + j] != find[j]) break;
			if (!find[j])	return (i);
		}
	}
	return (-1);
}