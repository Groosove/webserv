//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "utils.hpp"

enum Method {
	GET = 0,
	POST,
	PUT,
	HEAD,
};

class Location {
private:
//	std::map<std::string, std::string>  _value_location;
//	std::map<std::string, std::string>  _cgi;
	std::string					_root;
	std::string					_index;
	std::vector<std::string>	_allow_methods;
	bool						_autoindex;
	size_t						_request_limits;
public:
	explicit Location(std::ifstream& config_name);
	~Location() {};

	void	setRoot(const std::string& root);
	void	setIndex(const std::string& index);
	void	setAllowMethods(const std::string& allow_methods);
	void parseLocation();
};