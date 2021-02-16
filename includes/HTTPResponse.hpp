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
	HTTPRequest*	_request_status;

public:
	explicit HTTPResponse(const char* method);
	~HTTPResponse();

	static const std::string	message_phrases[count_status_code][2];

	void			generateResponse();

	static std::string				getMessagePhrase(const std::string& code);
	inline const std::string&		getStatusCode() const { return (_status_code); }
	const std::string&				getResponse() const { return _buf_response; }


	char*			getBuf() const;

};