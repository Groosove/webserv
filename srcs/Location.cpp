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
#include <fcntl.h>
#include <unistd.h>
#include "utils.hpp"

void Location::setRequestLimits(const std::string &body_size) {
	_request_limits = std::stoi(ft_strtrim(body_size, " \t"));
}

void Location::setAutoIndex(const std::string &autoindex) {
	if (autoindex.find("on", 0) != std::string::npos)
		_autoindex = true;
	if (autoindex.find("off", 0) != std::string::npos)
		_autoindex = false;
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

Location::Location(): _root(), _index(), _allow_methods(0), _autoindex(false), _request_limits(0) {}

bool Location::checkAllowMethod(const char *method) {
	std::vector<std::string>::iterator begin = _allow_methods.begin();
	while (begin != _allow_methods.end()) { // проверка доступности метода
		if ((*begin).find(method) != std::string::npos)
			break;
		else if (begin == _allow_methods.end() - 1 && (*begin).find(method) == std::string::npos)
			return false;
		begin++;
	}
	return true;
}

void Location::setCgiPath(const std::string &path_and_file) {
	size_t pos;
	if ((pos = path_and_file.find(' ')) == std::string::npos)
		std::cerr << "Error cgi_path" << std::endl;
	_cgi.insert(std::make_pair(path_and_file.substr(0, pos), path_and_file.substr(pos + 1, path_and_file.size())));
}
