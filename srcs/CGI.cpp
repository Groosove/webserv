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

int	status = 0;

CGI::CGI(Client* client, VirtualServer* virtualServer, char * path) {
	_request = client->getRequest();
	_response = client->getResponse();
	_path = ft_strdup(path);
	_sizeEnv = 18;
	_env = (char**)calloc(_sizeEnv, sizeof(char*));
	_env[0] = ft_strdup("AUTH_TYPE=basic");
	_env[1] = ft_strjoin("CONTENT_LENGTH=", std::to_string(_request->getBodySize()).c_str());
	_env[2] = ft_strjoin("CONTENT_TYPE=", (_request->getContentType()));
	_env[3] = ft_strdup("GATEWAY_INTERFACE=CGI/1.1");
	_env[4] = ft_strjoin("PATH_INFO=", _request->getPath());
	_env[5] = ft_strjoin("PATH_TRANSLATED=", _path);
	_env[6] = ft_strjoin("QUERY_STRING=", _request->getHttpQuery());
	_env[7] = ft_strdup("REMOTE_ADDR=");
	_env[8] = ft_strdup("REMOTE_IDENT=");
	_env[9] = ft_strdup("REMOTE_USER=");
	_env[10] = ft_strjoin("REQUEST_METHOD=", _request->getMethod());
	_env[11] = ft_strjoin("REQUEST_URI=http://", (client->getHost() + ":" + client->getPort() + _request->getPath()).c_str());
	_env[12] = ft_strjoin("SCRIPT_NAME=", _request->getPath());
	_env[13] = ft_strjoin("SERVER_NAME=", client->getHost().c_str());
	_env[14] = ft_strjoin("SERVER_PORT=", client->getPort().c_str());
	_env[15] = ft_strjoin("SERVER_PROTOCOL=", _request->getVersionHTTP());
	_env[16] = ft_strdup("SERVER_SOFTWARE=");//Строка идентификации сервера, указанная в заголовках, когда происходит ответ на запрос
	_env[17] = nullptr;
	std::cout << "PATH : " << path << std::endl;
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
	pid_t 	pid;
	int 	file_fd;
	char 	buf;
	int		pipe_fd[2];
	char* 	result_buf = (char*)calloc(_request->getBodySize() + 1, sizeof(char));

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
		perror("ERRNO = ");
		std::cout << "YA YPAL REBYATKI" << std::endl;
		exit(0);
	}
	else if(pid == -1) {
		;//error
	}
	else {
		write(pipe_fd[1], _request->getBody(), _request->getBodySize());
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		wait(&status);
		std::pair<char *, int> result;
		std::cout << "HELLO IAM HERE" << std::endl;
		if (!status) {
			lseek(file_fd, 0, 0);
			size_t size = 0;
			while (read(file_fd, &buf, 1) > 0)
				result_buf[size++] = buf;
			int pos = ft_strnstr(result_buf, (char*)"\r\n\r\n", size) + 4;
			char* result_header = ft_substr(result_buf, 0, pos);
			char* send_res_buf = ft_substr(result_buf, pos, size);
			response->setCgiHeaders(result_header);
			result.first = send_res_buf;
			result.second = size - pos;
		}
		response->setBody(result);
		response->setStatusCode("200");
	}
	close(file_fd);
	free(result_buf);
}
