//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include "HTTPRequest.hpp"
#include "VirtualServer.hpp"
#include "sys/socket.h"
#include "sys/select.h"
class WebServer {
private:
	std::vector<VirtualServer>	_virtual_server;
	bool						_status;

	void		parseConfigFile(std::ifstream& file);
public:
	explicit WebServer(const char *config_name = "default.conf");
	~WebServer() {};
	void						handle(VirtualServer& virtualServer);
	void						createVirtualServer();
	std::vector<VirtualServer>	getVirtualServer();
};