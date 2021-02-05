//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once
#include "Location.hpp"
#include "fstream"
#include "utils.hpp"

class VirtualServer {
private:
	std::string						_host;
	std::string						_port;
	std::string						_server_name;
	std::vector<std::string>		_error_page;
	std::map<std::string, Location>	_location;
	std::map<std::string, std::string> _parametr;
	int								_socket;

	void							_parseServerParam(const std::string& buf);
public:
	explicit VirtualServer(std::ifstream &file);
	~VirtualServer() {};

	void	setHost(const std::string& host);
	void	setPort(const std::string& port);
	void	setServerName(const std::string& server_name);
	void	setSocket(int socket);

	inline const std::string& 	getHost() const	{ return _host; }
	inline const std::string& 	getPort() const	{ return _port; }
	inline const std::string& 	getServerName() const { return _server_name; }
	inline int 					getSocket() const { return _socket; }
};