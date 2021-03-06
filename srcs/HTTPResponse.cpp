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

void	HTTPResponse::generateResponse(HTTPRequest* request) {
	std::map<std::string, std::string>::const_iterator it;
	size_t		pos = 0;
	int size = 0;
	std::string headers;
	std::string	errorPage = generateErrorPage();

	if (_buf_response)
		free(_buf_response);
	std::cout << "SIZE: " << _body_size << std::endl;
	std::cout << "STATUS CODE: " << _status_code << std::endl;
	pos = std::stoi(_status_code);
	if (pos >= 400)
		_body_size = errorPage.length();
	headers.append(VERISON + SPACE + _status_code + SPACE + getMessagePhrase(_status_code) + CRLF
				+ "Server:" + SPACE + "WebServ/1.1" + CRLF
				+ "Connection:" + SPACE + "keep-alive" + CRLF
				+ "Content-Length:" + SPACE + std::to_string(_body_size) + CRLF);
	if (_headers_cgi)
		headers.append(std::string(_headers_cgi) + CRLF);
	headers.append(CRLF);
	_buf_response = (char *)ft_memjoin(_buf_response, (char *)headers.c_str(), _header_size, headers.size());
	pos = std::stoi(_status_code);
	if (pos < 400)
		_buf_response = (char *)ft_memjoin(_buf_response, _body, _header_size, _body_size);
	else {
		_buf_response = (char*)ft_memjoin(_buf_response, (char*)errorPage.c_str(), _header_size, _body_size);
	}
	std::cout << "BODY RESPONSE: " << _buf_response << std::endl;
	std::cout << "SIZE RESPONSE: " << _body_size << std::endl;
}

HTTPResponse::HTTPResponse(): _body_size(0), _headers_cgi(nullptr) {
	_body = ft_strdup("");
	_buf_response = ft_strdup("");
	_headers_cgi = ft_strdup("");
	_header_size = 0;
}

void HTTPResponse::setBody(std::pair<char *, int> dst) {
	char *body = dst.first;
	int size = dst.second;
	_body = (char *)ft_memjoin(_body, body, _body_size, size);
}

int HTTPResponse::getBodySize() const { return _header_size; }

std::string HTTPResponse::generateErrorPage() {
	return ("<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" "
			"content=\"width=device-width, initial-scale=1.0\"><meta http-equiv=\"X-UA-Compatible\" "
			"content=\"ie=edge\"><title>" + _status_code + " " + getMessagePhrase(_status_code) + "</title><style>h1, "
																								"p {text-align: center;}</style></head><body><h1>" + _status_code + " " + getMessagePhrase(_status_code) +
			"</h1><hr><p>WebServ/0.1</p></body></html>");
}

char *HTTPResponse::getBody() const {
	return _body;
}
