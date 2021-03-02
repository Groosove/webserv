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
	int							_max_fd;


public:
	explicit WebServer(const char *config_name = "default.conf");
	~WebServer() {};
	void						handle();
	void						createVirtualServer();
	void						initSocketSet(fd_set& write_fd, fd_set& read_fd);
	void						addClientSocketToSet(fd_set& write_fd, fd_set& read_fd);
	void						treatmentAccept(fd_set& read_fd);
	void						searchSelectSocket(fd_set& write_fd, fd_set& read_fd);
	void						readRequest(Client*	client, fd_set& write_fd, fd_set& read_fd);
	void						deleteClient(std::vector<Client*>::iterator& client);
	void						handle_requests(Client* client, fd_set& read_fd, fd_set& write_fd) throw();
	void						treatmentStageGenerate(Client* client);
	std::string					checkValidRequest(Location* location, Client* client, struct stat* info);
	static void						checkDirectoryOrFile(struct stat* info, Location* location, std::string& path);
	void						handleDefaultResponse(Client* client, Location* location, struct stat* stat_info, std::string& path);
	void						handlePutResponse(Client* client, Location* location, struct stat* stat_info, std::string& path, int stat_info_created);
	void						handlePostReponse(Client* client, Location* location, struct stat* stat_info, std::string& path);
	bool						tryOpenDir(Location* location);
	bool						tryOpenFile(Location* location);
	std::pair<char *, int>		generateAutoindex(HTTPRequest* request, const std::string& path);
	std::vector<VirtualServer>	getVirtualServer();
	VirtualServer*				searchVirtualServer(Client* client);
	static std::pair<char *, int>		readBodyResponse(const std::string& path);
	void						parsing_request_part(Client *client, fd_set& read_fd, fd_set& write_fd);
	void						generate_response_part(Client *client, fd_set& read_fd, fd_set& write_fd);
	void						send_response_part(Client *client, fd_set& read_fd, fd_set& write_fd);
	int getMaxFd() const;
	void setMaxFd(int maxFd);
};
