//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once
#include "Location.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "fstream"
#include "utils.hpp"

// Инклюды для инициализации сокета и работы с ним и структурой socket_addr
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

class VirtualServer {
public:
	/* Constructor */
	VirtualServer() {};

	/* Destructor */
	~VirtualServer() {};

	/* Handlers */
	void										initSocket(void);
	void										preparationParams(void);
	std::map<std::string, Location>::iterator	findLocation(HTTPRequest* request);


	/* Setters */
	void										setHost(const std::string& host);
	void										setPort(const std::string& port);
	void										setServerName(const std::string& server_name);
	void										setErrorPage(const std::string& error_page);
	void										setSocket(int socket);

	/* Getters */
	std::map<std::string, Location>&			getLocation() { return _location; }
	inline const std::string& 					getHost() const	{ return _host; }
	inline const std::string& 					getPort() const	{ return _port; }
	inline const std::string& 					getServerName() const { return _server_name; }
	inline int 									getSocket() const { return _socket; }
	HTTPRequest*								getRequest() { return _request; }

private:
	std::map<std::string, std::string> 	_parametr;
	std::map<std::string, Location>		_location;
	std::vector<std::string>			_error_page;
	struct sockaddr_in 					_server_addr;
	HTTPRequest*						_request;
	std::string							_host;
	std::string							_port;
	std::string							_server_name;
	int									_socket;
};