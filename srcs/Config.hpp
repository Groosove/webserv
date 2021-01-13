//
// Created by Shonna Jakku on 1/9/21.
//

#ifndef WEBSERV_CONFIG_HPP
#define WEBSERV_CONFIG_HPP

#include <iostream>
#include <iomanip>

enum Error {
	ERROR_PARSE,
	ERROR_BIND,
	ERROR_SELECT,
	ERROR_PATH,
	ERROR_CONFIG,
	ERROR_PORT,
	ERROR_SERVERNAME,
};

class Config {
public:
	// constr
	Config();
	Config(const Config &);
	Config &operator=(const Config &);
	~Config();

	// start/stop server methods
	void             start(void) const;
	void             stop(void) const;

	// utils for start/stop server methods
	void             parse(void) const;
	void             setup(void) const;
	void             run(void) const;

	// getters
	std::string&     getPath(void) const;


	//setters
	std::string&    setPath(const std::string& path);

	// exceptions
	struct ParseFailedException: public std::exception { const char* what(void) const throw()};
	struct SetupFailedException: public std::exception { const char* what(void) const throw()};
	struct RunFailedException: public std::exception { const char* what(void) const throw()};
private:
	std::string _path;
};


#endif //WEBSERV_CONFIG_HPP
