//#include "Config.hpp"
//
//int     main(int ac, char** av) {
//	if (ac == 2) {
//		Config *sever = new Config(av[1]);
//		try {
//			server->start();
//			sever->stop();
//		}
//		catch (const std::exception& e) {
//			std::cout << e.what() << std::endl;
//		}
//	}
//	else
//		std::cerr << "Please try: ./WebServer <something path>" << std::endl;
//	return 0;
//}



//int     server_fd;
//
//	if (ac != 2) {
//		std::cerr << "Please try: ./WebServer <something path>" << std::endl;
//	return 0;
//	}
///* открываем сокет для нашей системы
// * A socket is the mechanism that most popular operating systems provide to give programs access to the network.
// * It allows messages to be sent and received between applications (unrelated processes) on different networked machines.
// */
//		if ((server_fd = socket(AF_NET, SOCK_STREAM, 0)) < 0) {
//			std::cerr << "Can`t create socket" << std::endl;
//		}
//	}
//	catch(const std::exception& e) {
//	std::cerr << e.what() << std::endl;
//}

#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <cstdlib>
#include <fcntl.h>

// buff на считыание и на отправку + client_fd будет массивом
// если считал из фд, а там 0, то чел ушел!
int     main(int ac, char** av) {
	int socket_fd, client, port = 8080, max_fd, ret, kek = 1;
	char* buff = (char*)calloc(4097, 1);
	fd_set read_fd, write_fd, cp_read_fd, cp_write_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len = sizeof(client_addr);
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cerr << "Can`t create socket" << std::endl;
	}
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &kek, sizeof(int));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
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
//	fcntl(socket_fd, F_SETFL, O_NONBLOCK);
	for (;;) {
		cp_read_fd = read_fd;
		cp_write_fd = write_fd;
		if (select(max_fd + 1, &cp_read_fd, &cp_write_fd, NULL, (struct timeval*)0) <= 0) {
			std::cout << "KEKEKEKEK" << std::endl;
			continue;
		}
		if (FD_ISSET(socket_fd, &cp_read_fd)) {
			if ((client = accept(socket_fd, (struct sockaddr *) &client_addr, &addr_len)) > 0) {
				FD_SET(client, &read_fd);
				FD_SET(client, &write_fd);
				if (client > max_fd)
					max_fd = client;
				std::cout << "COOL!" << std::endl;
			}
		}
		for (int i = 0; i <= max_fd; ++i) {
			if (FD_ISSET(i, &cp_read_fd)) {
				ret = recv(i, buff, 4097, 0);
				if (ret == 0) {
					std::cout << "USER DISCONNECT!" << std::endl;
					FD_CLR(i, &read_fd);
					FD_CLR(i, &write_fd);
					close(i);
				}
				else
					NULL;
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
