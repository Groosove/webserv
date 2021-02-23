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
	void						treatmentStageGenerate(Client* client);
	std::string					checkValidRequest(Location* location, Client* client, struct stat* info);
	void						checkDirectoryOrFile(struct stat* info, Location* location);
	void						handleDefaultResponse(Client* client, Location* location, struct stat* stat_info);
	void						handlePutResponse(Client* client, Location* location, struct stat* stat_info);
	bool						tryOpenDir(Location* location);
	bool						tryOpenFile(Location* location);
	std::string					generateAutoindex(HTTPRequest* request, const std::string& index, const std::string& root_dir);
	std::vector<VirtualServer>	getVirtualServer();
	VirtualServer*				searchVirtualServer(Client* client);
	std::string					readBodyResponse(const std::string& root, const std::string& file);
};