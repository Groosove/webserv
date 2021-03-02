//
// Created on 2/4/21 by.
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "WebServer.hpp"

int main(int ac, char** av) {
	WebServer webServer(av[1]);

	signal(SIGPIPE, SIG_IGN);
	webServer.createVirtualServer();
	std::vector<VirtualServer>::iterator it_begin;
	std::vector<VirtualServer>::iterator it_end;
	it_begin = webServer.getVirtualServer().begin();
	it_end = webServer.getVirtualServer().end();

	for (; it_begin != it_end; ++it_begin) {
		std::cout << "SERVER: " << (*it_begin).getHost() << std::endl;
		std::cout << "SERVER: " << (*it_begin).getPort() << std::endl;
		std::cout << "SERVER: " << (*it_begin).getServerName() << std::endl;
		std::cout << "SERVER: " << (*it_begin).getSocket() << std::endl;
	}
}
