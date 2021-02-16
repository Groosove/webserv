//
// Created by Fenix Lavon on 2/11/21.
// Copyright (c) 2021 All rights reserved.
//

#include <FileParser.hpp>

FileParser::FileParser(std::vector<std::string> config) {
	size_t size = config.size();
	size_t pos;

	for (size_t i = 0; i < size;) {
		if ((pos = config[i].find("server:")) != std::string::npos && checkIndent(config[i], pos, 0))
			_server.push_back(parseConfigFile(config, ++i));
		++i;
	};
}

VirtualServer FileParser::parseConfigFile(std::vector<std::string> config, size_t &index) {
	VirtualServer server;
	size_t size = config.size();
	size_t pos;
	_parseServerParam(config, index, server);
	for (size_t i = index; i < size; ++i) {
		if ((pos = config[i].find("location:")) != std::string::npos && checkIndent(config[i], pos, 1)) {
			Location location;
			std::string path = getArgument(config[i], ft_strchr(config[i], ':'));
			i++;
			while (config[i].find("location:") == std::string::npos && !config[i].empty() && config[i].find("server:") == std::string::npos && i < size) {
				if ((pos = config[i].find("root:", 0, 5)) != std::string::npos)
					location.setRoot(getArgument(config[i], ft_strchr(config[i], ':')));
				else if ((pos = config[i].find("index:", 0, 6)) != std::string::npos)
					location.setIndex(getArgument(config[i], ft_strchr(config[i], ':')));
				else if ((pos = config[i].find("allow_methods:", 0, 14)) != std::string::npos)
					location.setAllowMethods(getArgument(config[i], ft_strchr(config[i], ':')));
				else if ((pos = config[i].find("autoindex:", 0, 10)) != std::string::npos)
					location.setAutoIndex(getArgument(config[i], ft_strchr(config[i], ':')));
				else if ((pos = config[i].find("limits_client_body_size", 0, 24)) !=  std::string::npos)
					location.setRequestLimits(getArgument(config[i], ft_strchr(config[i], ':')));
				if (!checkIndent(config[i], pos, 2)) { std::cerr << "Error parse config file" << std::endl; break; }
				i++;
			}
			server.getLocation()[path] = location;
		}
		else if (config[i].empty()) continue;
		else { std::cerr << "Error parse config file" << std::endl; break; }
		if (config[i].find("server:") != std::string::npos) break;
	}
	for (std::map<std::string, Location>::iterator it = server.getLocation().begin(); it != server.getLocation().end(); ++it) {
		std::cout << it->first << std::endl;
		std::cout << it->second.getRoot() << std::endl;
		std::cout << it->second.getIndex() << std::endl;
		std::cout << it->second.getRequestLimits() << std::endl;
		std::cout << it->second.getAutoIndex() << std::endl;
	}
	std::cout << "KEK:" << server.getHost() << std::endl;
	std::cout << "KEK:" << server.getPort() << std::endl;
	std::cout << "KEK:" << server.getServerName() << std::endl;
	std::cout << std::endl;
	return server;
}

std::string FileParser::getArgument(const std::string &dst, int start) {
	return ft_strtrim(dst.substr(start + 1, dst.length()), " \t");
}

bool FileParser::checkIndent(const std::string &str, int find, int pos) {
	int result = 0;
	for (int i = 0; i < find; ++i) {
		if (str[i] == ' ' || str[i] == '\t')
			result += (str[i] == ' ') ? 1 : 4;
		else return false;
	}
	return (result == 4 * pos);
}

void FileParser::_parseServerParam(std::vector<std::string> &config, size_t &index, VirtualServer &server) {
	while (config[index].find("location:") == std::string::npos && config[index].find("server:") == std::string::npos && !config[index].empty()) {
		if (config[index].find("host:", 0, 5) != std::string::npos)
			server.setHost(getArgument(config[index], ft_strchr(config[index], ':')));
		else if (config[index].find("port:", 0, 5) != std::string::npos)
			server.setPort(getArgument(config[index], ft_strchr(config[index], ':')));
		else if (config[index].find("server_name:", 0, 12) != std::string::npos)
			server.setServerName(getArgument(config[index], ft_strchr(config[index], ':')));
		else if (config[index].find("error_page:", 0, 11) != std::string::npos)
			server._error_page.push_back(getArgument(config[index], ft_strchr(config[index], ':')));
		else {
			for (int i = 0; i < config[index].length(); ++i)
				if (!(config[index][i] == ' ' || config[index][i] == '\t')) {
					std::cerr << "Error config parse" << std::endl;
					break;
				}
		}
		index++;
	}
}