//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include "HTTPRequest.hpp"
#include "VirtualServer.hpp"
#include "Client.hpp"

class CGI {
public:
	CGI(Client* client, VirtualServer* virtualServer, char * path);
	~CGI();

	void execCGI(HTTPResponse* response);
	char** getEnv() const { return _env; }
	void setPathCGI(char * path);
	char* getPathCGI() const { return _argv[0]; }

private:
	HTTPRequest* _request;
	HTTPResponse* _response;
	char**	_env;
	char*	_argv[3];
	int 	_sizeEnv;
};
