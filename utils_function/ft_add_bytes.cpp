//
// Created by Fenix Lavon on 2/23/21.
// Copyright (c) 2021 All rights reserved.
//

#include "utils.hpp"

void ft_add_bytes(char *&dst, char *src, int &dst_size, int src_size) {
	char *tmp = (char *)malloc(dst_size + src_size + 1);
	tmp = (char *)ft_memcpy(tmp, dst, dst_size);
	tmp = (char *)ft_memcpy(tmp + dst_size, src, src_size);
	dst_size += src_size;
	dst = tmp;
}