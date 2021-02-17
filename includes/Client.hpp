//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include "Client.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

class Client {
private:
	int				_socket;
	HTTPRequest*	_request;
	HTTPResponse*	_response;
	std::string		_host;
	std::string		_port;

public:
	explicit Client(int client_socket, const std::string& host, const std::string& port);
	~Client();

	const std::string&		getHost() const { return _host; }
	const std::string&		getPort() const { return _port; }
	int						getSocket() { return _socket; }

	void					setHost(const std::string& host) { _host = host; }
	void					setPort(const std::string& port) { _port = port; }
	void					setSocket(int&	socket) { _socket = socket; }
};