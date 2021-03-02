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
	std::string		tmp_path;

	if (location) {
		tmp_path = std::string(request->getPath()).erase(0, it->first.size());
		if (tmp_path.find("/", 0, 1) != std::string::npos)
			tmp_path.erase(0, 1);
		path = location->getRoot() + tmp_path;
	}
	else
		path = "";
	if (stat((path.c_str()), &stat_info) == -1) // накидать стурктуру в которой будет значение файла, есть он или его нет, тем самым избавиться от проблемы в 15 тесте в PUT
		response->setStatusCode("404");
	else if (!(error = checkValidRequest(location, client, &stat_info)).empty()) {
		response->setStatusCode(error);
	} else {
		checkDirectoryOrFile(&stat_info, location, path);
		if (ft_compare(request->getMethod(), "POST"))
			handlePostReponse(client, location, &stat_info, path);
		if (ft_compare(request->getMethod(), "GET") || ft_compare(request->getMethod(), "HEAD"))
			handleDefaultResponse(client, location, &stat_info, path);
		else if (ft_compare(request->getMethod(), "PUT"))
			handlePutResponse(client, location, &stat_info, path);
	}
	std::cout << "METHOD: " << request->getMethod() << std::endl;
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

void WebServer::handlePutResponse(Client *client, Location *location, struct stat *stat_info,
								  std::string &path) {
	HTTPResponse*	response = client->getResponse();
	int 			fd = 0;
	int				tmp_fd = open(path.c_str(), O_RDONLY);

	if (response->getBodySize() < location->getRequestLimits())
		response->setStatusCode("413");
	if (S_ISDIR(stat_info->st_mode))
		response->setStatusCode("404");
	if ((fd = open(path.c_str(), O_RDONLY | O_CREAT | O_TRUNC, 0666)) < 0)
		response->setStatusCode("500");
	else {
		write(fd, response->getBody(), response->getBodySize());
		if (tmp_fd < 0)
			response->setStatusCode("200");
		else
			response->setStatusCode("201");
		close(fd);
		close(tmp_fd);
	}
}

void WebServer::handlePostReponse(Client *client, Location *location, struct stat *stat_info,
								  std::string &path) {
	HTTPResponse*	response = client->getResponse();
	int				fd = 0;

	if (response->getBodySize() < location->getRequestLimits())
		response->setStatusCode("413");
	if (S_ISDIR(stat_info->st_mode))
		response->setStatusCode("404");
	if ((fd = open(path.c_str(), O_RDONLY | O_CREAT | O_TRUNC, 0666)) < 0)
		response->setStatusCode("500");
	else {
		write(fd, response->getBody(), response->getBodySize());
		response->setStatusCode("200");
		close(fd);
	}
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
	int	flag = 0;

	if (S_ISDIR(info->st_mode)) {
		if (path.find("/", path.length() - 1, 1) != std::string::npos) {
			flag = 1;
			fd = open((path + location->getIndex()).c_str(), O_RDONLY);
		}
		else {
			flag = 2;
			fd = open((path + "/" + location->getIndex()).c_str(), O_RDONLY);
		}
		if (fd > 0) {
			if (flag == 1)
				path = path + location->getIndex();
			if (flag == 2)
				path = path + "/" + location->getIndex();
			stat(path.c_str(), info);
			close(fd);
		}
	}
}

std::pair<char *, int> WebServer::generateAutoindex(HTTPRequest *request, const std::string& path) {
	std::string 	autoindex;
	char*			tmp = NULL;
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
	tmp = ft_strdup(autoindex.c_str());
	return std::make_pair(tmp, autoindex.size());
}