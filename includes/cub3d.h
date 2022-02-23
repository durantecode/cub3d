/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:56:54 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/23 14:56:37 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <math.h>

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define WIN_HALF 360
# define MINI_MAP_WIDTH 180
# define MINI_MAP_HEIGHT 180
# define MINI_MAP_CENTER 90
# define MINI_MAP_HALF 89
# define TILE_SIZE 9
# define PLAYER_RADIUS 3.5

/*COLOR DEFINE*/

# define WALL_PURPLE 11027942
# define PLAYER_RED 16531322
# define RAY_GREY 8553090
# define FLOOR_BEIGE 15912380
# define TRANSPARENT 3358535222

// #ifndef KEYCODES
// # define KEYCODES

// # define KEY_UP 126
// # define KEY_DOWN 125
// # define KEY_LEFT 123
// # define KEY_RIGHT 124
// # define KEY_W 13
// # define KEY_S 1
// # define KEY_A 0
// # define KEY_D 2
// # define KEY_ESC 53
// #endif


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
	float		rotate;
	float		dir;
	float		step_x;
	float		step_y;
	float		step_left_x;
	float		step_right_y;
	float		move_pos_x;
	float		move_pos_y;
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

void	my_mlx_pixel_put(t_img *img, int x, int y, long texture);
void	write_line_bres(t_img img, t_bres bres, int texture);

#endif

/*
	Cosas a tener en cuenta:

	En el mapa, si hay 1 justo despues del color C no parsea esa lína,
	debería dar un error o parsearla.


	Luis echa un vistazo a esto:

	Cuando dejamos el boton de mover el rayo pulsado un rato el rayo empieza a descentrarse,
	no se si será algo problemático pero si podemos echarle un vistazo mejor :)

	A tener en cuenta:

	He puesto lo que pasabamos en grados directamente a radianes para trabajar en la misma unidad 
	de medida.
	Y el rayo ahora mismo se mueve solo de 90 grados en 90 grados.	
*/
