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

int extract_message(char *&buf, char *&msg)
{
	char	*newbuf;
	int	i;
	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while (buf[i])
	{
		if (i > 3 && buf[i] == '\n' && buf[i - 1] == '\r' && buf[i - 2] == '\n' && buf[i - 3] == '\r')
		{
			newbuf = (char *)calloc(1, sizeof(*newbuf) * (strlen(buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, buf + i + 1);
			*msg = *buf;
			msg[i + 1] = 0;
			buf = newbuf;
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
		if (_clients[i]->getStage() == 1)
			FD_SET(_clients[i]->getSocket(), &read_fd);
		if (_clients[i]->getStage() != 1)
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
			readRequest(*it, write_fd, read_fd);
		if (FD_ISSET((*it)->getSocket(), &write_fd))
			nullptr;
	}
}

void WebServer::readRequest(Client* client, fd_set& write_fd, fd_set& read_fd) {
	HTTPRequest*	request = client->getRequest();
	char*			buf;
	int				read_bytes;
	int				size_buffer = 4096;
	char*			chunk = nullptr;
	read_bytes = recv(client->getSocket(), buf, size_buffer, 0);
	buf[read_bytes] = 0;
	if (read_bytes == 0)
	{
		close(client->getSocket());
		if(client->getReadBuffer())
			free((void *) client->getReadBuffer());
		if(client->getWriteBuffer())
			free((void *) client->getWriteBuffer());
		FD_CLR(client->getSocket(), &read_fd);
		FD_CLR(client->getSocket(), &write_fd);
	}
	else if (read_bytes > 0)
	{
		client->setReadBuffer(str_join((char*)client->getReadBuffer(), buf));
		//тут ты пиздуешь в обработку или сначала смотришь есть ли тут \r\n
		char *tmp = client->getReadBuffer();
		while (extract_message(tmp, chunk))
		{
			client->setWriteBuffer((char*)"HTTP/1.1 200 OK\r\nServer: lol\r\nConnection: keep-alive\r\n\r\n");
			std::cout << chunk << " 1 " << std::endl;
			free(chunk);
			chunk = nullptr;
		}
	}
	bzero(buf, read_bytes);
}
