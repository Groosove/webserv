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

std::string		HTTPResponse::getMessagePhrase(const std::string& code) {
	for (int i = 0; i < count_status_code; ++i) {
		if (HTTPResponse::message_phrases[i][0] == code)
			return (HTTPResponse::message_phrases[i][1]);
	}
	return ("Unknown code");
}

void	HTTPResponse::check_status_code(const std::string& errorPage) {
	int	pos = 0;
	pos = std::stoi(_status_code);
	if (pos >= 400)
		_body_size = errorPage.length();
}

void	HTTPResponse::addHeadersToResponse(HTTPRequest* request, std::string& headers) {
	if (request->getHeaders().find("Connection") == request->getHeaders().end())
		request->setHeaders("Connection", "keep-alive");
	std::map<std::string, std::string>::const_iterator it = request->getHeaders().find("Connection");
	headers.append(
			VERISON + SPACE + _status_code + SPACE + getMessagePhrase(_status_code) + CRLF
			+ "Server:" + SPACE + "RaevkaTuliskiyPryanikNogotochki" + CRLF
			+ it->first + ":" + SPACE + it->second + CRLF
			+ "Content-Length:" + SPACE + std::to_string(_body_size) + CRLF
			+ "Date:" + SPACE + ft_get_time() + CRLF);
}

void	HTTPResponse::addBodyToResponse(const std::string& errorPage) {
	int	pos = 0;
	pos = std::stoi(_status_code);
	if (pos < 400)
		_buf_response = (char *)ft_memjoin(_buf_response, _body, _header_size, _body_size);
	else {
		_buf_response = (char*)ft_memjoin(_buf_response, (char*)errorPage.c_str(), _header_size, _body_size);
	}
}

void	HTTPResponse::generateResponse(HTTPRequest* request, int flagErrorPage, std::string& path) {
	std::string headers;
	std::string	errorPage = generateErrorPage(flagErrorPage, path);

	check_status_code(errorPage);
	addHeadersToResponse(request, headers);
	if (ft_strlen(_headers_cgi))
		headers.append(std::string(_headers_cgi));
	else
		headers.append(CRLF);
	_buf_response = (char*)ft_memjoin(_buf_response, (char *)headers.c_str(), _header_size, headers.size());
	addBodyToResponse(errorPage);
}


HTTPResponse::HTTPResponse(): _headers_cgi(nullptr), _body_size(0) {
	_body = ft_strdup("");
	_buf_response = ft_strdup("");
	_headers_cgi = ft_strdup("");
	_header_size = 0;
}

void HTTPResponse::setBody(std::pair<char *, int> dst) {
	char *body = dst.first;
	int size = dst.second;
	_body = (char *)ft_memjoin(_body, body, _body_size, size);
	free(dst.first);
}

int HTTPResponse::getBodySize() const { return _header_size; }

std::string HTTPResponse::generateErrorPage(int flagErrorPage, const std::string& path) {
	std::string error;
	if (flagErrorPage == 1) {
		int fd = open(path.c_str(), O_RDONLY);
		char buf[100];
		bzero(buf, 100);
		int	pos = 0;

		while ((pos = read(fd, &buf, 100)) > 0)
			error.append(buf, pos);
		close(fd);
	}
	else {
		error.append(
				"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" "
				"content=\"width=device-width, initial-scale=1.0\"><meta http-equiv=\"X-UA-Compatible\" "
				"content=\"ie=edge\"><title>" + _status_code + " " +
				getMessagePhrase(_status_code) + "</title><style>h1, "
												 "p {text-align: center;}</style></head><body><h1>" +
				_status_code + " " + getMessagePhrase(_status_code) +
				"</h1><hr><p>RaevkaTuliskiyPryanikNogotochki</p></body></html>");
	}
	return error;
}

void HTTPResponse::clear() {
	free(_buf_response);
	_buf_response = ft_strdup("");
	_body_size = 0;
	_header_size = 0;
}
