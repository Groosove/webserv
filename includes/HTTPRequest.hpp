//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include <map>
#include <vector>
#include "utils.hpp"

class HTTPRequest {

public:
	explicit HTTPRequest();
	~HTTPRequest();

	void								parse_request_http(char * buf, int bytes);

	/* Getters */
	std::map<std::string, std::string>&	getHeaders() { return _request_params; }
	const char *						getMethod() const { return _method; };
	const char *						getPath() const {return _http_path; }
	const char *						getHttpQuery() const { return _http_query; }
	const char *						getVersionHTTP() const { return _version_http; };
	const char *						getContentType() const;
	const char*							getBody() { return _body; }
	int 								getBodySize() const { return _body_size; };
	int									getParsingStage() const { return _stage; }

	/* Setters */
	void								setMethod(char * method);
	void								setPath(char * path);
	void								setVersionHTTP(char * version_http);

	/* Modifiers */
	void								clear();

private:
	std::map<std::string, std::string>	_request_params;
	char *		_body;
	char *		_request;

	char *		_method;
	char *		_http_path;
	char *		_http_query;
	char *		_version_http;

	size_t 		_request_capacity;
	size_t 		_request_size;
	size_t 		_body_size;
	size_t		_body_capacity;
	size_t		_hex_size;

	int			_stage;
	std::string _status_code;

	char *			getArgument(char *dst, int start);
	char *			getStr(size_t pos);
	void			parseFirstLine(char * line);
	void			takeHeader(char *header);
	int				parseBodyRequest();
	void			checkHeaders();
	void			ft_add(char *& dst, char *buf, int buf_size, size_t& dst_size, size_t& dst_capacity);
	void			ft_erase(char *& dst, int size, size_t& dst_size);
};
