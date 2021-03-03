//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "HTTPRequest.hpp"
#include "fcntl.h"

HTTPRequest::HTTPRequest(): _stage(false), _body_size(0), _hex_size(-1) {
	_request = ft_strdup("");
	_request_size = 0;
	_body = ft_strdup("");
}

HTTPRequest::~HTTPRequest() {}

std::string HTTPRequest::getArgument(const std::string &dst, int start) {
	return ft_strtrim(dst.substr(start + 1, dst.length()), " \t");
}

char * HTTPRequest::getStr(size_t pos) {
	char *result = ft_substr(_request, 0, pos);
	_request = ft_substr(_request, pos + 2, _request_size);
	_request_size -= pos + 2;
	return result;
}

void HTTPRequest::takeHeader(char *header) {
	size_t pos = ft_strchr(header, ':');
	if (pos == (size_t)-1) throw std::string ("400");
	char *tmp = ft_substr(header, 0, pos);
	_request_params[tmp] = getArgument(header, pos);
	free(tmp);
	free(header);
}


void HTTPRequest::parse_request_http(char * buf, int bytes) {
	std::cout << buf << std::endl;
	char *tmp = (char *)ft_memjoin(_request, buf, _request_size, bytes);
	free(_request);
	_request = tmp;
	size_t pos;
	while (_request && _stage != 3) {
		if (_stage == 0) {
			if ((pos = ft_find(_request, "\r\n")) != (size_t) -1)
				parseFirstLine(getStr(pos));
			else break;
		}
		else if (_stage == 1) {
			if ((pos = ft_find(_request, "\r\n")) != (size_t)-1 && pos != 0)
				takeHeader(getStr(pos));
			else if (pos == 0) {
				_request = ft_substr(_request, 2, ft_strlen(_request));
				_request_size -=2;
				if (_request_params.count("Host") == 0)
					throw std::string ("400");
				if (ft_compare(_method, "PUT") || ft_compare(_method, "POST")) {
					if (_request_params.count("Content-Length") == 0 && _request_params.count("Transfer-Encoding") == 0)
						throw std::string ("400");
					else {
						_stage = 2;
						continue;
					}
				}
				_stage = 3;
			}
			else break;
		} else if (_stage == 2) {
			if (parseBodyRequest() == 1)
				_stage = 3;
			else
				break;
		}
	}
}

int HTTPRequest::parseBodyRequest() {
	if (_request_params.count("Content-Length")) {
		size_t size = ft_atoi(_request_params["Content-Length"].c_str());
		_body = (char *) ft_memjoin(_body, _request, _body_size, size);
		if (ft_strlen(_body) > size) {
			char *tmp = ft_substr(_body, 0, size);
			free(_body);
			_body = tmp;
		}
		return 1;
	} else if (_request_params.count("Transfer-Encoding")) {
		size_t pos;
		while (_request) {
			if ((pos = ft_find(_request, "\r\n")) != (size_t)-1) {
				if (_hex_size == (size_t)-1) {
					_hex_size = ft_atoi_chunk(getStr(pos));
				} else if (_hex_size != 0) {
					_body = (char *)ft_memjoin(_body, getStr(pos), _body_size, _hex_size);
					_hex_size = -1;
				} else return 1;
			} else return 0;
		}
	}
	return 0;
}

void HTTPRequest::parseFirstLine(char *line) {
	char ** dst = ft_split(line, ' ');
	for (int i = 0; dst[i] != nullptr; ++i) {
		if (i == 0) {
			if (ft_compare(dst[i], "GET") || ft_compare(dst[i], "POST") || ft_compare(dst[i], "PUT") || ft_compare(dst[i], "HEAD"))
				setMethod(dst[i]);
			else throw std::string("400");
		}
		else if (i == 1)
			setPath(dst[i]);
		else {
			if (ft_compare(dst[i], "HTTP/1.1") || ft_compare(dst[i], "HTTP/1.0"))
				setVersionHTTP(dst[i]);
			else std::cerr << "Error set version HTTP/1.1" << std::endl;
		}
	}
	free(line);
	++_stage;
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
char *HTTPRequest::getRequest() const {
	return _request;
}

int HTTPRequest::getRequsetSize() const { return _request_size; }

int HTTPRequest::getBodySize() const {
	return _body_size;
}
