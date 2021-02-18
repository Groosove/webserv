//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(const char * buf): _stage(0) {
	_request_params = parse_request_http(buf);
}

HTTPRequest::~HTTPRequest() {}

std::string HTTPRequest::getArgument(const std::string &dst, int start) { return ft_strtrim(dst.substr(start + 1, dst.length()), " \t"); }

std::map<std::string, std::string> HTTPRequest::parse_request_http(const char * buf) {
	std::cout << buf << std::endl;
	char **request = ft_split(buf, '\n');
	std::map<std::string, std::string> result;
	size_t  pos;
	for (size_t i = 0; request[i] != nullptr; ++i) {
		if (_stage == 0)
			parseFirstLine((request[i]), _stage);
		else if (_stage == 1) {
			if ((pos = ft_strchr(request[i], ':')) != (size_t) -1)
				result[ft_substr(request[i], 0, pos)] = getArgument(request[i], pos);
			else if (ft_compare(request[i], "\r")) _stage = 2;
			else {std::cerr << "Error parse request" << std::endl;}
		} else if (_stage == 2) {
			std::cout << "Parse body in requset" << std::endl;
			break;
		}
	}
	for (std::map<std::string, std::string>::iterator it = result.begin(); it != result.end(); ++it)
		std::cout << "KEK:" << it->first << ":" << it->second << std::endl;
	return result;
}

void HTTPRequest::parseFirstLine(const char *line, int &stage) {
	char ** dst = ft_split(line, ' ');
	for (int i = 0; dst[i] != nullptr; ++i) {
		if (i == 0)
			setMethod(dst[i]);
		else if (i == 1)
			setPath(dst[i]);
		else
			setVersionHTTP(dst[i]);
	}
	++stage;
}

void HTTPRequest::setHostUrl(char *host_url) {
	_host_url = host_url;
}

void HTTPRequest::setMethod(char *method) {
	_method = method;
}

void HTTPRequest::setPath(char * path) {
	_path = path;
}

void HTTPRequest::setVersionHTTP(char *version_http) {
	_version_http = version_http;
}

void HTTPRequest::setRequestParams(std::map<std::string, std::string> request_params) {
	_request_params = request_params;
}

void HTTPRequest::setStatusCode(const std::string &status_code) {
	_status_code = status_code;
}

