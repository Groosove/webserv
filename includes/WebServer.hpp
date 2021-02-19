//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include "FileParser.hpp"
#include "VirtualServer.hpp"
#include "Client.hpp"
#include "sys/socket.h"
#include "sys/select.h"

class WebServer {
private:
	std::vector<Client*>		_clients;
	std::vector<VirtualServer>	_virtual_server;
	bool						_status;

	void		parseConfigFile(std::ifstream& file);
public:
	explicit WebServer(const char *config_name = "default.conf");
	~WebServer() {};
	void						handle();
	void						createVirtualServer();
	void						initSocketSet(fd_set& write_fd, fd_set& read_fd, int& max_fd);
	void						addClientSocketToSet(fd_set& write_fd, fd_set& read_fd, int& max_fd);
	void						treatmentAccept(fd_set& read_fd);
	void						searchSelectSocket(fd_set& write_fd, fd_set& read_fd);
	void						readRequest(Client*	client, fd_set& write_fd, fd_set& read_fd);
	void						deleteClient(std::vector<Client*>::iterator& client);
	void						handle_requests(Client* client, fd_set& read_fd, fd_set& write_fd);
	std::vector<VirtualServer>	getVirtualServer();
};