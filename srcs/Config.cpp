//
// Created by Shonna Jakku on 1/9/21.
//

#include "Config.hpp"

// utils methods
void            Config::setPath(const std::string &path) { this->_path = path; }

void            Config::parse(void) const {
	std::ifstream ifs = ifs.open(this->path);
	if (!ifs.is_open()) {
		setPath("default.conf");
		ifs.open(this->_path);
	}
	while ((this->_line = std::getline(ifs, "\n"))) {
		if (this->_line)
	}
}

// start/stop server methods
void            Config::start(void) const {
	try {
		parse();
	}
	catch(const int& value) {
		std::cout << "CHECK ENUM IN CONFIG HEADER FOR THIS VALUE: " << value << std::endl;
	}
}

// exceptions
const char*     Config::ParseFailedException::what(void) const throw() {
	return ("Parse Failed!");
}
const char*     Config::SetupFailedException::what(void) const throw() {
	return ("Setup Failed!");
}
const char*     Config::RunFailedException::what(void) const throw() {
	return ("Run Failed!");
}

// Constr
Config::Config() {}

Config::Config(const char* av): _path(std::string(av)) {
	std::cout << "Server start... " << std::endl;
}
Config::Config(const Config& c) { *this = c; }
Config& Config::operator=(const Config &c) {
	this->_path = c.getPath();
	return *this;
}
Config::~Config() {}
