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

enum Method {
	GET = 0,
	POST,
	PUT,
	HEAD,
};

class Location {
private:
//	std::map<std::string, std::string>  _value_location;
	std::map<std::string, std::string>  _cgi;
	std::string							_root;
	std::string							_index;
	std::vector<std::string>			_allow_methods;
	bool								_autoindex;
	size_t								_request_limits;
public:
	Location();
	~Location() {};

	void						setRequestLimits(const std::string& body_size);
	void						setAutoIndex(const std::string& autoindex);
	void						setRoot(const std::string& root);
	void						setIndex(const std::string& index);
	void						setAllowMethods(const std::string& allow_methods);
	void						setCgiPath(const std::string& path_and_file);

	std::string&				getRoot() { return _root; }
	std::string&				getIndex() { return _index; }
	bool getAutoIndex() const { return _autoindex; }
	size_t getRequestLimits() const { return _request_limits; }
	std::vector<std::string>	getAllowMethods() { return _allow_methods; }
	std::map<std::string, std::string>&	getCgi() { return _cgi; }

	bool 						checkAllowMethod(const char* method);
	bool						validationLocation(const char* method);
	bool						tryOpenDir();
	bool						tryOpenFile();
	bool						findCgiPath(const std::string& value);
	bool						findCgiFile(const std::string& value);
};