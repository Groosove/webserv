#include "VirtualServer.hpp"
#include "WebServer.hpp"

int		main(int ac, char** av) {
	VirtualServer virtualServer((ac == 2) ? std::string(av[1]) : std::string((char*)"default.conf"));

}