//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//


#include "HTTPResponse.hpp"
#include <fcntl.h>

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
	size_t		pos = 0;
	int size = 0;
	std::string headers;
	headers.append(VERISON + SPACE + _status_code + SPACE + getMessagePhrase(_status_code) + CRLF
						+ "Server:" + SPACE + "WebServ/1.1" + CRLF
						+ "Connection:" + SPACE + "close" + CRLF + CRLF);
	_buf_response = (char *)ft_memjoin(_buf_response, (char *)headers.c_str(), _header_size, headers.size());
	if ((pos = _status_code.find("4")) == std::string::npos || (pos = _status_code.find("5")) == std::string::npos)
		_buf_response = (char *)ft_memjoin(_buf_response, _body, _header_size, _body_size);
	else {
		_buf_response = (char*)ft_memjoin(_buf_response, (char*)generateErrorPage().c_str(), _header_size, generateErrorPage().size());
	}
}

HTTPResponse::HTTPResponse(): _body_size(0) {
	_body = ft_strdup("");
	_buf_response = ft_strdup("");
	_header_size = 0;
}

void HTTPResponse::setBody(std::pair<char *, int> dst) {
	char *body = dst.first;
	int size = dst.second;
	_body = (char *)ft_memjoin(_body, body, _body_size,size);
}

int HTTPResponse::getBodySize() const { return _header_size; }

std::string HTTPResponse::generateErrorPage() {
	return ("<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" "
			"content=\"width=device-width, initial-scale=1.0\"><meta http-equiv=\"X-UA-Compatible\" "
			"content=\"ie=edge\"><title>" + _status_code + " " + getMessagePhrase(_status_code) + "</title><style>h1, "
																								"p {text-align: center;}</style></head><body><h1>" + _status_code + " " + getMessagePhrase(_status_code) +
			"</h1><hr><p>WebServ/0.1</p></body></html>");
}
