# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 10:34:51 by rfelicio          #+#    #+#              #
#    Updated: 2022/08/23 10:46:09 by rfelicio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= clang
CC_FLAGS	= -Wall -Wextra -Werror

LEAK_FLAGS	= -g3 -fsanitize=address

ifeq ($(shell uname), Linux)
	LEAK_FLAGS	=
endif

FLAGS		= $(CC_FLAGS) $(LEAK_FLAGS)

HEADER_DIR	= ./includes
HEADERS		= -I $(HEADER_DIR)

SRC_DIR		= ./src
SRC			= $(SRC_DIR)/main.c

OBJ_DIR		= ./obj
OBJ_DIR		= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(FLAGS) $< -c -o $@ $(HEADERS)
	@echo

.PHONY: all clean fclean re bonus