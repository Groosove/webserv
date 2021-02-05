//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "WebServer.hpp"

void WebServer::parseConfigFile(std::ifstream &file) {
	std::string buf;
	while (std::getline(file, buf)) {
		std::cout  << buf << std::endl;
		if (buf.find("server", 0) != std::string::npos)
			_virtual_server.push_back(VirtualServer(file));
	}
}

WebServer::WebServer(const char *config_name) {
	std::ifstream file_config(config_name);
	if (file_config.is_open())
		parseConfigFile(file_config);
	else
		std::cerr << "File doesn't open!" << std::endl;
}

void WebServer::handle() {
	while (_status) {

	}
}
