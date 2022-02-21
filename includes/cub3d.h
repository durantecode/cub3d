/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:56:54 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/21 17:59:02 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>
# include <math.h>

# define WIN_WIDTH 1080
# define WIN_HEIGTH 720
# define MINI_MAP_WIDTH 200
# define MINI_MAP_HEIGTH 200

/*COLOR DEFINE*/
# define WALL_PURPLE 11027942
# define PLAYER_RED 16531322
# define FLOOR_BEIGE 15912380
# define TRANSPARENT 3358535222

#ifndef KEYCODES
# define KEYCODES

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_ESC 53
#endif


# define MAP_CHAR "10NSEW"
# define MAP_POS "NSEW"
# define MAP_SR "1 "

# define ERR_ARG "usage: ./cub3d [path_to_map]"
# define ERR_FILE "could not open map file"
# define ERR_XPM "could not open xpm file"
# define ERR_ID "invalid map identifier"
# define ERR_FL_CEI "too many arguments in floor or ceiling id"
# define ERR_ID_INT "floor or ceiling arguments must be numbers between 0-255"
# define ERR_EXT_FILE "map file must have"
# define ERR_EXT_ID "texture file must have"

/* MAP ERRORS */
# define ERR_MAP_CHAR "map must contain only valid characters:"
# define ERR_MAP_SRND "map must be surrounded by walls"
# define ERR_MAP_POS "there must be only one start position"
# define ERR_MAP_NO_POS "there is no start position"

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

typedef struct s_img
{
	void	*img;
	int		width;
	int		heigth;
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

typedef	struct s_bres
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;
}	t_bres;

typedef struct s_game
{
	void		*ptr;
	void		*win;
	int			player_x;
	int			player_y;
	int			size_x;
	int			size_y;
	int			move_pos_x;
	int			move_pos_y;
	char		**map;
	t_img		mini_map;
	t_textures	tex;
}	t_game;

char	**get_info(char **argv);
int		parse_data(char **info, t_data *data);
int		check_data(t_data *data, t_game *g);
void	get_map(char **info, t_data *data, int err);
int		check_map_surrounding(char **map, t_game *g);

int		load_files(t_game *g, t_data *data);
int		check_file_extension(char *argv, char *ext, char *err);
int		str_is_digit(char *str);

void	my_mlx_pixel_put(t_img *mini_map, int x, int y, long color);
void	write_line_bres(t_img mini_map, t_bres bres, int color);

#endif

/*
	Cosas a tener en cuenta:

	1. En el parseo debemos sacar la coordenada donde va a empezar
	nuestro personaje.
	
*/
