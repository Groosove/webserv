//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(char * buf): _stage(0) {
	parse_request_http(buf);
}

HTTPRequest::~HTTPRequest() {}

std::string HTTPRequest::getArgument(const std::string &dst, int start) { return ft_strtrim(dst.substr(start + 1, dst.length()), " \t"); }

char * HTTPRequest::getStr(char *&buf, size_t pos) {
	char *result = ft_substr(buf, 0, pos);
	buf = ft_substr(buf, pos + 2, ft_strlen(buf));
	return result;
}

void HTTPRequest::takeHeader(char *header) {
	size_t pos = ft_strchr(header, ':');
	_request_params[ft_substr(header, 0, pos)] = getArgument(header, pos);
}

void HTTPRequest::addBufferToRequest(char *buf) { _request = ft_strjoin(_request, buf); }

void HTTPRequest::parse_request_http(char * buf) {
	addBufferToRequest(buf);
	std::cout << buf << std::endl;
	size_t  pos;
	while (buf && _stage != 3) {
		if (_stage == 0) {
			if ((pos = ft_find(buf, "\r\n")) != (size_t) -1) {
				parseFirstLine(getStr(buf, pos), _stage);
				std::cout << "Method: " << getMethod() << std::endl;
				std::cout << "Path:" << getPath() << std::endl;
				std::cout << "HTTP:" << getVersionHTTP() << std::endl;
			} else break;
		}
		else if (_stage == 1) {
			if ((pos = ft_find(buf, "\r\n")) != (size_t)-1 && pos != 0)
				takeHeader(getStr(buf, pos));
			else if (pos == 0) { buf = ft_substr(buf, 2, ft_strlen(buf)); _stage = 2; }
			else {std::cerr << "Error parse request" << std::endl;}
		} else if (_stage == 2) {
			if (_request_params.count("content-length")) {
				size_t size = ft_atoi(_request_params["content-length"].c_str());
				_body = ft_strdup(buf);
				if (ft_strlen(_body) > size)
					_body = ft_substr(_body, 0, size);
				std::cout << "Body: " << _body << std::endl;
			} else if (_request_params.count("Transfer-Encoding")) {
				size_t size = -1;
				while (buf) {

				}
			}
			_stage = 3;
		}
	}
	for (std::map<std::string, std::string>::iterator it = _request_params.begin(); it != _request_params.end(); ++it)
		std::cout << "KEK:" << it->first << ":" << it->second << std::endl;
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

