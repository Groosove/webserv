//
// Created on 2/4/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#pragma once

#include "HTTPRequest.hpp"
#include <iostream>
#include <iterator>

class HTTPResponse {
private:
	size_t 	_status_code;
	char*	_buf_response;

public:
	explicit HTTPResponse();
	~HTTPResponse();

	void			generateRespose();


	char*			getBuf() const;

};