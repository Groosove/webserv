//
// Created on 2/23/21 by
// Shonna Jakku
// Fenix Lavon
// Freely Kathryn
//

#include "WebServer.hpp"

void WebServer::treatmentStageGenerate(Client *client) {
	VirtualServer*	virtual_server = searchVirtualServer(client);
	std::map<std::string, Location>::iterator it = virtual_server->findLocation(client->getRequest());
	Location*		location = &it->second;
	HTTPResponse*	response = client->getResponse();
	HTTPRequest*	request = client->getRequest();
	std::string 	error;
	struct stat		stat_info;
	std::string		path;

	if (location)
		path = location->getRoot() + std::string(request->getPath()).erase(0, it->first.size());
	else
		path = "";
	if (!(error = checkValidRequest(location, client, &stat_info)).empty()) {
		response->setStatusCode(error);
	} else {
		stat((path.c_str()), &stat_info);
		checkDirectoryOrFile(&stat_info, location, path);
		if (ft_compare(request->getMethod(), "GET") || ft_compare(request->getMethod(), "HEAD"))
			handleDefaultResponse(client, location, &stat_info, path);
		else if (ft_compare(request->getMethod(), "PUT"))
			nullptr;
//			handlePutRequest(client, location, &stat_info);
	}
	response->generateResponse();
	client->setResponseBuffer(response->getResponse(), response->getBodySize());
	client->setStage(send_response);
}

std::string WebServer::checkValidRequest(Location *location, Client *client,
												 struct stat *info) {
	if (!location)
		return std::string("404");
	else if (!location->checkAllowMethod(client->getRequest()->getMethod()))
		return std::string("405");
	else if (ft_strlen(client->getRequest()->getBody()) > location->getRequestLimits())
		return std::string("413");
	return std::string("");
}

void WebServer::handleDefaultResponse(Client *client, Location *location, struct stat *stat_info, std::string& path) {
	HTTPRequest*	request = client->getRequest();
	HTTPResponse*	response = client->getResponse();

	response->setStatusCode("200");
	if (S_ISLNK(stat_info->st_mode) || S_ISREG(stat_info->st_mode)) {
		if (ft_compare(request->getMethod(), "GET"))
			response->setBody(readBodyResponse(path));
	}
	else if (S_ISDIR(stat_info->st_mode) && !location->getAutoIndex())
		response->setStatusCode("404");
	else if (S_ISDIR(stat_info->st_mode) && ft_compare(request->getMethod(), "GET") && location->getAutoIndex())
		response->setBody(generateAutoindex(request, path));
}

std::pair<char *, int> WebServer::readBodyResponse(const std::string& path) {
	int 		fd;
	char		buf[40000];
	char*		index_html = ft_strdup("");
	int			bytes;
	int			size = 0;

	if (!(fd = open(path.c_str(), O_RDONLY)))
		std::cerr << "File not open" << std::endl;
	while ((bytes = read(fd, &buf, 40000)) > 0) {
		buf[bytes] = '\0';
		index_html = (char *)ft_memjoin(index_html, buf, size, bytes);
	}
	return std::make_pair(index_html, size);
}

void WebServer::checkDirectoryOrFile(struct stat *info, Location *location, std::string& path) {
	int fd = 0;
	if (S_ISDIR(info->st_mode) &&
		(fd = open((path + location->getIndex()).c_str(), O_RDONLY))) {
		path = path + location->getIndex();
		stat(path.c_str(), info);
		close(fd);
	}
}

std::pair<char *, int> WebServer::generateAutoindex(HTTPRequest *request, const std::string& path) {
	std::string 	autoindex;
	DIR*			directory = opendir(path.c_str());
	struct dirent*	entry = nullptr;

	if (directory) {
		autoindex.append("<html><head><title>Index of </title></head><body><h1>Index of </h1><br><hr><a href=\"../\">../</a><br>");
		while ((entry = readdir(directory)) != nullptr) {
			autoindex.append("<a href=\"" + std::string(entry->d_name) + "\">"
							+ std::string(entry->d_name) + "</a><br>");
		}
		autoindex.append("</body></html>");
	}
	return std::make_pair((char *)autoindex.c_str(), autoindex.size());
}