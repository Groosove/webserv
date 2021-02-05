cmake_minimum_required(VERSION 3.17.3)
project(WebServ)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

include_directories(
        includes
        srcs/
        .)

#set(INCLUDES
#        includes/WebServer.hpp
#        includes/VirtualServer.hpp
#        includes/Location.hpp
#        includes/HTTPResponse.hpp
#        includes/HTTPRequest.hpp
#        includes/Client.hpp
#        includes/CGI.hpp)

set(FILES
        main.cpp
        srcs/WebServer.cpp
        srcs/VirtualServer.cpp
        srcs/Location.cpp
        srcs/HTTPRequest.cpp
        srcs/HTTPResponse.cpp
        srcs/Client.cpp
        srcs/CGI.cpp)

add_executable(WebServ ${FILES} )