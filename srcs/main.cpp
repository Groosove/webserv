//
// Created on 2/4/21 by.
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>l
#include <sys/select.h>
#include <cstdlib>
#include <fcntl.h>
#include <map>
#include <string>
#include <sstream>

std::string    headers[12] = {
		"Method",
		"Host",
		"Connection",
		"Upgrade-Insecure-Requests",
		"User-Agent",
		"Accept",
		"Accept-Encoding",
		"Accept-Language"
};

char*       make_response(char* req) {
	return nullptr;
}

char*       parse_request_http(int fd, char* buff) {
	std::istringstream is(buff);
	size_t  pos = 0;
	std::string line;
	std::map<std::string, std::string> map;

	while (std::getline(is, line)) {
		if ((pos = line.find(':')) != std::string::npos)
			map[std::string(line, 0, pos)] = std::string(line, pos + 2, std::string::npos);
		pos = 0;
	}
	return NULL;
}

// buff на считыание и на отправку + client_fd будет массивом
// если считал из фд, а там 0, то чел ушел!
int     main(int ac, char** av) {
	int socket_fd, client, port = 8080, max_fd, ret, kek = 1;
	char* buff = (char*)calloc(4097, 1);
	fd_set read_fd, write_fd, cp_read_fd, cp_write_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len = sizeof(client_addr);

	/*
	 * Создание сокета
	 * 1. Семейстов адресации
	 * АF_INET - для взаимодействия по сети с помощью TCP/IP
	 * AF_UNIX - для взаимодействия сокетов внутри машины
	 *
	 * 2. Задание типа взаимодействия
	 * SOCK_STREAM - потоковое взаимодействие -> константа значение
	 * SOCK_DGRAM - дейтагарммное взаимодействие -> отправка пакетов любого размера
	 *
	 * 3. Использоумей протокол (можно указать просто 0)
	 * IPPROTO_TCP - TCP
	 * IPPROTO_UDP - UDP
	 *
	 * Возращает -1 в случае ошибки
	 */

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cerr << "Can`t create socket" << std::endl;
	}


	// Хуйня чтобы порт не зацикливался
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &kek, sizeof(int));

	/*
	 * Инициализация сервера
	 * sin_family - Тип сокета
	 * sin_port - Порт сокета
	 * sin_addr - Адрес ip сокета
	 */

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	/*
	 * Связывание сокета с адресом
	 * 1. socket_fd - дескриптор сокета
	 * 2. server_addr - сервер с конкретным адресом
	 * 3. Размер струкруты сервера в байтах
	 */

	if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		std::cout << "Bind failed" << std::endl;
		return 0;
	}

	if (listen(socket_fd, 0) == -1) {
		std::cout << "Listen failed!" << std::endl;
		return 0;
	}
	max_fd = socket_fd;
	FD_ZERO(&read_fd);
	FD_ZERO(&write_fd);
	FD_SET(socket_fd, &read_fd);
	FD_SET(socket_fd, &write_fd);
	fcntl(socket_fd, F_SETFL, O_NONBLOCK);
	std::cout << "++++++Waiting new Connect++++++" << std::endl;
	for (;;) {
		cp_read_fd = read_fd;
		cp_write_fd = write_fd;
		if (select(max_fd + 1, &cp_read_fd, &cp_write_fd, NULL, (struct timeval*)0) <= 0)
			continue;
		if (FD_ISSET(socket_fd, &cp_read_fd)) {
			if ((client = accept(socket_fd, (struct sockaddr *) &client_addr, &addr_len)) > 0) {
				FD_SET(client, &read_fd);
				FD_SET(client, &write_fd);
				if (client > max_fd)
					max_fd = client;
				std::cout << "++++++New user id added!++++++" << std::endl;
			}
		}
		for (int i = 0; i <= max_fd; ++i) {
			if (FD_ISSET(i, &cp_read_fd)) {
				ret = recv(i, buff, 4097, 0);
				if (ret == 0) {
					std::cout << "++++++USER DISCONNECT!++++++" << std::endl;
					FD_CLR(i, &read_fd);
					FD_CLR(i, &write_fd);
					close(i);
				}
				else {
					request_buffer = parse_request_http(i, buff); // если файловый дескриптор, готов на чтение и у нас уже пришел запрос, то мы начинаем парсить этот запрос
//					response_buffer = make_response(request_buffer);
//					NULL;
				}
			}
		}
		for (int i = 0; i <= max_fd; ++i) {
			if (FD_ISSET(i, &cp_write_fd)) {
				send(i, buff, strlen(buff), 0);
			}
		}
		bzero(buff, 4097);
	}

	return 0;
}
