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

#define RED "\033[1;31m"
#define TEXT_RESET "\033[0;0m"
#define GREEN "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"
#define EMPTY std::string("")

class WebServer {
public:
	/* Constructor */
	explicit WebServer(const char *config_name = "configs/default.conf");

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
	void							parsing_request_part(Client *client);
	void							send_response_part(Client *client);
	void							treatmentStageGenerate(Client* client);

	/* Validation */
	std::string						checkValidRequest(Location* location, Client* client);
	static void						checkDirectoryOrFile(struct stat* info, Location* location, std::string& path);
	VirtualServer*					searchVirtualServer(Client* client);

	/* Generators */
	std::pair<char *, int>			generateAutoindex(const std::string& path);
	static std::pair<char *, int>	readBodyResponse(const std::string& path);
	void							createVirtualServer();

	/* Output */
	static void							output_iteration(Client* client);

private:
	std::vector<Client*>			_clients;
	std::vector<VirtualServer>		_virtual_server;
	bool							_status;
	int								_max_fd;
};
