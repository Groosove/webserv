//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "Client.hpp"

Client::Client(int client_socket, const std::string &host, const std::string &port): _socket(client_socket), _request(), _response(), _host(host), _port(port), _stage(1) {
	std::cout << "Client is added" << std::endl;
}
