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

	const std::vector<VirtualServer> &getServer() const { return _server; }
private:
	std::vector<VirtualServer> _server;
	static VirtualServer 	parseConfigFile(std::vector<std::string> config, size_t &index);
	static void 			_parseServerParam(std::vector<std::string> &config, size_t &index, VirtualServer &server);
	static void 			_parseLocationParam(std::vector<std::string> &config, size_t &index, VirtualServer &server);
	static std::string getArgument(const std::string &dst, int start);

	static bool checkIndent(const std::string &str, int pos);
};

