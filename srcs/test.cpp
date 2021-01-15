#include <iostream>
#include <map>
#include <iterator>
#include <string>


char*       parse_request_http(int fd, const char* buff) {
	size_t  pos = 0;
	std::string line;
	std::map<std::string, std::string> map;

	std::map<std::string, std::string>::iterator it_b;
	std::map<std::string, std::string>::iterator it_e;

	std::pair<std::string, std::string> pair;

	while (buff[pos] != '\0') {
		if (buff[pos] == ':') {
			map[std::string(buff, pos)] = std::string(&buff[pos]);
		}
		++pos;
	}
	it_b = map.begin();
	pair = *it_b;
	std::cout << pair.first << " " << pair.second << std::endl;
	return NULL;
}

int     main() {
	const   char    hello[] = "Hello: World!\n";
//	std::cout << hello << std::endl;
	parse_request_http(1, hello);
	return 0;
}
//	size_t pos = 0;
//	std::string buffer = std::string(buff), line;
//	std::map <std::string, std::string> map;
//	while (std::getline(buffer, line)) {
//		if ((pos = line.find(":")) != std::npos)
//			map.insert(part<std::string, std::string>(std::string(line, pos),
//			                                          std::string(line[pos])));
//		std::cout << map[std::string(linem pos)] << std::endl;
//	}
