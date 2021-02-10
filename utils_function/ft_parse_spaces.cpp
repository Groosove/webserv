//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "utils.hpp"
#include <vector>

std::vector<std::string>	ft_parse_spaces(const std::string& line) {
	std::vector<std::string>	vect;
	size_t						pos = 0;
	size_t 						tmp_pos = 0;
	while (line[pos] != '\n' && line[pos]) {
		if (line[pos] == '\r' || line[pos] == '\n' || line[pos] == '\t') {
			vect.push_back(line.substr(tmp_pos, pos));
			tmp_pos = pos;
		}
		pos++;
	}
	return vect;
}
