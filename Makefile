# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamighi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 11:14:33 by tamighi           #+#    #+#              #
#    Updated: 2022/04/18 11:01:58 by tamighi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STD_NAME = std_cont
FT_NAME = ft_cont
CC = c++
FLAGS = -Wall -Werror -Wextra -pedantic -std=c++11

OBJ_DIR = objs/

FILES = main.cpp
F_DIR = ./

SRCS = $(addprefix $(F_DIR), $(FILES))

STD_OBJS = $(addprefix $(OBJ_DIR), $(addprefix std_, $(FILES:.cpp=.o)))
FT_OBJS = $(addprefix $(OBJ_DIR), $(addprefix ft_, $(FILES:.cpp=.o)))

RM = rm -rf

all: $(STD_NAME) $(FT_NAME)

$(OBJ_DIR)std_%.o: $(F_DIR)%.cpp 
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -o $@ -c $< -D NAMESPACE=std

$(OBJ_DIR)ft_%.o: $(F_DIR)%.cpp 
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -o $@ -c $< -D NAMESPACE=ft

$(STD_NAME): $(STD_OBJS)
	$(CC) -o $(STD_NAME) $(STD_OBJS)

$(FT_NAME): $(FT_OBJS)
	$(CC) -o $(FT_NAME) $(FT_OBJS)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(FT_NAME) $(STD_NAME)

re: fclean all

.PHONY: all re clean fclean
