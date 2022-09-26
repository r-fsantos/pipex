# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 10:34:51 by rfelicio          #+#    #+#              #
#    Updated: 2022/09/27 10:44:21 by rfelicio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= clang
CC_FLAGS	= -Wall -Wextra -Werror

LEAK_FLAGS	= -g3 -fsanitize=address

ifeq ($(shell uname), Linux)
	LEAK_FLAGS	= -g3
endif

FLAGS		= $(CC_FLAGS) $(LEAK_FLAGS)

HEADER_DIR	= ./includes
HEADERS		= -I $(HEADER_DIR)

SRC_DIR		=	./src
SRC			=	$(SRC_DIR)/main.c			\
				$(SRC_DIR)/ft_awk.c			\
				$(SRC_DIR)/ft_arg_parsers.c	\
				$(SRC_DIR)/ft_env.c			\
				$(SRC_DIR)/ft_error.c		\
				$(SRC_DIR)/ft_exec.c		\
				$(SRC_DIR)/ft_mem.c			\
				$(SRC_DIR)/ft_mem2.c		\
				$(SRC_DIR)/ft_parsers.c		\
				$(SRC_DIR)/ft_pipeline.c	\
				$(SRC_DIR)/ft_process.c		\
				$(SRC_DIR)/ft_putstr.c		\
				$(SRC_DIR)/ft_split.c		\
				$(SRC_DIR)/ft_split2.c		\
				$(SRC_DIR)/ft_str.c			\

OBJS_DIR		= ./obj
OBJS			= $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRC))

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $< -c -o $@ $(HEADERS)
	@echo

$(NAME): $(OBJS_DIR) $(OBJS)
	@echo "Linking..."
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(HEADERS)
	@echo

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@echo "Cleaning object files..."
	@echo
	@rm -rf $(OBJS_DIR)
	@echo "Finished cleaning object files"
	@echo

fclean: clean
	@echo "Cleaning executable file: $(NAME)"
	@rm -rf $(NAME)
	@echo

re: fclean all

.PHONY: all clean fclean re bonus
