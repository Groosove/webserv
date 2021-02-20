//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest(const char * buf) {
	std::cout << "Request ready for create" << std::endl;
}

HTTPRequest::~HTTPRequest() {}

void HTTPRequest::parse_request_http(const char * buf) {
	size_t pos = 0;
	std::string tmp_buf = std::string(buf);

	while (!tmp_buf.empty()) {
		if (getParsingStage() == parse_first_line) {
			if ((pos = tmp_buf.find("\r\n")) != std::string::npos) {
				parseFirstLine(tmp_buf.substr(pos + 2));
				tmp_buf.erase(pos + 2);
			}
			else return ;
		}
		else if (getParsingStage() == parse_other_headers) {
			if ((pos = tmp_buf.find("\r\n")) != std::string::npos) {
				parseHeaders(tmp_buf.substr(pos + 2));
				tmp_buf.erase(pos + 2);
			}
			else if ((pos = tmp_buf.find("\r\n")) == 0) {
				checkValidHeaders();
				tmp_buf.erase(pos + 2);
			}
			else
				return ;
			break ;
		}
	}
}

void HTTPRequest::parseFirstLine(const std::string& line) {
	std::vector<std::string> dst = ft_split(line, std::string(" "), 1);
	for (int i = 0; i != dst.size() - 1; ++i) {
		if (i == 0)
			setMethod((char*)dst[i].c_str());
		else if (i == 1)
			setPath((char*)dst[i].c_str());
		else
			setVersionHTTP((char*)dst[i].c_str());
	}
}

void HTTPRequest::parseHeaders(const std::string& header_line) {
	size_t pos;

	if (std::count(header_line.begin(), header_line.end(), ':') < 1)
		throw std::string("400");
	if ((pos = header_line.find("Host")) != std::string::npos)
		setHostUrl((char*)header_line.substr(pos + 2).c_str());
	pos = header_line.find(':');
	_request_params[header_line.substr(pos)] = header_line.substr(pos + 2);
}

void HTTPRequest::checkValidHeaders() {
	if (!_host_url)
		throw std::string("400");
	setParsingStage(complite);
}

void HTTPRequest::setHostUrl(char *host_url) {
	_host_url = host_url;
}

void HTTPRequest::setMethod(char *method) {
	_method = method;
}

void HTTPRequest::setPath(char * path) {
	_path = path;
}

void HTTPRequest::setVersionHTTP(char *version_http) {
	_version_http = version_http;
}

void HTTPRequest::setRequestParams(std::map<std::string, std::string> request_params) {
	_request_params = request_params;
}

void HTTPRequest::setStatusCode(const std::string &status_code) {
	_status_code = status_code;
}



//char **request = ft_split(buf, '\n');
//std::map<std::string, std::string> result;
//size_t  pos;
//for (size_t i = 0; request[i] != nullptr; ++i) {
//if (ft_strchr(request[i], ':') == -1 && request[i + 1] != nullptr)
//parseFirstLine((request[i]));
//else if ((pos = ft_strchr(request[i], ':')) != (size_t) -1) {
//if (ft_compare(request[i], "Host", 4))
//setHostUrl(ft_substr(request[i], pos + 2, ft_strlen(request[i]) - 1));
//else
//result[ft_substr(request[i], 0, pos)] = ft_substr(request[i], pos + 2,
//ft_strlen(request[i]) - 1);
//}
//}
//return result;