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
	HTTPRequest*	request = client->getRequest();
	std::string 	error;
	struct stat		stat_info;

	stat((location->getRoot()).c_str(), &stat_info);
	if (!(error = checkValidRequest(location, client, &stat_info)).empty()) {
		response->setStatusCode(error);
	}
	else {
		checkDirectoryOrFile(&stat_info, location);
		if (ft_compare(request->getMethod(), "GET") || ft_compare(request->getMethod(), "HEAD"))
			handleDefaultResponse(client, location, &stat_info);
		else if (ft_compare(request->getMethod(), "PUT"))
			nullptr;
//			handlePutRequest(client, location, &stat_info);
	}
	response->generateResponse();
	client->setResponseBuffer(response->getResponse());
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

void WebServer::handleDefaultResponse(Client *client, Location *location, struct stat *stat_info) {
	HTTPRequest*	request = client->getRequest();
	HTTPResponse*	response = client->getResponse();

	response->setStatusCode("200");
	if (S_ISLNK(stat_info->st_mode) || S_ISREG(stat_info->st_mode)) {
		if (ft_compare(request->getMethod(), "GET"))
			response->setBody(readBodyResponse(location->getRoot(), location->getIndex()));
	}
	else if (S_ISDIR(stat_info->st_mode) && !location->getAutoIndex())
		response->setStatusCode("404");
	else if (S_ISDIR(stat_info->st_mode) && ft_compare(request->getMethod(), "GET") && location->getAutoIndex())
		response->setBody(generateAutoindex(request, location->getIndex(), location->getRoot()));
}

char* WebServer::readBodyResponse(const std::string& root, const std::string& file) {
	int 		fd;
	char*		buf;
	std::string	index_html;

	if (!(fd = open((root + file).c_str(), O_RDONLY)))
		std::cerr << "File not open" << std::endl;
	while (get_next_line(fd, &buf))
		index_html.append(buf);
	return (char*)index_html.c_str();
}

void WebServer::checkDirectoryOrFile(struct stat *info, Location *location) {
	int fd = 0;
	if (S_ISDIR(info->st_mode) &&
		(fd = open((location->getRoot() + location->getIndex()).c_str(), O_RDONLY))) {
		stat((location->getRoot() + location->getIndex()).c_str(), info);
		close(fd);
	}
}

std::string WebServer::generateAutoindex(HTTPRequest *request, const std::string &index,
												 const std::string &root_dir) {
	std::string 	autoindex;
	DIR*			directory = opendir(root_dir.c_str());
	struct dirent*	entry = nullptr;

	if (directory) {
		autoindex.append("<html><head><title>Index of " + index + "</title></head><body>" +
		"<h1>Index of " + index + "</h1><br><hr><a href=\"../\">../</a><br>");
		while ((entry = readdir(directory)) != nullptr) {
			autoindex.append("<a href=\"" + std::string(entry->d_name) + "\">"
							+ std::string(entry->d_name) + "</a><br>");
		}
		autoindex.append("</body></html>");
	}
	return autoindex;
}