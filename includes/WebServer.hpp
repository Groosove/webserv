//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include "VirtualServer.hpp"
class WebServer {
private:
	std::vector<VirtualServer>	_virtual_server;
	bool						_status;
public:
	explicit WebServer();
	~WebServer();
	void	handle();
};