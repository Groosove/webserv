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

	char *	_body;
	char *	_request;
	int		_request_size;
	int		_body_size;
	size_t	_hex_size;

	int			_stage;
	std::string _status_code;
public:

	explicit HTTPRequest();
	~HTTPRequest();
	void		parse_request_http(char * buf, int bytes);
	void		parseFirstLine(char * line);

	char *	getStr(size_t pos);
	void	takeHeader(char *header);
	int		parseBodyRequest();

	const char *						getMethod() const { return _method; };
	const char *						getPath() const {return _path; }

	int getBodySize() const;;
	const char *						getVersionHTTP() const { return _version_http; };
	const char *						getHostUrl() const { return _request_params.find("Host")->second.c_str(); };
	const char *						getContentLength() const { return _request_params.find("Content-Length")->second.c_str(); }
	const char *						getContentType() const { return _request_params.find("Content-Type")->second.c_str(); }
	const std::string&					getStatusCode() const { return _status_code; }
	int									getParsingStage() const { return _stage; }
	int 								getRequestSize() const { return _request_size; }
	std::map<std::string, std::string>	getHeaders() { return _request_params; }
	const char*							getBody() { return _body; }

	int getRequsetSize() const;

	char *getRequest() const;

	char *getArgument(char *dst, int start);
	void								setMethod(char * method);
	void								setPath(char * path);
	void								setVersionHTTP(char * version_http);
	void								setStatusCode(const std::string& status_code);

};
