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

enum ParsingRequest {
	parse_first_line,
	parse_other_headers,
	parse_body,
	complite,
};

class HTTPRequest {
private:
	std::map<std::string, std::string>	_request_params;
	char *		_method;
	char *		_path;
	char *		_version_http;
	char *		_host_url;
	int			_stage;
	std::string _status_code;
public:
	explicit HTTPRequest(const char *buf);
	~HTTPRequest();
	void									parse_request_http(const char * buf);
	void									parseFirstLine(const std::string& line);
	void									parseHeaders(const std::string& header_line);
	void									checkValidHeaders();

	void								setRequestParams(std::map<std::string, std::string> request_params);

	const char *						getMethod(void) { return _method; };
	const char *						getPath(void) {return _path; };
	const char *						getVersionHTTP(void) { return _version_http; };
	const char *						getHostUrl(void) { return _host_url; };
	const std::string&					getStatusCode() { return _status_code; }
	std::map<std::string, std::string>	getHeaders() { return _request_params; }
	int									getParsingStage() { return _stage; }

	void								setMethod(char * method);
	void								setPath(char * path);
	void								setVersionHTTP(char * version_http);
	void								setHostUrl(char * host_url);
	void								setStatusCode(const std::string& status_code);
	void								setParsingStage(int stage) { _stage = stage; }

};