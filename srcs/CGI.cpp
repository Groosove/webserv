//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "CGI.hpp"
#include <utils.hpp>
#include <fcntl.h>


CGI::CGI(HTTPRequest request, VirtualServer virtualServer) {
	this->_request = request;
	_sizeEnv = 18;
	_env = (char**)calloc(_sizeEnv, sizeof(char*));
	_env[0] = ft_strdup("AUTH_TYPE=BASIC");
	_env[1] = ft_strjoin("CONTENT_LENGTH=", std::to_string(request.getRequestSize()).c_str());
	if (!(request.getHeaders().find("Content-type")->second.empty())) {
		_env[2] = ft_strjoin("CONTENT_TYPE=", (request.getHeaders().find("Content-type")->second).c_str());
	} else {
		_env[2] = ft_strdup("CONTENT_TYPE=");
	}
	_env[3] = ft_strdup("GATEWAY_INTERFACE=CGI/1.1");
	_env[4] = ft_strdup("PATH_INFO="); // HTTP-путь к сценарию
	_env[5] = ft_strjoin("PATH_TRANSLATED=", getPathCGI());
	_env[6] = ft_strdup("QUERY_STRING="); //Строка запроса, если есть, через которую была открыта страница
	_env[7] = ft_strdup("REMOTE_ADDR="); //IP-адрес, с которого пользователь просматривает текущую страницу
	_env[8] = ft_strdup("REMOTE_IDENT="); // часть от аутентификации пользователя ??? //
	_env[9] = ft_strdup("REMOTE_USER="); //Аутентифицированный пользователь //
	_env[10] = ft_strjoin("REQUEST_METHOD=", request.getMethod());
	_env[11] = ft_strjoin("REQUEST_URI=", request.getHostUrl());
	_env[12] = ft_strjoin("SCRIPT_NAME=", getPathCGI());
	_env[13] = ft_strjoin("SERVER_NAME=", virtualServer.getServerName().c_str());
	_env[14] = ft_strjoin("SERVER_PORT=", std::to_string(virtualServer.getSocket()).c_str());
	_env[15] = ft_strjoin("SERVER_PROTOCOL=", request.getVersionHTTP());
	_env[16] = ft_strdup("SERVER_SOFTWARE=");//Строка идентификации сервера, указанная в заголовках, когда происходит ответ на запрос
	_env[17] = nullptr;
	setPathCGI(ft_strdup("/Users/fkathryn/Desktop/webserv/cgi_scripts/test.py"));
}

CGI::~CGI() {
	for (int i = 0; i < _sizeEnv - 1; ++i) {
		free(_env[i]);
	}
	free(_env);
	for (int i = 0; i < 2; ++i) {
		free(_argv[i]);
	}
}

void CGI::execCGI(HTTPResponse response) {
	int fd_out;
	pid_t pid;
	int file_fd;
	char buf;
	char* result_buf = (char*)calloc(10000, sizeof(char));

	fd_out = dup(1);
	file_fd = open("file", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if ((pid = fork()) == 0) {
		dup2(file_fd, 1);
		exit(execve(_argv[0], _argv, getEnv()));
	}
	else if(pid == -1) {
		;//error
	}
	else {
		write(fd_out, _request.getBody(), _request.getRequestSize());
		wait(nullptr);
		lseek(file_fd, 0, 0);
		int r, size = 0;
		while ((r = read(file_fd, &buf, 1)) > 0) {
			result_buf[size++] = buf;
		}
		std::pair<char*, int> result;
		result.first = result_buf;
		result.second = size;
		//delete old response
		response.setBody(result);
	}
	close(file_fd);
}

void CGI::setPathCGI(char * string) {
	_argv[0] = string;
	_argv[1] = string;
	_argv[2] = nullptr;
}
