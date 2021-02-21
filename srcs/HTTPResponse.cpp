//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//


#include "HTTPResponse.hpp"

const std::string	HTTPResponse::message_phrases[count_status_code][2] = {
		{"200", "OK"},
		{"201", "Created"},
		{"301", "Moved Permanently"},
		{"302", "Found"},
		{"400", "Bad Request"},
		{"401", "Unauthorized"},
		{"403", "Forbidden"},
		{"404", "Not Found"},
		{"405", "Method Not Allowed"},
		{"411", "Length Required"},
		{"413", "Payload Too Large"},
		{"500", "Internal server error"},
		{"501", "Not Implemented"}
};

#define VERISON (std::string)"HTTP/1.1"
#define SPACE	" "
#define CRLF	"\r\n"

std::string		HTTPResponse::getMessagePhrase(const std::string& code) {
	for (int i = 0; i < count_status_code; ++i) {
		if (HTTPResponse::message_phrases[i][0] == code)
			return (HTTPResponse::message_phrases[i][1]);
	}
	return ("Unknown code");
}

void	HTTPResponse::generateResponse() {
	std::map<std::string, std::string>::const_iterator it;

	_buf_response.append(VERISON + SPACE + _status_code + SPACE + getMessagePhrase(_status_code) + CRLF
						+ "Server:" + SPACE + "WebServ/1.1" + CRLF
						+ "Connection:" + SPACE + "keep-alive" + CRLF + CRLF);

//	for (it = _request_status->getHeaders().begin(); it != _request_status->getHeaders().end(); ++it)
//		_buf_response.append(it->first + ":" + SPACE + it->second + CRLF);
}

HTTPResponse::HTTPResponse() {
//	_status_code = _request_status->getStatusCode();
	_status_code.append("200");
	generateResponse();

}
