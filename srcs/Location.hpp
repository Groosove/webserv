//
// Created on 2/4/21 by.
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include <iostream>
#include <vector>
#include <map>

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
	std::string					_root_dir;
	std::string					_index;
	std::vector<std::string>	_allow_methods;
	bool						_autoindex;
	size_t						_request_limits;
public:
	explicit Location();
	~Location();

	void parseLocation();
};