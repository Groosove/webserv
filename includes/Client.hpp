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

enum Stage {
	parsing_request,
	generate_response,
	send_response,
	close_connection,
};

class Client {
private:
	int				_socket;
	HTTPRequest*	_request;
	HTTPResponse*	_response;
	std::string		_host;
	std::string		_port;
	int				_stage;
	char*			_read_buffer;
	char*			_write_buffer;

public:
	explicit Client(int client_socket, const std::string& host, const std::string& port);
	~Client();

	const std::string&		getHost() const { return _host; }
	const std::string&		getPort() const { return _port; }
	int						getSocket() const { return _socket; }
	HTTPRequest*			getRequest() const { return _request; }
	HTTPResponse*			getResponse() const { return _response; }
	size_t					getStage() const { return _stage; }
	char*					getReadBuffer() { return _read_buffer; }
	char*					getWriteBuffer() { return _write_buffer; }

	void					setHost(const std::string& host) { _host = host; }
	void					setPort(const std::string& port) { _port = port; }
	void					setSocket(int&	socket) { _socket = socket; }
	void					setReadBuffer(char* buf) { _read_buffer = buf; }
	void					setWriteBuffer(char* buf) { _write_buffer = buf; }
	void					setStage(size_t stage) { _stage = stage; }
};