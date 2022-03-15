# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 23:59:04 by ldurante          #+#    #+#              #
#    Updated: 2022/03/15 19:02:35 by ldurante         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLE DECLARATIONS #

NAME = cub3D
CC = gcc
RM = rm -f
MAKE = make
DEBUG = -g3 -fsanitize=address
CFLAGS = -g3 -Wall -Werror -Wextra $(KEYCODES)
UNAME = $(shell uname -s)

# Properties for compiling in MacOS
MLX_LINK = -lmlx -framework OpenGL -framework AppKit
ESC = KEY_ESC=53
W = KEY_W=13
A = KEY_A=0
S = KEY_S=1
D = KEY_D=2
UP = KEY_UP=126
DOWN = KEY_DOWN=125
LEFT = KEY_LEFT=123
RIGHT = KEY_RIGHT=124

# Propierties for compiling in Linux
ifeq ($(UNAME), Linux)
	MLX_LINK = -lmlx -lXext -lX11 -lm
	ESC = KEY_ESC=65307
	W = KEY_W=119
	A = KEY_A=97
	S = KEY_S=115
	D = KEY_D=100
	UP = KEY_UP=65362
	DOWN = KEY_DOWN=65364
	LEFT = KEY_LEFT=65361
	RIGHT = KEY_RIGHT=65363
endif

# Define Keycodes depending on OS
KEYCODES =  -D $(ESC) -D $(W) -D $(A) -D $(S) -D $(D) -D $(UP) -D $(DOWN) -D $(LEFT) -D $(RIGHT)

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
		srcs/file_management/check_map_surrounding.c \
		srcs/utils.c \
		srcs/input.c \
		srcs/player.c \
		srcs/background.c \
		srcs/cube.c \
		srcs/raycast.c \
		srcs/minimap.c \

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
	./cub3D maps/map0$${map}.cub

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
