//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "Location.hpp"
#include <iostream>
#include <fstream>

Location::Location(std::ifstream &config_name) {
	std::string buf;
	size_t i;
	while (std::getline(config_name, buf)) {
		i = 0;
		if ((i = buf.find("root:", 0, 5)) != std::string::npos)
			setRoot(buf.substr(i + 5,  buf.length()));
		else if ((i = buf.find("index:", 0, 6)) != std::string::npos)
			setIndex(buf.substr(i + 6, buf.length()));
		else if ((i = buf.find("allow_methods:", 0, 14)) != std::string::npos)
			setAllowMethods(buf.substr(i + 14, buf.length()));
	}
	std::cout << "KEK: " << _root << std::endl;
	std::cout << "KEK: " << _index << std::endl;
	std::cout << "KEK: " << *_allow_methods.begin() << std::endl;
}

void Location::setRoot(const std::string &root) {
	_root = ft_strtrim(root, " \t");
}

void Location::setIndex(const std::string &index) {
	_index =  ft_strtrim(index, " \t");
}

void Location::setAllowMethods(const std::string &allow_methods) {
	_allow_methods.insert(_allow_methods.begin(),ft_strtrim(allow_methods, " \t"));
}