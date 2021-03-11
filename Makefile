# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjakku <sjakku@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/29 14:36:51 by sjakku            #+#    #+#              #
#    Updated: 2020/12/31 04:31:23 by sjakku           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		WebServer
VPATH       = includes:utils_function:utils_function/get_next_line:srcs
SRC = 		CGI.cpp \
            main.cpp \
            Client.cpp \
            FileParser.cpp \
            HTTPRequest.cpp \
            HTTPResponse.cpp \
            Location.cpp \
            VirtualServer.cpp \
            WebServer.cpp \
            WebServer_generateResponse.cpp \
            ft_atoi.cpp \
            ft_compare.cpp \
            ft_current_data.cpp \
            ft_erase.cpp \
            ft_find.cpp \
            ft_memcpy.cpp \
            ft_memjoin.cpp \
            ft_parse_spaces.cpp \
            ft_split.cpp \
            ft_strchr.cpp \
            ft_strdup.cpp \
            ft_strjoin.cpp \
            ft_strlen.cpp \
            ft_strstr.cpp \
            ft_strtrim.cpp \
            ft_substr.cpp \
            get_next_line.cpp \
            get_next_line_utils.cpp


OBJPATH = 	obj/
CC = 		clang++
HEADER_FLAGS    =  -Wall -Wextra -Werror -I./includes/ -I./utils_function/ -I./utils_function/get_next_line/
CFLAGS          = $(HEADER_FLAGS)
OBJ = 		$(addprefix $(OBJPATH),$(SRC:.cpp=.o))
HEADERS      = CGI.hpp \
               Client.hpp \
               FileParser.hpp \
               HTTPRequest.hpp \
               HTTPResponse.hpp \
               Location.hpp \
               VirtualServer.hpp \
               get_next_line.hpp \
               utils.hpp \
               WebServer.hpp

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
UNDERLINE = \033[0;4m
TEXT_RESET = \033[0;0m

.PHONY: 	all re fclean clean %.obj

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Success$(TEXT_RESET)"

$(OBJPATH)%.o: %.cpp $(HEADER)
	@test -d $(OBJPATH) || mkdir $(OBJPATH)
	@echo "$(CYAN)Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@/bin/rm -rf $(OBJPATH)
fclean: clean
	@/bin/rm -f $(NAME)
re: fclean all

