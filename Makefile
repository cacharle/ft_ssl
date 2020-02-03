# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 20:14:50 by cacharle          #+#    #+#              #
#    Updated: 2020/02/03 20:31:02 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = rm -f
MAKE = make

LIBFT_DIR = libft
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj

CC = gcc
CCFLAGS = -Wall -Wextra #-Werror
LDFLAGS = -L$(LIBFT_DIR) -lft

INCLUDE = $(shell find $(INCLUDE_DIR) -type f -name "*.h")
SRC = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = ft_ssl

all: prebuild libft_all $(NAME)

prebuild:
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi

$(NAME): $(OBJ)
	@echo "Linking: $@"
	@$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)/%.c $(INCLUDE)
	@echo "Compiling: $@"
	@$(CC) $(CCFLAGS) -c -o $@ $<

clean: libft_fclean
	@echo "Removing objects"
	@$(RM) $(OBJ)

fclean: clean
	@echo "Removing $(NAME)"
	@$(RM) $(NAME)

re: fclean all

libft_all:
	$(MAKE) $(MAKE_ARGS) -C $(LIBFT_DIR) all

libft_fclean:
	$(MAKE) $(MAKE_ARGS) -C $(LIBFT_DIR) fclean

