//
// Created by Fenix Lavon on 2/11/21.
// Copyright (c) 2021 All rights reserved.
//

#pragma once

#include "VirtualServer.hpp"
class FileParser {
public:
	explicit FileParser(std::vector<std::string> vector);
	~FileParser() {};

	VirtualServer parseConfigFile(std::vector<std::string> config, size_t &index);
	void _parseServerParam(std::vector<std::string> &config, size_t &index, VirtualServer &server);
	const std::vector<VirtualServer> &getServer() const { return _server; }
	std::string getArgument(const std::string &dst, int start);

	bool checkIndent(const std::string &str, int find, int pos);
private:
	std::vector<VirtualServer> _server;
};

