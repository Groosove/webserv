//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(): _stage(0) {
	_request = ft_strdup("");
	_body = ft_strdup("");
}

HTTPRequest::~HTTPRequest() {}

std::string HTTPRequest::getArgument(const std::string &dst, int start) {
	return ft_strtrim(dst.substr(start + 1, dst.length()), " \t");
}

char * HTTPRequest::getStr(char *&buf, size_t pos) {
	char *result = ft_substr(buf, 0, pos);
	char *tmp = ft_substr(buf, pos + 2, ft_strlen(buf));
	free(buf);
	buf = tmp;
	return result;
}

void HTTPRequest::takeHeader(char *header) {
	size_t pos = ft_strchr(header, ':');
	char *tmp = ft_substr(header, 0, pos);
	_request_params[tmp] = getArgument(header, pos);
	free(tmp);
	free(header);
}

void HTTPRequest::addBufferToRequest(char *buf) {
	char *tmp = ft_strjoin(_request, buf);
	free(_request);
	_request = tmp;
	free(buf);
}

void HTTPRequest::addBodyToRequest(char *buf) {
	char *tmp = ft_strjoin(_body, buf);
	free(_body);
	_body = tmp;
}

void HTTPRequest::parse_request_http(char * buf, int bytes) {
	std::cout << buf << std::endl;
	addBufferToRequest(buf);
	size_t  pos;
	while (_request && _stage != 3) {
		if (_stage == 0) {
			if ((pos = ft_find(_request, "\r\n")) != (size_t) -1)
				parseFirstLine(getStr(_request, pos));
			else break;
		}
		else if (_stage == 1) {
			if ((pos = ft_find(_request, "\r\n")) != (size_t)-1 && pos != 0)
				takeHeader(getStr(_request, pos));
			else if (pos == 0) { _request = ft_substr(_request, 2, ft_strlen(_request)); _stage = 2; }
			else {std::cerr << "Error parse request" << std::endl;}
		} else if (_stage == 2) {
			if (parseBodyRequest() == 1)
				_stage = 3;
			else break;
		}
	}
//	for (std::map<std::string, std::string>::iterator it = _request_params.begin(); it != _request_params.end(); ++it)
//		std::cout << "KEK:" << it->first << ":" << it->second << std::endl;
}

int HTTPRequest::parseBodyRequest() {
	if (_request_params.count("content-length")) {
		size_t size = ft_atoi(_request_params["content-length"].c_str());
		addBodyToRequest(_request);
		if (ft_strlen(_body) > size) {
			char *tmp = ft_substr(_body, 0, size);
			free(_body);
			_body = tmp;
		}
		return 1;
	} else if (_request_params.count("Transfer-Encoding")) {
		int size;
		size_t pos;
		while (_request) {
			if ((pos = ft_find(_request, "\r\n")) != (size_t)-1) {
				if (size == -1) {
					size = ft_atoi_chunk(getStr(_request, pos));
				} else if (size != 0) {
					char *tmp = (char *)malloc(sizeof(size) + 1);
					tmp[size] = '\0';
					addBodyToRequest(tmp);
					free(tmp);
					size = -1;
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

