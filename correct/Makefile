# COLORS #
GREEN = @echo "\033[0;32m"
BLUE = @echo "\033[0;34m" 
PURPLE = @echo "\033[0;35m"
CYAN = @echo "\033[0;36m"
RESET = "\033[1;0m"

# VARIABLES #
NAME = so_long
LIBFT_NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3
CFLAGS += -I ./$(INC_PATH) -I ./$(LIBFT_PATH)
MINILIBX = -lmlx -framework OpenGL -framework AppKit

# PATHs #
LIBFT_PATH  = srcs/libft
MAP_PATH  = srcs/map
GAME_PATH  = srcs/game
ENEMY_PATH = srcs/enemy
INC_PATH    = includes
SRC_PATH    = srcs
OBJ_PATH    = objects

# SOURCES #
SRC =   main.c

SRC_GAME = game_mechanics.c image_control.c start_game.c free_data.c events.c coins.c

SRC_MAP = mapreader.c mapcheck.c get_file_height.c

SRC_ENEMYS = enemy.c enemy_path_new_patrol.c


# RULES #
all: $(NAME)

OBJ_NAME = $(SRC:%.c=%.o)
OBJ_GAMES = $(SRC_GAME:%.c=%.o)
OBJ_MAPS = $(SRC_MAP:%.c=%.o)
OBJ_ENEMYS = $(SRC_ENEMYS:%.c=%.o)

SRCS = $(addprefix $(SRC_PATH)/, $(SRC))
SRCS_GAMES = $(addprefix $(GAME_PATH)/, $(SRC))
SRCS_MAP = $(addprefix $(MAP_PATH)/, $(SRC))
SRCS_ENEMY = $(addprefix $(ENEMY_PATH)/, $(SRC))

OBJS =  $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
OBJS_GAMES =  $(addprefix $(OBJ_PATH)/, $(OBJ_GAMES))
OBJS_MAPS =  $(addprefix $(OBJ_PATH)/, $(OBJ_MAPS))
OBJS_ENEMYS =  $(addprefix $(OBJ_PATH)/, $(OBJ_ENEMYS))

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH) 2> /dev/null

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(GAME_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(MAP_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(ENEMY_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@
            
$(NAME): $(OBJS) $(OBJS_MAPS) $(OBJS_ENEMYS) $(OBJS_GAMES) | $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(OBJS_MAPS) $(OBJS_ENEMYS) $(OBJS_GAMES) $(OBJS) $(MINILIBX) -o $(NAME) $(addprefix $(LIBFT_PATH)/, $(LIBFT_NAME))

$(LIBFT_NAME):
	make -sC $(LIBFT_PATH)

##RULES
$(MAKE): make

norminette:
	norminette $(SRCS)
	norminette $(LIBFT_PATH)
	norminette $(MAP_PATH)
	norminette $(GAME_PATH)

clean:
	$(PURPLE) CLEANING OBJECTS $(RESET)
	rm -rf $(OBJ_PATH)
#rm -rf $(OBJS)
#rm -rf $(OBJS_GAMES)
#rm -rf $(OBJS_MAPS)
	
fclean: clean
	$(PURPLE) CLEANING DIRECTORY AND EXEC $(RESET)
	rm -rf $(NAME)
	rm -rf $(OBJ_PATH)
	make fclean -sC $(LIBFT_PATH)

re: fclean all

PHONY.: all clean fclean re norminette
