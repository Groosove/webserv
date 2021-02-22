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
	char *		_body;


	char *_request;

	int			_stage;
	std::string _status_code;
public:
	explicit HTTPRequest();
	~HTTPRequest();
	void		parse_request_http(char * buf);
	void		parseFirstLine(char * line);

	static char *	getStr(char *&buf, size_t pos);
	void			takeHeader(char *header);
	void			addBufferToRequest(char *buf);
	void			addBodyToRequest(char *buf);
	int				parseBodyRequest();

	const char *						getMethod(void) { return _method; };
	const char *						getPath(void) {return _path; };
	const char *						getVersionHTTP(void) { return _version_http; };
	const char *						getHostUrl(void) { return _host_url; };
	const std::string&					getStatusCode() { return _status_code; }
	int									getParsingStage() const { return _stage; }
	std::map<std::string, std::string>	getHeaders() { return _request_params; }
	static std::string getArgument(const std::string &dst, int start);

	void								setMethod(char * method);
	void								setPath(char * path);
	void								setVersionHTTP(char * version_http);
	void								setHostUrl(char * host_url);
	void								setStatusCode(const std::string& status_code);

};
