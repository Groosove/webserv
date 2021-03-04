//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include "HTTPRequest.hpp"
#include "HTTPRequest.hpp"
#include <iostream>
#include <iterator>

enum { count_status_code = 13, };

class HTTPResponse {
private:
	std::string 	_status_code;
	char *			_buf_response;
	char *			_body;
	int				_body_size;
	int				_header_size;

public:
	explicit HTTPResponse();
	~HTTPResponse();

	static const std::string		message_phrases[count_status_code][2];

	void							generateResponse(HTTPRequest* requestz);

	static std::string				getMessagePhrase(const std::string& code);
	const std::string&				getStatusCode() const { return (_status_code); }
	char *							getResponse() const { return _buf_response; }
	std::string						generateErrorPage();

	int getBodySize() const;

	char *getBody() const;

	void							setStatusCode(const std::string& status) { _status_code = status; }
	void							setBody(std::pair<char *, int> buf);

};