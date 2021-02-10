//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(char *buf) {
	_request_params = parse_request_http(buf);
}

HTTPRequest::~HTTPRequest() {}

std::map<std::string, std::string> HTTPRequest::parse_request_http(char *buf) {
	char **request = ft_split(buf, '\n');
	size_t  pos;
	size_t	index = 0;
	std::string line;
	while (request[index] != nullptr) {
		if (ft_strchr(request[index], ':') == -1)
			parseFirstLine(line);
		else if ((pos = ft_strchr(request[index], ':')) != (size_t)-1) {
			if (ft_compare(request[index], "Host", 4)) {
				std::cout << "LOL:" << request[index] << std::endl;
//  				setHostUrl(a);
				std::cout << "BOOM" << std::endl;
			}
			else {
				std::cout << "DO" << std::endl;
//				_request_params[std::string(line, 0, pos)] = std::string(line, pos + 2, std::string::npos);
			}
		}
		index++;
	}
	std::cout << "KEK: " << _method << std::endl;
	std::cout << "KEK: " << _path << std::endl;
	std::cout << "KEK: " << _version_http << std::endl;
	return _request_params;
}

void HTTPRequest::parseFirstLine(const std::string& line) {
	std::vector<std::string>			vect = ft_parse_spaces(line);
	size_t 								count = 0;
	std::vector<std::string>::iterator	it_begin = vect.begin();
	std::vector<std::string>::iterator	it_end = vect.end();

	for (; it_begin != it_end; ++it_begin, ++count) {
		if (count == 0) {
			setMethod(*it_begin);
		}
		else if (count == 1) {
			setPath(*it_begin);
		}
		else
			setVersionHTTP(*it_begin);
	}
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

