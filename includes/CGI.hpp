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

class CGI {
private:
	HTTPRequest _request;
	char**	_env;
	char*	_argv[3];
	int 	_sizeEnv;

public:
	CGI(HTTPRequest request, VirtualServer virtualServer);
	~CGI();

	void execCGI(HTTPResponse response);
	char** getEnv() const { return _env; }
	void setPathCGI(char * string);
	char* getPathCGI() const { return _argv[0]; }
};
