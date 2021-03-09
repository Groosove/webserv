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
	char* 			_response_complite;
	int				_bytes;
	size_t 			_send_bytes;

public:

	explicit Client(int client_socket, const std::string& host, const std::string& port);
	~Client();

	const std::string&		getHost() const { return _host; }
	const std::string&		getPort() const { return _port; }
	int						getSocket() const { return _socket; }
	HTTPRequest*			getRequest() const { return _request; }
	HTTPResponse*			getResponse() const { return _response; }
	size_t					getStage() const { return _stage; }
	char *					getReponseBuffer() { return _response_complite; }

	size_t& getSendBytes();

	void setSendBytes(size_t sendBytes);

	int getBytes() const;

	void					setStage(size_t stage) { _stage = stage; }
	void 					setResponseBuffer(char * buf, int bytes );
};