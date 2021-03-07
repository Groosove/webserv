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
#define GREEN  "\033[1;32m"

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
	close(fd);
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
		FD_ZERO(&read_fd);
		FD_ZERO(&write_fd);
		for (size_t i = 0; i < _virtual_server.size(); ++i)
			FD_SET(_virtual_server[i].getSocket(), &read_fd);
		setMaxFd(_virtual_server.back().getSocket());
		for (size_t i = 0; i != _clients.size(); ++i)
		{
			FD_SET(_clients[i]->getSocket(), &read_fd);
			if (_clients[i]->getStage() != parsing_request)
				FD_SET(_clients[i]->getSocket(), &write_fd);
			if (_clients[i]->getSocket() > getMaxFd())
				setMaxFd(_clients[i]->getSocket());
		}
		select(getMaxFd() + 1, &read_fd, &write_fd, 0, &tv);
		for (size_t i = 0; i < _virtual_server.size(); ++i)
		{
			int	client_fd = 0;
			if (FD_ISSET(_virtual_server[i].getSocket(), &read_fd))
			{
				client_fd = accept(_virtual_server[i].getSocket(), 0, 0);
				if (client_fd > 0)
					_clients.push_back(new Client(client_fd, _virtual_server[i].getHost(), _virtual_server[i].getPort()));

			}
		}
		std::vector<Client*>::iterator it = _clients.begin();
		while (it != _clients.end())
		{
			if (FD_ISSET((*it)->getSocket(), &read_fd))
				handle_requests(*it, read_fd, write_fd);
			else if (FD_ISSET((*it)->getSocket(), &write_fd) && (*it)->getStage() != parsing_request)
				handle_requests(*it, read_fd, write_fd);
			if ((*it)->getStage() == close_connection)
			{
				close((*it)->getSocket());
				delete *it;
				it = _clients.erase(it);
				if (it == _clients.end())
					break;
			}
			else
				++it;
			if (_clients.empty())
				break;
		}
	}
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

	read_bytes = recv(client->getSocket(), buf, size_buffer, 0);
	buf[read_bytes] = 0;
	try {
		if (read_bytes > 0) {
			client->getRequest()->parse_request_http(buf, read_bytes);
			if (client->getRequest()->getParsingStage() == 3)
				client->setStage(generate_response);
		}
		else if (read_bytes <= 0) {
			client->getResponse()->clear();
			client->getRequest()->clear();
			client->setStage(close_connection);
		}
	}
	catch (const std::string& status_value) {
		client->getResponse()->setStatusCode(status_value);
		client->getResponse()->generateResponse(client->getRequest());
		client->setResponseBuffer(client->getResponse()->getResponse(), client->getResponse()->getBodySize());
		client->setStage(send_response);
	}
}

void WebServer::send_response_part(Client *client, fd_set &read_fd, fd_set &write_fd) {
	size_t	ret = 0;
	size_t	bytes_send = 0;
	size_t	all_bytes = client->getBytes();
	while (all_bytes > 0) {
		ret = send(client->getSocket(), client->getReponseBuffer() + bytes_send, all_bytes, 0);
		if (ret == -1) {
			if (errno != EPIPE && bytes_send != 0)
				continue;
			client->getResponse()->clear();
			client->getRequest()->clear();
			client->setStage(close_connection);
		}
		bytes_send += ret;
		all_bytes -= ret;
	}
	client->setStage(parsing_request);
	client->getResponse()->clear();
	client->getRequest()->clear();
	static int i = 1;
	std::cerr << RED << "sent response for request #" << i++ << TEXT_RESET << std::endl;
	std::cerr << RED << "FD: " << client->getSocket() << std::endl;
}

int WebServer::getMaxFd() const {
	return _max_fd;
}

void WebServer::setMaxFd(int maxFd) {
	_max_fd = maxFd;
}
