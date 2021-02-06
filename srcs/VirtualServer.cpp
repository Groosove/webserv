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