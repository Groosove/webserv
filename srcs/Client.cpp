//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "Client.hpp"

Client::Client(int client_socket, const std::string &host, const std::string &port): _socket(client_socket), _request(), _response(), _host(host), _port(port), _stage(0), _send_bytes(0) {
	_request = new HTTPRequest();
	_response = new HTTPResponse();
	_response_complite = ft_strdup("");
	_send_bytes = 0;
	std::cout << "Client is added" << std::endl;
}

Client::~Client() {
	delete _request;
	delete _response;
	free(_response_complite);
}

int Client::getBytes() const { return _bytes; }

size_t& Client::getSendBytes() {
	return _send_bytes;
}

void Client::setSendBytes(size_t sendBytes) {
	_send_bytes = sendBytes;
}

void Client::setResponseBuffer(char *buf, int bytes) {
	free(_response_complite);
	_response_complite = (char *)calloc(bytes, sizeof(char));
	ft_memcpy(_response_complite, buf, bytes);
	_bytes = bytes;
}
