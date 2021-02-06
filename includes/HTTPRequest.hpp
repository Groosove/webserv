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
#include <sstream>

class HTTPRequest {
private:
	std::map<std::string, std::string>	_request_params;
	std::string							_method;
	std::string							_path;
	std::string							_version_http;
	std::string							_host_url;
public:
	explicit HTTPRequest(const std::string& buf);
	~HTTPRequest();
	std::map<std::string, std::string>	parse_request_http(const std::string& buf);

	void								setRequestParams(std::map<std::string, std::string> request_params);

	const std::string&					getMethod(void);
	const std::string&					getPath(void);
	const std::string&					getVersionHTTP(void);
	const std::string&					getHostUrl(void);

	void								setMethod(const std::string& method);
	void								setPath(const std::string& path);
	void								setVersionHTTP(const std::string& version_http);
	void								setHostUrl(const std::string& host_url);

};