//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "WebServer.hpp"

void WebServer::parseConfigFile(std::ifstream &config_name) {
	std::string buf;
	while (std::getline(config_name, buf)) {
		if (buf.find("server", 0) != std::string::npos)
			_virtual_server.push_back(VirtualServer(config_name));
	}
}

WebServer::WebServer(const char *config_name) {
	std::ifstream file_config(config_name);
	if (file_config.is_open())
		parseConfigFile(file_config);
	else
		std::cerr << "File doesn't open!" << std::endl;
}

void WebServer::createVirtualServer() {
	for (size_t i = 0; i < _virtual_server.size(); ++i) {
//		check_valid_virtual_server(); // TODO написать валидацию серверов, для того чтобы не запускать рандомный сервер, напишем потом!
		_virtual_server[i].initSocket();
		_virtual_server[i].preparationParams();
		handle(_virtual_server[i]);
	}
}

std::vector<VirtualServer> WebServer::getVirtualServer() {
	return std::vector<VirtualServer>(_virtual_server);
}

void WebServer::handle(VirtualServer &virtualServer) {

}
