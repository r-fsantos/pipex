# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 10:34:51 by rfelicio          #+#    #+#              #
#    Updated: 2022/09/19 09:31:46 by rfelicio         ###   ########.fr        #
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
