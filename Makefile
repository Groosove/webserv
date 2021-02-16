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
SRC = 		src/main.cpp
OBJPATH = 	obj/
CC = 		clang++
CFLAGS = 	-Wall -Wextra -Werror
OBJ = 		$(addprefix $(OBJPATH),$(SRC:.cpp=.o))
HEADER =    	includes/something.hpp

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

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	@echo "$(GREEN)Success$(TEXT_RESET)"

$(OBJPATH)%.o: %.cpp
	@test -d $(OBJPATH) || mkdir $(OBJPATH)
	@echo "$(CYAN)Compiling $<"
	@$(CC) -c $< -o $@

clean:
	@/bin/rm -rf $(OBJPATH)
fclean: clean
	@/bin/rm -f $(NAME)
re: fclean all

