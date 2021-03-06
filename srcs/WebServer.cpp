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
#define RED "\033[1;31m"
#define TEXT_RESET "\033[0;0m"
size_t			countttt = 0;

WebServer::WebServer(const char *config_name): _status(true), _max_fd(0) {
	std::vector<std::string> config;
	int fd = open(config_name, O_RDONLY);
	char *line = nullptr;
	if (fd > 0)
		while (get_next_line(fd, &line) > 0) {
			config.push_back(line);
			free(line);
		}
	else
		std::cerr << "File doesn't open!" << std::endl;
	free(line);
	FileParser _config(config);
	_virtual_server = _config.getServer();
}

void WebServer::createVirtualServer() {
	for (size_t i = 0; i < _virtual_server.size(); ++i) {
		_virtual_server[i].initSocket();
		_virtual_server[i].preparationParams();
	}
	handle();
}

std::vector<VirtualServer> WebServer::getVirtualServer() {
	return std::vector<VirtualServer>(_virtual_server);
}

void WebServer::handle() {
	fd_set	write_fd;
	fd_set	read_fd;
	struct	timeval	tv;

	tv.tv_usec = 0;
	while(_status) {
		tv.tv_sec = 240;
		initSocketSet(write_fd, read_fd);
		addClientSocketToSet(write_fd, read_fd);
		select(getMaxFd() + 1, &read_fd, &write_fd, 0, &tv);
		treatmentAccept(read_fd);
		searchSelectSocket(write_fd, read_fd);
	}
}

void WebServer::initSocketSet(fd_set& write_fd, fd_set& read_fd) {
	FD_ZERO(&write_fd);
	FD_ZERO(&read_fd);

	for (size_t i = 0; i < _virtual_server.size(); ++i)
		FD_SET(_virtual_server[i].getSocket(), &read_fd);
	setMaxFd(_virtual_server.back().getSocket());
}

void WebServer::addClientSocketToSet(fd_set &write_fd, fd_set &read_fd) {
	for (size_t i = 0; i < _clients.size(); ++i) {
		if (_clients[i]->getStage() == parsing_request)
			FD_SET(_clients[i]->getSocket(), &read_fd);
		if(_clients[i]->getStage() != parsing_request)
			FD_SET(_clients[i]->getSocket(), &write_fd);
		if (_clients[i]->getSocket() > getMaxFd())
			setMaxFd(_clients[i]->getSocket());
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
	char*							chunk = nullptr;

	for (it = _clients.begin(); it != _clients.end(); ++it) {
		if (FD_ISSET((*it)->getSocket(), &read_fd))
			handle_requests(*it, read_fd, write_fd);
		if (FD_ISSET((*it)->getSocket(), &write_fd) && ((*it)->getStage() == generate_response || (*it)->getStage() == send_response))
			handle_requests(*it, read_fd, write_fd);
		if ((*it)->getStage() == close_connection) {
			deleteClient(it);
			break;
		}
		if (_clients.empty())
			break ;
	}
}

void WebServer::deleteClient(std::vector<Client*>::iterator& client) {
	close((*client)->getSocket());
	delete *client;
	_clients.erase(client);
}

VirtualServer *WebServer::searchVirtualServer(Client *client) {
	for (size_t i = 0; i < _virtual_server.size(); ++i) {
		if (client->getHost() == _virtual_server[i].getHost() && client->getPort() == _virtual_server[i].getPort()) // TODO добавить сравнение сервер неймов
			return &_virtual_server[i];
	}
	return nullptr;
}

void WebServer::handle_requests(Client *client, fd_set& read_fd, fd_set& write_fd) throw(){
	if (client->getStage() == parsing_request) {
		parsing_request_part(client, read_fd, write_fd);
	}
	else if (client->getStage() == generate_response) {
		treatmentStageGenerate(client);
	}
	else if (client->getStage() == send_response)
		send_response_part(client, read_fd, write_fd);
}

void WebServer::parsing_request_part(Client *client, fd_set& read_fd, fd_set& write_fd) {
	char*			buf = (char*)calloc(80000, 1);
	int				read_bytes;
	int				size_buffer = 80000;

	std::cout << RED << "REBYATKI, MOI NUMBER: " << countttt << " FD: " << client->getSocket() << TEXT_RESET << std::endl;
	countttt++;
	read_bytes = recv(client->getSocket(), buf, size_buffer, 0);
	buf[read_bytes] = 0;
	try {
		if (read_bytes > 0) {
			client->getRequest()->parse_request_http(buf, read_bytes);
			if (client->getRequest()->getParsingStage() == 3)
				client->setStage(generate_response);
		}
		else if (read_bytes == 0)
			client->setStage(close_connection);
	}
	catch (const std::string& status_value) {
		client->getResponse()->setStatusCode(status_value);
		client->getResponse()->generateResponse(client->getRequest());
		client->setResponseBuffer(client->getResponse()->getResponse(), client->getResponse()->getBodySize());
		client->setStage(send_response);
	}
}

void WebServer::send_response_part(Client *client, fd_set &read_fd, fd_set &write_fd) {
	if (client->getBytes() != client->getSendBytes()) {
		size_t ret;
		if (FD_ISSET(client->getSocket(), &write_fd)) {
			ret = send(client->getSocket(), client->getReponseBuffer() + client->getSendBytes(),
					   client->getBytes() - client->getSendBytes(), 0);
			if (errno != EPIPE) {
				client->setSendBytes(client->getSendBytes() + ret);
				if (client->getBytes() == client->getSendBytes()) {
					client->setStage(close_connection);
				}
				else
					return;
			}
			errno = 0;
		}
	}
	FD_CLR(client->getSocket(), &read_fd);
	FD_CLR(client->getSocket(), &write_fd);
	client->setStage(close_connection);
}

int WebServer::getMaxFd() const {
	return _max_fd;
}

void WebServer::setMaxFd(int maxFd) {
	_max_fd = maxFd;
}
