//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "WebServer.hpp"

#include <cstdlib>
#include <unistd.h>
#include <cstring>

WebServer::WebServer(const char *config_name): _status(true) {
	std::vector<std::string> config;
	int fd = open(config_name, O_RDONLY);
	char *line = nullptr;
	if (fd > 0)
		while (get_next_line(fd, &line) > 0)
			config.push_back(line);
	else
		std::cerr << "File doesn't open!" << std::endl;
	FileParser _config(config);
	_virtual_server = _config.getServer();
}

void WebServer::createVirtualServer() {
	for (size_t i = 0; i < _virtual_server.size(); ++i) {
//		check_valid_virtual_server(); // TODO написать валидацию серверов, для того чтобы не запускать рандомный сервер, напишем потом!
		_virtual_server[i].initSocket();
		_virtual_server[i].preparationParams();
	}
	handle();
}

std::vector<VirtualServer> WebServer::getVirtualServer() {
	return std::vector<VirtualServer>(_virtual_server);
}

void WebServer::handle() { // TODO разнести тело цикла по методам _virtual_server и накидать класс CLIENT;
	fd_set	write_fd;
	fd_set	read_fd;
	int		max_fd;
	int		select_value;
	struct	timeval	tv;

	tv.tv_usec = 0;
	while(_status) {
		tv.tv_sec = 240;
		initSocketSet(write_fd, read_fd, max_fd);
		addClientSocketToSet(write_fd, read_fd, max_fd);
		select_value = select(max_fd, &read_fd, &write_fd, 0, &tv);
		if (select_value < 1) {
			if (errno != EINTR)
				std::cout << "Select error" << std::endl;
			else
				std::cout << "Treatment request" << std::endl;
			continue;
		}
		if (select_value == 0) {
			std::cout << "Time out" << std::endl;
			continue;
		}
		treatmentAccept(read_fd);
		searchSelectSocket(write_fd, read_fd);
	}
}

void WebServer::initSocketSet(fd_set& write_fd, fd_set& read_fd, int& max_fd) {
	FD_ZERO(&write_fd);
	FD_ZERO(&read_fd);

	for (size_t i = 0; i < _virtual_server.size(); ++i)
		FD_SET(_virtual_server[i].getSocket(), &read_fd);
	max_fd = _virtual_server.back().getSocket();
}

void WebServer::addClientSocketToSet(fd_set &write_fd, fd_set &read_fd, int &max_fd) {
	for (size_t i = 0; i < _clients.size(); ++i) {
		if (_clients[i]->getStatus() == 1)
			FD_SET(_clients[i]->getSocket(), &read_fd);
		if (_clients[i]->getStatus() != 1)
			FD_SET(_clients[i]->getSocket(), &write_fd);
		if (_clients[i]->getSocket() > max_fd)
			max_fd = _clients[i]->getSocket();
	}
}

void WebServer::treatmentAccept(fd_set &read_fd) {
	int	client_socket;
	for (size_t i = 0; i < _virtual_server.size(); ++i) {
		if (FD_ISSET(_virtual_server[i].getSocket(), &read_fd)) {
			if ((client_socket = accept(_virtual_server[i].getSocket(), 0, 0)) > 0)
				_clients.push_back(new Client(client_socket, _virtual_server[i].getHost(), _virtual_server[i].getPort()));
		}
	}
}

void WebServer::searchSelectSocket(fd_set &write_fd, fd_set &read_fd) {
	std::vector<Client*>::iterator	it;
	char*							buff;
	size_t							ret = 0;

	for (it = _clients.begin(); it < _clients.end(); ++it) {
		if (FD_ISSET((*it)->getSocket(), &read_fd))
			readRequest();
	}
}

void WebServer::readRequest() {
	HTTPRequest*	request = _clients->getRequest();
	char*			buf;

}

