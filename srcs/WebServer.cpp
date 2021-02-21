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

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;
	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if (i > 3 && (*buf)[i] == '\n' && (*buf)[i - 1] == '\r' && (*buf)[i - 2] == '\n' && (*buf)[i - 3] == '\r')
		{
			newbuf = (char *)calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char    *newbuf;
	int        len;
	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = (char*)malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

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
		select_value = select(max_fd + 1, &read_fd, &write_fd, 0, &tv);
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
		if (_clients[i]->getStage() == parsing_request)
			FD_SET(_clients[i]->getSocket(), &read_fd);
		if(_clients[i]->getStage() != parsing_request)
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
	char*							chunk = nullptr;

	for (it = _clients.begin(); it < _clients.end(); ++it) {
		if (FD_ISSET((*it)->getSocket(), &read_fd) || FD_ISSET((*it)->getSocket(), &write_fd))
			handle_requests(*it, read_fd, write_fd);
		else if ((*it)->getStage() == close_connection && !(FD_ISSET((*it)->getSocket(), &read_fd) || FD_ISSET((*it)->getSocket(), &write_fd)))
			deleteClient(it);
		if (_clients.empty())
			break ;
	}
}

void WebServer::deleteClient(std::vector<Client*>::iterator& client) {
	delete *client;
	_clients.erase(client);
	client = _clients.begin();
}

void WebServer::handle_requests(Client *client, fd_set& read_fd, fd_set& write_fd) {
	HTTPRequest*	request = client->getRequest();
	char*			buf = (char*)calloc(4097, 1);
	int				read_bytes;
	int				size_buffer = 4097;
	char*			chunk = nullptr;

	if (client->getStage() == parsing_request) {
		read_bytes = recv(client->getSocket(), buf, size_buffer, 0);
		buf[read_bytes] = 0;
		try {
			if (read_bytes > 0) {
				client->getRequest()->parse_request_http(buf);
				if (client->getRequest()->getParsingStage() == 3)
					client->setStage(generate_response);
			}
			else if (read_bytes == 0)
				client->setStage(close_connection);
		}
		catch (const std::string& status_value) {
			VirtualServer*	virtual_server = searchVirtualServer(client);
			Location*		location = virtual_server->findLocation(client->getRequest());

			client->getResponse()->setStatusCode(client->getRequest()->getStatusCode());
			client->getResponse()->generateResponse();

		}
	}
	else if (client->getStage() == generate_response) {

	}
	else if (client->getStage() == send_response) {

	}
}

VirtualServer *WebServer::searchVirtualServer(Client *client) {
	HTTPRequest* request = client->getRequest();

	for (size_t i = 0; i < _virtual_server.size(); ++i) {
		if (client->getHost() == _virtual_server[i].getHost() && client->getPort() == _virtual_server[i].getPort()
			&& std::string(request->getHostUrl()) == _virtual_server[i].getServerName())
			return &_virtual_server[i];
	}
	return nullptr;
}