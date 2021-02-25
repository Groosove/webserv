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


CGI::CGI(HTTPRequest request) {
	_env[0] = ft_strdup("AUTH_TYPE=BASIC");
	_env[1] = ft_strdup("CONTENT_LENGTH="); // длина содержимого
	_env[2] = ft_strdup("CONTENT_TYPE="); //MIME-type содержимого text/html, image/jpg
	_env[3] = ft_strdup("GATEWAY_INTERFACE=CGI/1.1");
	_env[4] = ft_strdup("PATH_INFO="); // HTTP-путь к сценарию
	_env[5] = ft_strdup("PATH_TRANSLATED="); // полный путь к сценарию
	_env[6] = ft_strdup("QUERY_STRING="); //Строка запроса, если есть, через которую была открыта страницаx
	_env[7] = ft_strdup("REMOTE_ADDR="); //IP-адрес, с которого пользователь просматривает текущую страницу
	_env[8] = ft_strdup("REMOTE_IDENT="); // часть от аутентификации пользователя ??? //
	_env[9] = ft_strdup("REMOTE_USER="); //Аутентифицированный пользователь //
	_env[10] = ft_strjoin("REQUEST_METHOD=", request.getMethod());
	_env[11] = ft_strjoin("REQUEST_URI=", request.getHostUrl()); // url == uri (?)
	_env[12] = ft_strdup("SCRIPT_NAME="); //Содержит путь к текущему исполняемому скрипту
	_env[13] = ft_strdup("SERVER_NAME="); //hostName virtualServer.getName()
	_env[14] = ft_strdup("SERVER_PORT="); //Порт на компьютере сервера virtualServer.getSocket()
	_env[15] = ft_strjoin("SERVER_PROTOCOL=", request.getVersionHTTP());
	_env[16] = ft_strdup("SERVER_SOFTWARE=");//Строка идентификации сервера, указанная в заголовках, когда происходит ответ на запрос
	_env[17] = nullptr;
}

CGI::~CGI() {
	for (int i = 0; i < 17; ++i) {
		free(_env[i]);
	}
	for (int i = 0; i < 2; ++i) {
		free(_argv[i]);
	}
}

void CGI::execCGI() {
	int fd_out;
	pid_t pid;
	int file_fd;

	fd_out = dup(1);
	file_fd = open("file", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if ((pid = fork()) == -1) {;}
	else if (pid == 0) {
		dup2(file_fd, 1);
		dup2(fd_out, 1);
		close(file_fd);
		int status = execve(_argv[0], _argv, _env);
		exit(status);
	} else {

	}
}

char ** CGI::pathCGI() {
	_argv[0] = ft_strdup("/Users/fkathryn/Desktop/cgi/test.py");
	_argv[1] = ft_strdup("/Users/fkathryn/Desktop/cgi/test.py");
	_argv[2] = nullptr;
}

char ** CGI::getEnv() { return _env; }
