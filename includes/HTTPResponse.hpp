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
	std::string		_buf_response;
	std::string		_body;

public:
	explicit HTTPResponse();
	~HTTPResponse();

	static const std::string		message_phrases[count_status_code][2];

	void							generateResponse(const std::string& status);

	static std::string				getMessagePhrase(const std::string& code);
	const std::string&				getStatusCode() const { return (_status_code); }
	const std::string&				getResponse() const { return _buf_response; }

	void							setStatusCode(const std::string& status) { _status_code = status; }
	void							setBody(const std::string& chunk_body) { _body.append(chunk_body); }

};