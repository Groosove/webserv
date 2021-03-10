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

public:

	/* Constructors */
	explicit Client(int client_socket, const std::string& host, const std::string& port);

	/* Destructor */
	~Client();

	/* Getters */
	const std::string&		getHost() const { return _host; }
	const std::string&		getPort() const { return _port; }
	char *					getReponseBuffer() { return _response_complite; }
	size_t					getStage() const { return _stage; }
	int						getSocket() const { return _socket; }
	int 					getBytes() const;
	HTTPRequest*			getRequest() const { return _request; }
	HTTPResponse*			getResponse() const { return _response; }

	/* Setters */
	void					setStage(size_t stage) { _stage = stage; }
	void 					setResponseBuffer(char * buf, int bytes );

private:
	HTTPRequest*	_request;
	HTTPResponse*	_response;
	std::string		_host;
	std::string		_port;
	int				_socket;
	int				_stage;
	int				_bytes;
	size_t 			_send_bytes;
	char* 			_response_complite;
};
