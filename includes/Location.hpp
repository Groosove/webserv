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

// Инклюды для проверки доступности директории, поиска файлов и stat
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

class Location {

public:
	/* Constructor */
	Location();

	/* Destructor */
	~Location() {};

	/* Setters */
	void								setRequestLimits(const std::string& body_size);
	void								setAutoIndex(const std::string& autoindex);
	void								setRoot(const std::string& root);
	void								setIndex(const std::string& index);
	void								setAllowMethods(const std::string& allow_methods);
	void								setCgiPath(const std::string& path_and_file);

	/* Getters */
	std::string&						getRoot() { return _root; }
	std::string&						getIndex() { return _index; }
	bool								getAutoIndex() const { return _autoindex; }
	int 								getRequestLimits() const { return _request_limits; }
	std::map<std::string, std::string>&	getCgi() { return _cgi; }

	/* Validation */
	bool 								checkAllowMethod(const char* method);

private:
	std::map<std::string, std::string>  _cgi;
	std::string							_root;
	std::string							_index;
	std::vector<std::string>			_allow_methods;
	bool								_autoindex;
	int									_request_limits;
};