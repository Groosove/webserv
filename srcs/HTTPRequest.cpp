//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(const std::string &buf) {
	_request_params = parse_request_http(buf);
}

HTTPRequest::~HTTPRequest() {}

std::map<std::string, std::string> HTTPRequest::parse_request_http(const std::string &buf) {
	std::istringstream is(buf);
	size_t  pos;
	std::string line;

	while (std::getline(is, line)) { // TODO: Сюда нужно вкинуть аргументы. Всё-таки нужно только с мапой её парсить, потому что заносить миллиард переменных - пиздец плохо
		if ((pos = line.find(':')) != std::string::npos) {
			_request_params[std::string(line, 0, pos)] = std::string(line, pos + 2, std::string::npos);
			if (ft_compare(std::string(line, 0, pos), "Host"))
				setHostUrl(std::string(line, pos + 2, std::string::npos));
			else if (ft_compare(std::string(line, 0, pos), "Host"))
				setMethod(std::string(line, pos + 2, std::string::npos));
			else if (ft_compare(std::string(line, 0, pos), "Host"))
				setPath(std::string(line, pos + 2, std::string::npos));
			else if (ft_compare(std::string(line, 0, pos), "Host"))
				setVersionHTTP(std::string(line, pos + 2, std::string::npos));
		}
	}
	return _request_params;
}

void HTTPRequest::setHostUrl(const std::string &host_url) {
	_host_url = host_url;
}

void HTTPRequest::setMethod(const std::string &method) {
	_method = method;
}

void HTTPRequest::setPath(const std::string &path) {
	_path = path;
}

void HTTPRequest::setVersionHTTP(const std::string &version_http) {
	_version_http = version_http;
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