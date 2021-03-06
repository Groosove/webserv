cmake_minimum_required(VERSION 3.17.3)
project(WebServ)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(
		utils_function/
		includes/
		srcs/
		utils_function/get_next_line
		.)

set(UTILS
		utils_function/ft_strtrim.cpp
		utils_function/ft_strchr.cpp
		utils_function/ft_compare.cpp
		utils_function/ft_parse_spaces.cpp
		utils_function/ft_split.cpp
		utils_function/ft_substr.cpp
		utils_function/ft_strlen.cpp
		utils_function/ft_strdup.cpp
		utils_function/ft_strjoin.cpp
		utils_function/get_next_line/get_next_line.cpp
		utils_function/get_next_line/get_next_line_utils.cpp
		utils_function/ft_atoi.cpp
		utils_function/ft_find.cpp
		utils_function/ft_memcpy.cpp
		utils_function/ft_memjoin.cpp
		utils_function/ft_erase.cpp
		)

set(FILES
		main.cpp
		srcs/WebServer.cpp
		srcs/WebServer_generateResponse.cpp
		srcs/VirtualServer.cpp
		srcs/Location.cpp
		srcs/HTTPRequest.cpp
		srcs/HTTPResponse.cpp
		srcs/Client.cpp
		srcs/FileParser.cpp
		srcs/CGI.cpp
		utils_function/ft_strstr.cpp)

add_executable(WebServ ${UTILS} ${FILES} )