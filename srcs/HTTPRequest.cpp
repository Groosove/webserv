//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(const std::string &buf) {
	_request_params = parse_request_http(buf); // TODO написать парсер для запроса с переменными, мапа будет как запасной вариант
}

HTTPRequest::~HTTPRequest() {}

std::map<std::string, std::string> HTTPRequest::parse_request_http(const std::string &buf) {
	std::istringstream is(buf);
	size_t  pos = 0;
	std::string line;

	while (std::getline(is, line)) {
		if ((pos = line.find(':')) != std::string::npos)
			_request_params[std::string(line, 0, pos)] = std::string(line, pos + 2, std::string::npos);
		pos = 0;
	}
	return _request_params;
}

void HTTPRequest::setRequestParams(std::map<std::string, std::string> request_params) {
	_request_params = request_params;
}

const std::string & HTTPRequest::getHostUrl() {
	return _host_url;
}

const std::string & HTTPRequest::getPath() {
	return _path;
}

const std::string & HTTPRequest::getMethod() {
	return _method;
}

const std::string & HTTPRequest::getVersionHTTP() {
	return _version_http;
}