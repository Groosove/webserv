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
	if (buf.find("host", 0, 4) != std::string::npos) {
		std::cout << " THIS IS BUFF " << buf << std::endl;
		setHost(buf.substr(0, '\t'));
	}
	else if (buf.find("port", 0) != std::string::npos)
		setPort(buf.substr(0, '\t'));
	else if (buf.find("server_name", 0) != std::string::npos)
		setServerName(buf);
	else
		_error_page.push_back(buf);
}

VirtualServer::VirtualServer(std::ifstream &config_name) {
	std::string buf;
	while (std::getline(config_name, buf)) {
//		std::cout  << buf << std::endl;
		if (buf.find("location", 0) == std::string::npos)
			_parseServerParam(buf);
	}
	std::cout << " KEK: " << _host << std::endl;
	std::cout << " KEK: " << _port << std::endl;
	std::cout << " KEK: " << _server_name << std::endl;
}