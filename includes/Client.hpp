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

#define RED "\033[1;31m"
#define TEXT_RESET "\033[0;0m"
#define GREEN "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define UNDERLINE "\033[0;4m"

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
	int						getFlagErrorPage() const { return _flagErrorPage; }

	/* Setters */
	void					setStage(size_t stage) { _stage = stage; }
	void 					setResponseBuffer(char * buf, int bytes );
	void					setFlagErrorPage(int flag) { _flagErrorPage = flag; }

private:
	HTTPRequest*	_request;
	HTTPResponse*	_response;
	std::string		_host;
	std::string		_port;
	int				_socket;
	int				_stage;
	int				_bytes;
	int				_flagErrorPage;
	char* 			_response_complite;
};
