//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "WebServer.hpp"

void WebServer::parseConfigFile(std::ifstream &config_name) {
	std::string buf;
	while (std::getline(config_name, buf)) {
		if (buf.find("server", 0) != std::string::npos)
			_virtual_server.push_back(VirtualServer(config_name));
	}
}

WebServer::WebServer(const char *config_name) {
	std::ifstream file_config(config_name);
	if (file_config.is_open())
		parseConfigFile(file_config);
	else
		std::cerr << "File doesn't open!" << std::endl;
}

void WebServer::createVirtualServer() {
	for (size_t i = 0; i < _virtual_server.size(); ++i) {
//		check_valid_virtual_server(); // TODO написать валидацию серверов, для того чтобы не запускать рандомный сервер, напишем потом!
		_virtual_server[i].initSocket();
		_virtual_server[i].preparationParams();
		handle(_virtual_server[i]);
	}
}

std::vector<VirtualServer> WebServer::getVirtualServer() {
	return std::vector<VirtualServer>(_virtual_server);
}

void WebServer::handle(VirtualServer &virtualServer) { // TODO разнести тело цикла по методам _virtual_server и накидать класс CLIENT;
	int 	max_fd;
	int 	ret;
	fd_set 	read_fd, write_fd, cp_read_fd, cp_write_fd;
	int client;
	sockaddr_in client_addr;
	socklen_t addr_len;
	char *buff;

	max_fd = virtualServer.getSocket();
	FD_ZERO(&read_fd);
	FD_ZERO(&write_fd);
	FD_SET(virtualServer.getSocket(), &read_fd);
	FD_SET(virtualServer.getSocket(), &write_fd);
	std::cout << "++++++Waiting new Connect++++++" << std::endl;
	while (_status) {
		cp_read_fd = read_fd;
		cp_write_fd = write_fd;
		if (select(max_fd + 1, &cp_read_fd, &cp_write_fd, nullptr, (struct timeval*)nullptr) <= 0)
			continue;
		if (FD_ISSET(virtualServer.getSocket(), &cp_read_fd)) {
			if ((client = accept(virtualServer.getSocket(), (struct sockaddr *) &client_addr, &addr_len)) > 0) {
				FD_SET(client, &read_fd);
				FD_SET(client, &write_fd);
				if (client > max_fd)
					max_fd = client;
				std::cout << "++++++New user id added!++++++" << std::endl;
			}
		}
		for (size_t i = 0; i <= max_fd; ++i) {
			if (FD_ISSET(i, &cp_read_fd)) {
				ret = recv(i, buff, 4097, 0);
				if (ret == 0) {
					std::cout << "++++++USER DISCONNECT!++++++" << std::endl;
					FD_CLR(i, &read_fd);
					FD_CLR(i, &write_fd);
//					close(i);
					break;
				}
			}
		}
		for (size_t i = 0; i <= max_fd; ++i) {
			if (FD_ISSET(i, &cp_write_fd)) {
				send(i, "Server", 6, 0);
				send(i, buff, strlen(buff), 0);

			}
		}
		bzero(buff, 4097);
	}
}
