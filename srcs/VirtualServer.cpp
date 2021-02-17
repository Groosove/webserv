//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "VirtualServer.hpp"

void VirtualServer::setHost(const std::string &host) {
	_host = host;
	_parametr.insert(std::make_pair("host", _host));
}

void VirtualServer::setPort(const std::string &port) {
	_port = port;
	_parametr.insert(std::make_pair("port", _port));
}

void VirtualServer::setSocket(int socket) {
	_socket = socket;
	_parametr.insert(std::make_pair("socket", std::to_string(socket)));
}

void VirtualServer::setServerName(const std::string &server_name) {
	_server_name = server_name;
	_parametr.insert(std::make_pair("server_name", _server_name));
}

void VirtualServer::setErrorPage(const std::string &error_page) {
	_error_page.push_back(error_page);
}

void VirtualServer::initSocket() {
	int	param = 1; // парамет р для setsockopt;
	// Создаем сокет сервера;
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		std::cerr << "Can`t create socket fd" << std::endl;
	// Делаем сокет незацикливающимся;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &param, sizeof(int));
}

void VirtualServer::preparationParams() {
	/*
	 * Инициализация сервера
	 * sin_family - Тип сокета
	 * sin_port - Порт сокета
	 * sin_addr - Адрес ip сокета
	*/

	_server_addr.sin_family = AF_INET;
	_server_addr.sin_port = htons((uint16_t )std::stoi(_port));
	_server_addr.sin_addr.s_addr = inet_addr(_host.c_str());

	/*
	 * Связывание сокета с адресом
	 * 1. socket_fd - дескриптор сокета
	 * 2. server_addr - сервер с конкретным адресом
	 * 3. Размер струкруты сервера в байтах
	*/

	// биндим наш сокет на определенный адресс и порт
	if (bind(_socket, (struct sockaddr *)&_server_addr, sizeof(_server_addr)) == -1) {
		std::cout << "Bind failed" << std::endl;
		return ;
	}
	// делаем файловый дескриптор сокета неблокирующимся
	fcntl(_socket, F_SETFL, O_NONBLOCK);
	// начинаем слушать порт
	if (listen(_socket, 0) == -1) {
		std::cout << "Listen failed!" << std::endl;
		return ;
	}
}

const char* VirtualServer::treatmentRequest(const char* buf) {
	_request = new HTTPRequest(buf);
	if (std::string(_request->getMethod()).find("GET") != std::string::npos)
		generateResponse(_request->getMethod());
	return _complete_response.c_str();
}

void	VirtualServer::generateResponse(const char *method) {
	std::map<std::string, Location>::iterator begin = _location.begin();
	std::cout << begin->first << std::endl;
	while (begin != _location.end()) {
		if (begin->first.find((_request->getPath())) != std::string::npos) {
			if (!begin->second.validationLocation(_request->getMethod()))
				return;
			else
			{
				_response = new HTTPResponse(_request->getMethod());
				_complete_response.append(_response->getResponse());
				addBodyToResponse(begin->second);
				break ;
			}
		}
		begin++;
	}
}

void VirtualServer::addBodyToResponse(const Location& location) {
	std::ifstream	thread(location.getRoot() + location.getIndex());
	std::string		buf;

	while(std::getline(thread, buf))
		_complete_response.append(buf);

	_complete_response.append("\r\n\r\n\r\n");
	std::cout << "RESPONSE: " << _complete_response << std::endl;
}


