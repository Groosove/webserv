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

WebServer::WebServer(const char *config_name): _status(true), _max_fd(0) {
	std::vector<std::string> config;
	int fd = open(config_name, O_RDONLY);
	char *line = nullptr;
	if (fd > 0) {
		while (get_next_line(fd, &line) > 0) {
			config.push_back(line);
			free(line);
		}
		config.push_back(line);
		free(line);
	}

	else
		throw std::string ("File doesn't open!");
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

void WebServer::handle() {
	fd_set	write_fd;
	fd_set	read_fd;
	struct	timeval	tv;

	tv.tv_usec = 0;
	std::cout << GREEN << "Waiting connection... " << TEXT_RESET << std::endl;
	while(_status) {
		tv.tv_sec = 240;
		FD_ZERO(&read_fd);
		FD_ZERO(&write_fd);
		for (size_t i = 0; i < _virtual_server.size(); ++i)
			FD_SET(_virtual_server[i].getSocket(), &read_fd);
		setMaxFd(_virtual_server.back().getSocket());
		for (size_t i = 0; i != _clients.size(); ++i) {
			FD_SET(_clients[i]->getSocket(), &read_fd);
			if (_clients[i]->getStage() != parsing_request)
				FD_SET(_clients[i]->getSocket(), &write_fd);
			if (_clients[i]->getSocket() > getMaxFd())
				setMaxFd(_clients[i]->getSocket());
		}
		select(getMaxFd() + 1, &read_fd, &write_fd, 0, &tv);
		for (size_t i = 0; i < _virtual_server.size(); ++i)
			if (FD_ISSET(_virtual_server[i].getSocket(), &read_fd)) {
				int client_fd = accept(_virtual_server[i].getSocket(), 0, 0);
				if (client_fd > 0)
					_clients.push_back(new Client(client_fd, _virtual_server[i].getHost(), _virtual_server[i].getPort()));
			}
		std::vector<Client*>::iterator it = _clients.begin();
		while (it != _clients.end())
		{
			if (FD_ISSET((*it)->getSocket(), &read_fd) && (*it)->getStage() == parsing_request)
				parsing_request_part(*it, read_fd, write_fd);
			if (FD_ISSET((*it)->getSocket(), &write_fd) && (*it)->getStage() == generate_response)
				treatmentStageGenerate(*it);
			if (FD_ISSET((*it)->getSocket(), &write_fd) && (*it)->getStage() == send_response)
				send_response_part(*it, read_fd, write_fd);
			if ((*it)->getStage() == close_connection) {
				delete *it;
				it = _clients.erase(it);
			} else
				++it;
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

void WebServer::parsing_request_part(Client *client, fd_set& read_fd, fd_set& write_fd) {
	char*			buf = (char*)calloc(80000, 1);
	int				read_bytes;
	int				size_buffer = 80000;

	read_bytes = recv(client->getSocket(), buf, size_buffer, 0);
	try {
		if (read_bytes > 0) {
			buf[read_bytes] = 0;
			client->getRequest()->parse_request_http(buf, read_bytes);
			if (client->getRequest()->getParsingStage() == 3)
				client->setStage(generate_response);
		}
		else if (read_bytes <= 0) {
			client->setStage(close_connection);
			free(buf);
		}
	}
	catch (const std::string& status_value) {
		std::string path = EMPTY;
		client->getResponse()->setStatusCode(status_value);
		client->getResponse()->generateResponse(client->getRequest(), client->getFlagErrorPage(), path);
		client->setResponseBuffer(client->getResponse()->getResponse(), client->getResponse()->getBodySize());
		client->setStage(send_response);
	}
}

void WebServer::send_response_part(Client *client, fd_set &read_fd, fd_set &write_fd) {
	int	ret = 0;
	int	bytes_send = 0;
	int	all_bytes = client->getBytes();

	while (all_bytes > 0) {
		ret = send(client->getSocket(), client->getReponseBuffer() + bytes_send, all_bytes, 0);
		if (ret == -1) {
			if (bytes_send != 0)
				continue;
			else {
				client->setStage(close_connection);
				return;
			}
		}
		bytes_send += ret;
		all_bytes -= ret;
	}
	output_iteration(client);
	client->getResponse()->clear();
	client->getRequest()->clear();
	if (ft_compare(client->getRequest()->getHeaders().find("Connection")->second.c_str(), "close"))
		client->setStage(close_connection);
	else
		client->setStage(parsing_request);
}

void	WebServer::output_iteration(Client *client) {
	static int i = 1, post = 1;
	std::cerr << YELLOW << "sent response for request #" << i++ << " ( method " << client->getRequest()->getMethod()
			  << " )" << TEXT_RESET;
	if (ft_compare(client->getRequest()->getMethod(), "POST"))
		std::cerr << RED << " #" << post++ << TEXT_RESET;
	std::cerr << std::endl;
}
