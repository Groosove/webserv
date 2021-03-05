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
#include <Client.hpp>


CGI::CGI(Client* client, VirtualServer* virtualServer, char * path) {
	_request = client->getRequest();
	_response = client->getResponse();
	_sizeEnv = 18;
	_env = (char**)calloc(_sizeEnv, sizeof(char*));
	_env[0] = ft_strdup("AUTH_TYPE=BASIC");
	_env[1] = ft_strjoin("CONTENT_LENGTH=", _request->getContentLength());
	_env[2] = ft_strjoin("CONTENT_TYPE=", (_request->getContentType()));
	_env[3] = ft_strdup("GATEWAY_INTERFACE=CGI/1.1");
	_env[4] = ft_strjoin("PATH_INFO=", path); // HTTP-путь к сценарию
	_env[5] = ft_strjoin("PATH_TRANSLATED=", getPathCGI());
	_env[6] = ft_strdup("QUERY_STRING="); //Строка запроса, если есть, через которую была открыта страница
	_env[7] = ft_strdup("REMOTE_ADDR="); //IP-адрес, с которого пользователь просматривает текущую страницу
	_env[8] = ft_strdup("REMOTE_IDENT=");
	_env[9] = ft_strdup("REMOTE_USER=");
	_env[10] = ft_strjoin("REQUEST_METHOD=", "POST");
	_env[11] = ft_strjoin("REQUEST_URI=", _request->getHostUrl());
	_env[12] = ft_strjoin("SCRIPT_NAME=", getPathCGI());
	_env[13] = ft_strjoin("SERVER_NAME=", virtualServer->getServerName().c_str());
	_env[14] = ft_strjoin("SERVER_PORT=", std::to_string(virtualServer->getSocket()).c_str());
	_env[15] = ft_strjoin("SERVER_PROTOCOL=", _request->getVersionHTTP());
	_env[16] = ft_strdup("SERVER_SOFTWARE=");//Строка идентификации сервера, указанная в заголовках, когда происходит ответ на запрос
	_env[17] = nullptr;
	std::cout << path << " THIS IS ENV " << _env[10] << std::endl;
	_path = ft_strdup(path);
	setArgs();
	execCGI(_response);
}

CGI::~CGI() {
	for (int i = 0; i < _sizeEnv - 1; ++i) {
		free(_env[i]);
	}
	free(_env);
	free(_path);
}

void CGI::execCGI(HTTPResponse* response) {
	pid_t pid;
	int file_fd;
	char buf;
	int		pipe_fd[2];
	char* result_buf = (char*)calloc(100000, sizeof(char));

	pipe(pipe_fd);
	file_fd = open("file", O_CREAT | O_RDWR | O_TRUNC, 0677);
	std::cerr << "FORK" << std::endl;
	if ((pid = fork()) == 0) {
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		dup2(file_fd, 1);
		close(file_fd);
		execve(_argv[0], _argv, getEnv());
		std::cerr << "YA YPAL REBYATKI" << std::endl;
		exit(1);

	}
	else if(pid == -1) {
		;//error
	}
	else {
		std::cerr << "HELLO REBYATKI, IM HERE" << std::endl;
		write(pipe_fd[1], _request->getBody(), _request->getBodySize());
		std::cerr << "HELLO REBYATKI, IM HERE" << std::endl;
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		wait(nullptr);
		std::cerr << "HELLO REBYATKI, IM HERE" << std::endl;
		lseek(file_fd, 0, 0);
		int r, size = 0;
		while ((r = read(file_fd, &buf, 1)) > 0) {
			result_buf[size++] = buf;
		}
		std::cerr << "HELLO REBYATKI, IM HERE" << std::endl;
		std::pair<char*, int> result;
		result.first = result_buf;
		result.second = size;
		//delete old response
		std::cerr << "HELLO REBYATKI, IM HERE" << std::endl;
		response->setBody(result);
		response->setStatusCode("200");
	}
	close(file_fd);
	free(result_buf);
}

void CGI::setArgs() {
	_argv[0] = _path;
	_argv[1] = _path;
	_argv[2] = nullptr;
}
