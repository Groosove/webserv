//
// Created by Fenix Lavon on 2/11/21.
// Copyright (c) 2021 All rights reserved.
//

#include <FileParser.hpp>

FileParser::FileParser(std::vector<std::string> config) {
	size_t size = config.size();

	for (size_t i = 0; i < size;) {
		if (config[i].find("server:") != std::string::npos && checkIndent(config[i], 0))
			_server.push_back(parseConfigFile(config, ++i));
	};
}

VirtualServer FileParser::parseConfigFile(std::vector<std::string> config, size_t &index) {
	VirtualServer server;
	size_t size = config.size();
	_parseServerParam(config, index, server);
	for (size_t i = index; i < size; ++i) {
		if (config[i].find("location:") != std::string::npos && checkIndent(config[i], 1))
			_parseLocationParam(config, i, server); // TODO Если директория без слеша, то нужно дополнять!
		else if (config[i].empty()) continue;
		else { std::cerr << "Error parse config file" << std::endl; break; }
		index = i;
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

std::string FileParser::getArgument(const std::string &dst, int start) { return ft_strtrim(dst.substr(start + 1, dst.length()), " \t"); }

bool FileParser::checkIndent(const std::string &str, int pos) {
	int result = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == ' ' || str[i] == '\t')
			result += (str[i] == ' ') ? 1 : 4;
		else break;
	}
	return (result == 4 * pos);
}

void FileParser::_parseServerParam(std::vector<std::string> &config, size_t &index, VirtualServer &server) {
	while (config[index].find("location:") == std::string::npos && config[index].find("server:") == std::string::npos) {
		if (config[index].find("host:", 0, 5) != std::string::npos)
			server.setHost(getArgument(config[index], ft_strchr(config[index], ':')));
		else if (config[index].find("port:", 0, 5) != std::string::npos)
			server.setPort(getArgument(config[index], ft_strchr(config[index], ':')));
		else if (config[index].find("server_name:", 0, 12) != std::string::npos)
			server.setServerName(getArgument(config[index], ft_strchr(config[index], ':')));
		else if (config[index].find("error_page:", 0, 11) != std::string::npos)
			server.setErrorPage(getArgument(config[index], ft_strchr(config[index], ':')));
		else if (config[index].empty()) { ++index; continue; }
		if (!checkIndent(config[index], 1)) { std::cerr << "Error parse config file" << std::endl; break; }
		index++;
	}
}

void FileParser::_parseLocationParam(std::vector<std::string> &config, size_t &i, VirtualServer &server) {
	Location location;
	std::string path = getArgument(config[i], ft_strchr(config[i], ':'));
	++i;
	while (config[i].find("location:") == std::string::npos && config[i].find("server:") == std::string::npos && i < config.size()) {
		if ((config[i].find("root:", 0, 5)) != std::string::npos)
			location.setRoot(getArgument(config[i], ft_strchr(config[i], ':')));
		else if ((config[i].find("index:", 0, 6)) != std::string::npos)
			location.setIndex(getArgument(config[i], ft_strchr(config[i], ':')));
		else if ((config[i].find("allow_methods:", 0, 14)) != std::string::npos)
			location.setAllowMethods(getArgument(config[i], ft_strchr(config[i], ':')));
		else if ((config[i].find("autoindex:", 0, 10)) != std::string::npos)
			location.setAutoIndex(getArgument(config[i], ft_strchr(config[i], ':')));
		else if ((config[i].find("limits_client_body_size", 0, 24)) !=  std::string::npos)
			location.setRequestLimits(getArgument(config[i], ft_strchr(config[i], ':')));
		else if (config[i].empty()) { ++i; continue; }
		if (!checkIndent(config[i], 2)) { std::cerr << "Error parse config file" << std::endl; break; }
		++i;
	}
	if (config[i].find("location:") != std::string::npos)
		--i;
	server.getLocation()[path] = location;
}