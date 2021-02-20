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
private:
	std::string							_host;
	std::string							_port;
	std::string							_server_name;
	std::vector<std::string>			_error_page;
	std::map<std::string, Location>		_location;
	std::map<std::string, std::string> 	_parametr;
	int									_socket;
	struct sockaddr_in 					_server_addr;
	std::string							_complete_response;

	HTTPRequest*						_request;
	HTTPResponse*						_response;
public:
	VirtualServer() {};
	~VirtualServer() {};

	void							initSocket(void);
	void							preparationParams(void);
	const char*						treatmentRequest(char* buf);
	void							generateResponse(const char* method);
	void						addBodyToResponse(const Location& location);

	void							setHost(const std::string& host);
	void							setPort(const std::string& port);
	void							setServerName(const std::string& server_name);
	void							setErrorPage(const std::string& error_page);
	void							setSocket(int socket);

	std::map<std::string, Location>& getLocation() { return _location; }
	HTTPRequest*					getRequest() { return _request; }
	inline const std::string& 		getHost() const	{ return _host; }
	inline const std::string& 		getPort() const	{ return _port; }
	inline const std::string& 		getServerName() const { return _server_name; }
	inline int 						getSocket() const { return _socket; }
};