//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(const char * buf) {
	_request_params = parse_request_http(buf);
}

HTTPRequest::~HTTPRequest() {}

std::map<std::string, std::string> HTTPRequest::parse_request_http(const char * buf) {
	char **request = ft_split(buf, '\n');
	std::map<std::string, std::string> result;
	size_t  pos;
	for (size_t i = 0; request[i] != nullptr; ++i) {
		if (ft_strchr(request[i], ':') == -1 && request[i + 1] != nullptr)
			parseFirstLine((request[i]));
		else if ((pos = ft_strchr(request[i], ':')) != (size_t) -1) {
			if (ft_compare(request[i], "Host", 4))
				setHostUrl(ft_substr(request[i], pos + 2, ft_strlen(request[i]) - 1));
			else
				result[ft_substr(request[i], 0, pos)] = ft_substr(request[i], pos + 2,
																  ft_strlen(request[i]) - 1);
		}
	}
	return result;
}

void HTTPRequest::parseFirstLine(const char *line) {
	char ** dst = ft_split(line, ' ');
	for (int i = 0; dst[i] != nullptr; ++i) {
		if (i == 0)
			setMethod(dst[i]);
		else if (i == 1)
			setPath(dst[i]);
		else
			setVersionHTTP(dst[i]);
	}
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

