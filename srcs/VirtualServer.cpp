//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "VirtualServer.hpp"
// TODO накидать сплит для парсера строк
void VirtualServer::_parseServerParam(const std::string& buf) {
	size_t i = 0;
	if ((i = buf.find("host:", 0, 5)) != std::string::npos)
		setHost(buf.substr(i + 5,  buf.length()));
	else if ((i = buf.find("port:", 0, 5)) != std::string::npos)
		setPort(buf.substr(i + 5, buf.length()));
	else if ((i = buf.find("server_name:", 0, 12)) != std::string::npos)
		setServerName(buf.substr(i + 12, buf.length()));
	else
		_error_page.push_back(buf);
}

VirtualServer::VirtualServer(std::ifstream &config_name) {
	std::string buf;
	while (std::getline(config_name, buf)) {
		if (buf.find("server:", 0) != std::string::npos)
			break;
		if (buf.find("location:", 0) == std::string::npos)
			_parseServerParam(buf);
		else {
			size_t index = 0;
			while (buf[index] != ':')
				++index;
			buf.erase(0, index + 1);
			_location.insert(std::make_pair(ft_strtrim(buf, " \t"), Location(config_name)));
		}
	}
	std::cout << "KEK: " << _host << std::endl;
	std::cout << "KEK: " << _port << std::endl;
	std::cout << "KEK: " << _server_name << std::endl;
}

void VirtualServer::setHost(const std::string &host) {
	_host = ft_strtrim(host, " \t");
	_parametr.insert(std::make_pair("host", _host));
}

void VirtualServer::setPort(const std::string &port) {
	_port = ft_strtrim(port, " \t");
	_parametr.insert(std::make_pair("port", _port));
}

void VirtualServer::setSocket(int socket) {
	_socket = socket;
	_parametr.insert(std::make_pair("socket", std::to_string(socket)));
}

void VirtualServer::setServerName(const std::string &server_name) {
	_server_name = ft_strtrim(server_name, " \t");
	_parametr.insert(std::make_pair("server_name", _server_name));
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