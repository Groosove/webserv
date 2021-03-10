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
#include "CGI.hpp"
#include "sys/socket.h"
#include "sys/select.h"

class WebServer {
public:
	/* Constructor */
	explicit WebServer(const char *config_name = "default.conf");

	/* Destructor */
	~WebServer() {};

	/* Getters */
	const int&						getMaxFd() const { return _max_fd; };

	/* Setters */
	void							setMaxFd(int maxFd) { _max_fd = maxFd; };

	/* Handlers */
	void							handleDefaultResponse(Client* client, Location* location, struct stat* stat_info, std::string& path);
	void							handlePutResponse(Client* client, Location* location, struct stat* stat_info, std::string& path, int stat_info_created);
	void							handle();

	/*	Response part */
	void							parsing_request_part(Client *client, fd_set& read_fd, fd_set& write_fd);
	void							send_response_part(Client *client, fd_set& read_fd, fd_set& write_fd);
	void							treatmentStageGenerate(Client* client);

	/* Validation */
	std::string						checkValidRequest(Location* location, Client* client, struct stat* info);
	static void						checkDirectoryOrFile(struct stat* info, Location* location, std::string& path);
	VirtualServer*					searchVirtualServer(Client* client);

	/* Generators */
	std::pair<char *, int>			generateAutoindex(HTTPRequest* request, const std::string& path);
	static std::pair<char *, int>	readBodyResponse(const std::string& path);
	void							createVirtualServer();

private:
	std::vector<Client*>			_clients;
	std::vector<VirtualServer>		_virtual_server;
	bool							_status;
	int								_max_fd;
};
