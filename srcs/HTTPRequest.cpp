//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(char * buf): _stage(0) {
	_request_params = parse_request_http(buf);
}

HTTPRequest::~HTTPRequest() {}

std::string HTTPRequest::getArgument(const std::string &dst, int start) { return ft_strtrim(dst.substr(start + 1, dst.length()), " \t"); }

char * HTTPRequest::getData(char *&buf, size_t pos) {
	char *result = ft_substr(buf, 0, pos);
	buf = ft_substr(buf, pos + 2, ft_strlen(buf));
	return result;
}

void HTTPRequest::takeHeader(char *header, std::map<std::string, std::string> &arg) {
	size_t pos = ft_strchr(header, ':');
	arg[ft_substr(header, 0, pos)] = getArgument(header, pos);
}

std::map<std::string, std::string> HTTPRequest::parse_request_http(char * buf) {
	std::cout << buf << std::endl;
	std::map<std::string, std::string> result;
	size_t  pos;
	while (buf && _stage != 3) {
		if (_stage == 0 && (pos = ft_find(buf, "\r\n")) != (size_t)-1) {
			parseFirstLine(getData(buf, pos), _stage);
			std::cout << "Method: " << getMethod() << std::endl;
			std::cout << "Path:" << getPath() << std::endl;
			std::cout << "HTTP:" << getVersionHTTP() << std::endl;
		}
		else if (_stage == 1) {
			if ((pos = ft_find(buf, "\r\n")) != (size_t)-1 && pos != 0)
				takeHeader(getData(buf, pos), result);
			else if (pos == 0) { buf = ft_substr(buf, 2, ft_strlen(buf)); _stage = 2; }
			else {std::cerr << "Error parse request" << std::endl;}
		} else if (_stage == 2) {
			if (result.count("content-length")) {
				size_t size = ft_atoi(result["content-length"].c_str());
				_body = ft_strdup(buf);
				if (ft_strlen(_body) > size)
					_body = ft_substr(_body, 0, size);
				std::cout << "Body: " << _body << std::endl;
			} else {
				while (buf) {
					break;
				}
			}
			_stage = 3;
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

void HTTPRequest::setStatusCode(const std::string &status_code) {
	_status_code = status_code;
}

