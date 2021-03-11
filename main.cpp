//
// Created on 2/4/21 by.
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "WebServer.hpp"

int main(int ac, char** av) {
	const char *config_name = (ac == 1) ? "configs/default.conf" : av[1];
	try {
		WebServer webServer(config_name);
		signal(SIGPIPE, SIG_IGN);
		webServer.createVirtualServer();
	} catch (const std::exception &e) {
		std::cout << "BAD CONFIG" << std::endl;
		return 9;
	}

	return 0;
}
