//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "utils.hpp"

class HTTPRequest {
private:
	std::map<std::string, std::string>	_request_params;
	char *		_method;
	char *		_path;
	char *		_version_http;
	char *		_host_url;
public:
	explicit HTTPRequest(const char *buf);
	~HTTPRequest();
	std::map<std::string, std::string>		parse_request_http(const char * buf);
	void									parseFirstLine(const char * line);

	void								setRequestParams(std::map<std::string, std::string> request_params);

	const char *				getMethod(void) { return _method; };
	const char *					getPath(void) {return _path; };
	const char *				getVersionHTTP(void) { return _version_http; };
	const char *					getHostUrl(void) { return _host_url; };

	void								setMethod(char * method);
	void								setPath(char * path);
	void								setVersionHTTP(char * version_http);
	void								setHostUrl(char * host_url);

};