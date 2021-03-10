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
	_body = ft_strdup("");
	_request = ft_strdup("");

	_method = ft_strdup("");
	_version_http = ft_strdup("");
	_http_query = ft_strdup("");
	_http_path = ft_strdup("");

	_request_size = 0;
	_request_capacity = 0;
	_body_capacity = 0;
}

HTTPRequest::~HTTPRequest() {
	free(_request);
	free(_body);
	free(_version_http);
	free(_http_query);
	free(_http_path);
	free(_method);
}

char *HTTPRequest::getArgument(char *dst, int start) {
	char *tmp = ft_substr(dst, start, ft_strlen(dst));
	char *result = ft_strtrim(tmp, " \t");
	free(tmp);
	return result;
}

char * HTTPRequest::getStr(size_t pos) {
	char *result = ft_substr(_request, 0, pos);
	ft_erase(_request, pos + 2, _request_size);
	return result;
}

void HTTPRequest::takeHeader(char *header) {
	size_t pos = ft_strchr(header, ':');
	if (pos == (size_t)-1)
		throw std::string("400");

	char *tmp = ft_substr(header, 0, pos - 1);
	char *value = getArgument(header, pos);
	_request_params[tmp] = value;
	free(value);
	free(tmp);
	free(header);
}

void HTTPRequest::parse_request_http(char * buf, int bytes) {
	if (bytes == 0)
		throw std::string ("400");
	ft_add(_request, buf, bytes, _request_size, _request_capacity);
	free(buf);
	size_t pos;
	while (_request_size != 0 && _stage != 3) {
		if (_stage == 0 && (pos = ft_find(_request, "\r\n")) != (size_t) -1)
			parseFirstLine(getStr(pos));
		else if (_stage== 1 && (pos = ft_find(_request, "\r\n")) != (size_t)-1 && pos != 0)
			takeHeader(getStr(pos));
		else if (_stage == 1 && pos == 0)
				checkHeaders();
		else if (_stage == 2 && parseBodyRequest())
				_stage = 3;
		else break;
	}
}

int HTTPRequest::parseBodyRequest() {
	if (_request_params.count("Content-Length")) {
		size_t size = ft_atoi(_request_params["Content-Length"].c_str());
		ft_add(_body, _request, size, _body_size, _body_capacity);
		if (_body_size > size)
			ft_erase(_body, _body_size - size, _body_size);
		return 1;
	} else if (_request_params.count("Transfer-Encoding")) {
		size_t pos;
		while (_request)
			if ((pos = ft_find(_request, "\r\n")) != (size_t)-1) {
				if (_hex_size == (size_t)-1)
					_hex_size = ft_atoi_chunk(getStr(pos));
				else if (_hex_size != 0) {
					ft_add(_body, _request, _hex_size, _body_size, _body_capacity);
					ft_erase(_request, pos + 2, _request_size);
					_hex_size = -1;
				} else return 1;
			} else return 0;
	}
	return 0;
}

void HTTPRequest::parseFirstLine(char *line) {
	char ** dst = ft_split(line, ' ');
	int i = 0;
	for (; dst[i] != nullptr; ++i)
		if (i == 0 && (ft_compare(dst[i], "GET") || ft_compare(dst[i], "POST") || ft_compare(dst[i], "PUT") || ft_compare(dst[i], "HEAD")))
				setMethod(dst[i]);
		else if (i == 1)
			setPath(dst[i]);
		else if (i == 2 && (ft_compare(dst[i], "HTTP/1.1") || ft_compare(dst[i], "HTTP/1.0")))
				setVersionHTTP(dst[i]);
		else break;

	free(line);
	if (i != 3)  {
		for (int j = 0; dst[j]; ++j)
			free(dst[j]);
		free(dst);
		throw std::string("400");
	}
	free(dst);
	++_stage;
}

void HTTPRequest::ft_erase(char *& dst, int size, size_t& dst_size) {
	dst_size -= size;
	ft_memcpy(dst, dst + size, dst_size);
	dst[dst_size] = '\0';
}

void HTTPRequest::ft_add(char *&dst, char *buf, int buf_size, size_t& dst_size, size_t& dst_capacity) {
	if (dst_size + buf_size >= dst_capacity) {
		dst_capacity = (dst_size + buf_size) * 2;
		char *_realloc_body = dst;
		dst = (char *)malloc(dst_capacity);
		ft_memcpy(dst, _realloc_body, dst_size);
		free(_realloc_body);
	}
	for (int i = 0; i < buf_size; ++i, ++dst_size)
		dst[dst_size] = buf[i];
	dst[dst_size] = '\0';
}


void HTTPRequest::clear() {
	free(_method);
	free(_version_http);
	free(_http_path);
	free(_http_query);
	free(_request);
	free(_body);
	_request = ft_strdup("");
	_body = ft_strdup("");
	_method = ft_strdup("");
	_version_http = ft_strdup("");
	_http_query = ft_strdup("");
	_http_path = ft_strdup("");
	_request_size = 0;
	_request_capacity = 0;
	_body_capacity = 0;
	_stage = false;
	_body_size = 0;
	_hex_size = -1;
	_status_code.clear();
}

void HTTPRequest::setMethod(char *method) {
	free(_method);
	_method = ft_strdup(method);
	free(method);
}

void HTTPRequest::setPath(char * path) {
	free(_http_path);
	free(_http_query);
	size_t pos = ft_strchr(path, '?');
	if (pos == (size_t)-1) {
		_http_path = ft_strdup(path);
		_http_query = ft_strdup("");
	} else {
		_http_path = ft_substr(path, 0, pos - 1);
		_http_query = ft_substr(path, pos + 2, ft_strlen(path));
	}
	free(path);
}

void HTTPRequest::setVersionHTTP(char *version_http) {
	free(_version_http);
	_version_http = ft_strdup(version_http);
	free(version_http);
}

const char *HTTPRequest::getContentType() const {
	std::map<std::string, std::string>::const_iterator it = _request_params.find("Content-Type");
	if (it != _request_params.end())
		return it->second.c_str();
	return nullptr;
}

void HTTPRequest::checkHeaders() {
	ft_erase(_request, 2, _request_size);
	if (_request_params.count("Host") == 0)
		throw std::string ("400");
	if (ft_compare(_method, "PUT") || ft_compare(_method, "POST"))
		if (_request_params.count("Content-Length") == 0 && _request_params.count("Transfer-Encoding") == 0)
			throw std::string ("400");
		else
			_stage = 2;
	else
		_stage = 3;
}
