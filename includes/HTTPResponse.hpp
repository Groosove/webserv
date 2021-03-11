//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include "HTTPRequest.hpp"
#include "utils.hpp"
#include <iostream>
#include <iterator>

#define VERISON (std::string)"HTTP/1.1"
#define SPACE	" "
#define CRLF	"\r\n"

enum { count_status_code = 13, };

class HTTPResponse {

public:
	/* Constructor */
	explicit HTTPResponse();

	/* Destructor */
	~HTTPResponse() { free(_buf_response); free(_body); free(_headers_cgi); };

	/* Static massive */
	static const std::string		message_phrases[count_status_code][2];

	/* Getters */
	static std::string				getMessagePhrase(const std::string& code);
	std::string						generateErrorPage(int flagErrorPage, const std::string& path);
	std::string						getStatusCode() { return _status_code; }
	char *							getResponse() const { return _buf_response; }
	int 							getBodySize() const;

	/* Setters */
	void							setStatusCode(const std::string& status) { _status_code = status; }
	void							setBody(std::pair<char *, int> buf);
	void							setCgiHeaders(char* headers) { free(_headers_cgi); _headers_cgi = ft_strdup(headers);  }

	/* Checkers */
	void							check_status_code(const std::string& errorPage);


	/* Modifiers */
	void							addBodyToResponse(const std::string& errorPage);
	void							addHeadersToResponse(HTTPRequest* request, std::string& headers);
	void							generateResponse(HTTPRequest* request, int flagErrorPage, std::string& path);
	void							clear();

private:
	std::string 	_status_code;
	char *			_buf_response;
	char *			_body;
	char *			_headers_cgi;
	size_t 			_body_size;
	size_t 			_header_size;
};