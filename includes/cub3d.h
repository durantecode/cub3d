/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:56:54 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/16 11:22:08 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "keycodes.h"
# include <mlx.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <math.h>

/* WINDOWS DEFINES */

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define WIN_HALF 360
# define MINI_MAP_WIDTH 189
# define MINI_MAP_HEIGHT 189
# define MINI_MAP_CENTER 90

/* CONSTANT DEFINES */

# define TILE_SIZE 9
# define PLAYER_RADIUS 4
# define PLAYER_SPEED 0.14
# define PLAYER_ROTATE 0.07
# define FOV_ANGLE 1.0472
# define HFOV_ANGLE 0.523599
# define DEGREES_0 0
# define DEGREES_90 1.5708
# define DEGREES_180 3.14159
# define DEGREES_270 4.71239
# define DEGREES_360 6.28319

/* MINIMAP COLORS */

# define PURPLE_DARK 6366286
# define GREY 7771317
# define RED 16531322
# define YELLOW 16777126
# define TRANSPARENT 3358535222

/* MAP VALID CHARACTERS */

# define MAP_CHAR "10NSEW"
# define MAP_POS "NSEW"
# define MAP_SR "1 "

/* ERROR MESSAGES */

# define ERR_ARG "usage: ./cub3d [path_to_map]"
# define ERR_FILE "could not open map file"
# define ERR_XPM "could not open xpm file"
# define ERR_ID "invalid map identifier"
# define ERR_FL_CEI "too many arguments in floor or ceiling id"
# define ERR_ID_INT "floor or ceiling arguments must be numbers between 0-255"
# define ERR_EXT_FILE "map file must have"
# define ERR_EXT_ID "texture file must have"
# define ERR_MAP_CHAR "map must contain only valid characters:"
# define ERR_MAP_SRND "map must be surrounded by walls"
# define ERR_MAP_POS "there must be only one start position"
# define ERR_MAP_NO_POS "there is no start position"
# define ERR_MAP_EMPTY "map file is empty"

/* STRUCTURES & FUNCTIONS */

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*fl;
	char	*cei;
	char	**map;
}	t_data;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	int		bpp;
	char	*addr;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_textures
{
	t_img	no;
	t_img	so;
	t_img	ea;
	t_img	we;
	int		floor;
	int		ceiling;
}	t_textures;

typedef struct s_bres
{
	float	x;
	float	y;
	float	end_x;
	float	end_y;
}	t_bres;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	float		step_x;
	float		step_y;
	int			mouse;
	t_keys		key;
}	t_player;

typedef struct s_game
{
	void		*ptr;
	void		*win;
	int			size_x;
	int			size_y;
	char		**map;
	float		wall_height;
	t_player	player;
	t_img		mini_map;
	t_img		bg;
	t_textures	tex;
}	t_game;

char	**get_info(char **argv);
int		parse_data(char **info, t_data *data);
int		check_data(t_data *data, t_game *g);
void	get_map(char **info, t_data *data, int err);
int		check_map_surrounding(char **map, t_game *g);
int		check_space_surrounding(char **map, int i, int j, t_game *g);

int		check_file_extension(char *argv, char *ext, char *err);
int		str_is_digit(char *str);

void	init_cube(t_data *data, t_game *g);
void	raycast(t_game *g);
void	draw_background(t_img bg, int ceiling, int floor);
void	draw_mini_map(t_img mini_map, t_game *g);

void	my_mlx_pixel_put(t_img *img, int x, int y, long texture);
int		my_mlx_pixel_get(t_img *data, int x, int y);
void	draw_line(t_img img, t_bres bres, int texture);

void	check_movement(t_game *g);
int		key_released(int key, t_game *g);
int		key_pressed(int key, t_game *g);
int		mouse_input(int x, int y, t_game *g);

void	free_data(t_data *data);
int		close_game(t_game *g);

#endif
