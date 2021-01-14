cmake_minimum_required(VERSION 3.17.3)
project(WebServ)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

set(FILES
        srcs/main.cpp)
add_executable(WebServ ${FILES})