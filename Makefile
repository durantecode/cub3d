# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 23:59:04 by ldurante          #+#    #+#              #
#    Updated: 2022/02/16 17:47:26 by ldurante         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE DECLARATIONS #

NAME = cub3D
CC = gcc
RM = rm -f
MAKE = make
CFLAGS = -Wall -Werror -Wextra
DEBUG = -g3 -fsanitize=address

UNAME = $(shell uname -s)

# Properties for MacOS
MLX_LINK = -lmlx -framework OpenGL -framework AppKit
ifeq ($(UNAME), Linux)

# Properties for Linux
MLX_LINK = -lmlx -lXext -lX11
endif

# COLORS #
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
GREY = \033[2;37m
MAGENTA = \033[0;35m
CURSIVE = \033[3m
NO_COLOR = \033[0m

# SOURCES & OBJECTS #
SRCS =	srcs/main.c \
		srcs/file_management/read_file.c \
		srcs/file_management/parse_data.c \
		srcs/file_management/check_data.c \
		srcs/file_management/get_map.c \
		srcs/file_management/check_map.c \
		srcs/file_management/load_files.c \
		srcs/utils/utils.c

OBJS = $(SRCS:.c=.o)

# RULES #
all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s all -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LINK) libft/libft.a -o $(NAME)
	@echo "$(GREY) cub3d compiled $(GREEN) ✔✔✔ $(NO_COLOR)"

test: all
	@echo "$(YELLOW) **** RUN TEST CUB3D **** $(NO_COLOR)"
	@read -p "Select map number: " map; \
	./cub3d maps/map0$${map}.cub

clean:
	@clear
	@$(RM) $(OBJS)
	@$(MAKE) clean -C libft
	@echo "$(RED) **** object files removed **** $(NO_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) libft/libft.a
	@echo "$(RED) **** cub3d removed **** $(NO_COLOR)"

re: fclean all

.PHONY: all re clean fclean

.SILENT: $(OBJS)
