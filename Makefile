# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamighi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 11:14:33 by tamighi           #+#    #+#              #
#    Updated: 2022/04/15 11:43:05 by tamighi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test
CC = c++
FLAGS = -Wall -Werror -Wextra -pedantic -std=c++98

OBJ_DIR = objs/

FILES = mvector.cpp
F_DIR = ./
HEADERS = iterator_traits.hpp map.hpp
H_DIR = containers/

SRCS = $(addprefix $(F_DIR), $(FILES))
INCLUDES = $(addprefix $(H_DIR), $(HEADERS))

OBJS = $(addprefix $(OBJ_DIR), $(FILES:.cpp=.o))

RM = rm -rf

all: $(NAME)

$(OBJ_DIR)%.o: $(F_DIR)%.cpp $(INCLUDES) 
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
