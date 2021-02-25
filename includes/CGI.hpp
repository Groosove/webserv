//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include "HTTPRequest.hpp"

class CGI {
private:
	char** _env;
	char* _argv[3];

public:
	CGI(HTTPRequest request);
	~CGI();

	void execCGI();
	char** getEnv();
	char** pathCGI();
};
