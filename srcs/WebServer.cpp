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

typedef struct	s_client {
	char *read_buff;
	char *write_buff;
}				t_client;

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
		handle(&_virtual_server[i]);
	}
}

std::vector<VirtualServer> WebServer::getVirtualServer() {
	return std::vector<VirtualServer>(_virtual_server);
}

void WebServer::handle(VirtualServer* virtualServer) { // TODO разнести тело цикла по методам _virtual_server и накидать класс CLIENT;
	int									max_fd, ret, client;
	struct sockaddr_in					client_addr;
	socklen_t 							addr_len = sizeof(client_addr);
	fd_set 								read_fd, write_fd, cp_read_fd, cp_write_fd;
	char* 								buff = (char*)calloc(4097, 1);
	std::map< int, t_client > 			clients;
	std::map< int, t_client >::iterator begin;
	std::map< int, t_client >::iterator end;
	t_client 							temp;
	char								*chunk = nullptr;

	bzero(&temp, sizeof(temp));
	// TODO в цикле добавлять фдшники каждого сервера в сет
	max_fd = virtualServer->getSocket();
	FD_ZERO(&read_fd);
	FD_ZERO(&write_fd);
	FD_SET(virtualServer->getSocket(), &read_fd);
	FD_SET(virtualServer->getSocket(), &write_fd);
	std::cout << "++++++Waiting new Connect++++++" << std::endl;
	while (_status) {
		cp_read_fd = read_fd;
		cp_write_fd = write_fd;
		select(max_fd + 1, &cp_read_fd, &cp_write_fd, nullptr, nullptr); //TODO добавить цикл для проверки каждого сервера, фдешника в сетах ( строка ниже )
		if (FD_ISSET(virtualServer->getSocket(), &cp_read_fd)) {
			if ((client = accept(virtualServer->getSocket(), (struct sockaddr *) &client_addr,
								 &addr_len)) > 0) {
				FD_SET(client, &read_fd);
				FD_SET(client, &write_fd);
				max_fd = (client > max_fd) ? client : max_fd;
				clients[client] = temp; // создаем пару
				std::cout << "++++++New user id added!++++++" << std::endl;
			}
		}
		for (begin = clients.begin(); begin != clients.end(); begin++)
		{
			if (FD_ISSET(begin->first, &cp_read_fd))
			{
				ret = recv(begin->first, buff, 4096, 0);
				if (ret == 0)
				{
					close(begin->first);
					if(begin->second.read_buff)
						free(begin->second.read_buff);
					if(begin->second.write_buff)
						free(begin->second.write_buff);
					FD_CLR(begin->first, &read_fd);
					FD_CLR(begin->first, &write_fd);
					clients.erase(begin);
					std::cout << "++++++New user id delete!++++++" << std::endl;
					break;
				}
				else if (ret > 0)
				{
					begin->second.read_buff = str_join(begin->second.read_buff, buff);
					//тут ты пиздуешь в обработку или сначала смотришь есть ли тут \r\n
					while (extract_message(&(begin->second.read_buff), &chunk))
					{
						begin->second.write_buff = ft_strdup(virtualServer->treatmentRequest(chunk));
						std::cout << chunk << " 1 " << std::endl;
						free(chunk);
						chunk = nullptr;
					}
				}
				bzero(buff, ret);
			}
		}
		for (begin = clients.begin(); begin != clients.end(); begin++)
		{
			if (FD_ISSET(begin->first, &cp_write_fd) && begin->second.write_buff)
			{
				ret = send(begin->first, begin->second.write_buff, strlen(begin->second.write_buff), 0);
				if (ret == 0)
				{
					close(begin->first);
					if(begin->second.read_buff)
						free(begin->second.read_buff);
					if(begin->second.write_buff)
						free(begin->second.write_buff);
					FD_CLR(begin->first, &read_fd);
					FD_CLR(begin->first, &write_fd);
					clients.erase(begin);
					break;
				}
				else if (ret != strlen(begin->second.write_buff))
				{
					chunk = str_join(chunk, begin->second.write_buff + ret);
					free(begin->second.write_buff);
					begin->second.write_buff = chunk;
				}
				else
				{
					free(begin->second.write_buff);
					begin->second.write_buff = nullptr;
				}
			}
		}
	}
}
