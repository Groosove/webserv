//
// Created on 2/23/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//

#include "WebServer.hpp"

void WebServer::treatmentStageGenerate(Client *client) {
	VirtualServer*	virtual_server = searchVirtualServer(client);
	Location*		location = virtual_server->findLocation(client->getRequest());
	HTTPResponse*	response = client->getResponse();
	std::string 	error;
	struct stat		stat_info;

	stat(location->getRoot().c_str(), &stat_info);
	if (tryOpenDir(location)) {
		if (S_ISDIR(stat_info.st_mode) && tryOpenFile(location))
			stat((location->getRoot() + location->getIndex()).c_str(), &stat_info);
		if (request->getMethod() == "GET" || request->getMethod() == "HEAD")
			handleGetHeadMethods(client, location, &stat_info);
	}
	else {
		response->setStatusCode("404");
	}
	response->generateResponse(response->getStatusCode());
	client->setStage(send_response);
}

void WebServer::handleGetHeadMethods(Client *client, Location *location, struct stat *stat_info) {
	HTTPRequest*	request = client->getRequest();
	HTTPResponse*	response = client->getResponse();
	int				fd;
	char*			buf;

	response->setStatusCode("200");
	for (std::vector<std::string>::iterator it = location->getAllowMethods().begin(); it != location->getAllowMethods().end(); ++it) { // проверка на доступные методы
		if ((*it).find(request->getMethod()) != std::string::npos)
			break;
		else if (it == location->getAllowMethods().end() - 1 && (*it).find(request->getMethod()) == std::string::npos)
			response->setStatusCode("405");
	}
	if (S_ISREG(stat_info->st_mode) || S_ISLNK(stat_info->st_mode)) { // проверка на то что это либо файл, лио лин на файл
		if (fd = open((location->getRoot() + location->getIndex()).c_str(), O_RDONLY) && request->getMethod() == "GET") { // считааем этот файл если он есть и если метод GET, тк в нем есть body
			while (get_next_line(fd, &buf))
				response->setBody(std::string(buf));
		}
		else
			std::cout << "File doesn`t open" << std::endl;
	}
	else if (S_ISDIR(stat_info->st_mode) && !location->getAutoIndex()) // если это папка и нет автоиндекса, то 404, та же проверка, что и предыдущая, только на то что могут запросить директорию
		response->setStatusCode("404");
	else if (S_ISDIR(stat_info->st_mode) && location->getAutoIndex() && request->getMethod() == "GET") // если папка и директория, генерируем автоиндекс
		response->setBody(generateAutoindex(request, location->getIndex(), location->getRoot()));
}

bool WebServer::tryOpenDir(Location* location) {
	DIR*			directory = opendir(location->getRoot().c_str()); // возможно стоит проверить директория ли это или нет через stat(_root, &dir); if (S_ISDIR(dir.st_mode));
	struct dirent*	entry = nullptr;

	if (directory) { // директория открылась или нет
		while ((entry = readdir(directory)) != nullptr) { // бегаем по файлам директории пока они не закончатся
			if (std::string(entry->d_name).find(location->getIndex()) != std::string::npos) { // проверяем есть ли файал который мы ищем в этой директории
				closedir(directory);
				return true;
			}
		}
	}
	closedir(directory);
	return false;
}

bool WebServer::tryOpenFile(Location* location) {
	struct stat file;

	stat((location->getRoot() + location->getIndex()).c_str(), &file);
	if (S_ISREG(file.st_mode)) { // проверка на то что это файл
		if (file.st_mode & S_IRUSR) // проверка на что что этот файл доступен для чтения
			return true;
	}
	return false;
}

const std::string &WebServer::generateAutoindex(HTTPRequest *request, const std::string &index,
												const std::string &root_dir) {
	std::string		body_response;
	DIR*			directory = opendir(root_dir.c_str()); // возможно стоит проверить директория ли это или нет через stat(_root, &dir); if (S_ISDIR(dir.st_mode));
	struct dirent*	entry = nullptr;
	struct stat file;

	if (directory) {
		body_response.append("<html><head><title>Index of " + index + "</title></head><body>" +
							 "<h1> Index of " + index + "</h1><pre><a href=\"../\">../</a><br>");
		while ((entry = readdir(directory)) != nullptr) {
			std::string current_file(entry->d_name);
			stat((root_dir + index).c_str(), &file);
			if (entry->d_type == 4)
				current_file.append("/");
			body_response.append("<a href=\"" + current_file + "\">" + current_file + "</a><br>");
		}
	}
	body_response.append("</pre><hr></body></html>");
	return body_response;
}
