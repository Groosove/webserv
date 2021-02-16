//
// Created on 2/5/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//  Copyright (c) 2021 RaevkaTuliskiyPryanikNogotochki All rights reserved.
//

#include "Location.hpp"
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include "utils.hpp"

bool			ft_getline(int fd, std::string &line) {
	static std::string	surplus = std::string();
	char				buffer[513];
	size_t 				bytes;

	if (surplus.empty()) {
		while ((bytes = read(fd, buffer, 512)) > 0) {
			buffer[bytes] = '\0';
			surplus.append(buffer);
		}
		if (!bytes && surplus.empty()) {
			return (false);
		}
	}
	std::string::size_type pos = surplus.find('\n');
	if (pos == std::string::npos) {
		line = surplus;
		surplus.clear();
	}
	else {
		line = surplus.substr(0, pos);
		surplus = surplus.substr(pos + 1);
	}
	return (true);
}

void Location::setRequestLimits(const std::string &body_size) {
	_request_limits = std::stoi(ft_strtrim(body_size, " \t"));
}

void Location::setAutoIndex(const std::string &autoindex) {
	if (autoindex.find("on", 0) != std::string::npos)
		_autoindex = true;
	if (autoindex.find("off", 0) != std::string::npos)
		_autoindex = false;
}

void Location::setRoot(const std::string &root) {
	_root = ft_strtrim(root, " \t");
}

void Location::setIndex(const std::string &index) {
	_index =  ft_strtrim(index, " \t");
}

void Location::setAllowMethods(const std::string &allow_methods) {
	_allow_methods.insert(_allow_methods.begin(),ft_strtrim(allow_methods, " \t"));
}

bool Location::validationLocation(const char* method) {
	std::vector<std::string>::iterator begin = _allow_methods.begin();
	while (begin != _allow_methods.end()) { // проверка доступности метода
		if ((*begin).find(method) != std::string::npos)
			break;
		else if (begin == _allow_methods.end() - 1 && (*begin).find(method) == std::string::npos)
			return false;
		begin++;
	}
	if (!tryOpenDir())
		return false;
	if (!tryOpenFile())
		return false;
	return true;
}

bool Location::tryOpenDir() {
	DIR*			directory = opendir(_root.c_str()); // возможно стоит проверить директория ли это или нет через stat(_root, &dir); if (S_ISDIR(dir.st_mode));
	struct dirent*	entry = nullptr;

	if (directory) { // директория открылась или нет
		while ((entry = readdir(directory)) != nullptr) { // бегаем по файлам директории пока они не закончатся
			if (std::string(entry->d_name).find(_index) != std::string::npos) { // проверяем есть ли файал который мы ищем в этой директории
				closedir(directory);
				return true;
			}
		}
	}
	closedir(directory);
	return false;
}

bool Location::tryOpenFile() {
	struct stat file;

	stat((_root + _index).c_str(), &file);
	if (S_ISREG(file.st_mode)) { // проверка на то что это файл
		if (file.st_mode & S_IRUSR) // проверка на что что этот файл доступен для чтения
			return true;
	}
	return false;
}
