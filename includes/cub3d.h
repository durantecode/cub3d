/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:56:54 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/16 14:55:09 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>
# include <math.h>

# define MAP_CHAR "10NSEW"
# define MAP_POS "NSEW"
# define MAP_SR "1 "

# define ERR_ARG "usage: ./cub3d [path_to_map]"
# define ERR_FILE "could not open map file"
# define ERR_ID "invalid map identifier"
# define ERR_FL_CEI "too many arguments in floor or ceiling id"
# define ERR_ID_INT "floor or ceiling arguments must be numbers between 0-255"
# define ERR_EXT_FILE "map file must have"
# define ERR_EXT_ID "texture file must have"

/* MAP ERRORS */
# define ERR_MAP_CHAR "map must contain only valid characters:"
# define ERR_MAP_SRND "map must be surrounded by walls"
# define ERR_MAP_POS "there must be only one start position"

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*fl;
	char	*cei;
	char	**map;
}	t_data;

typedef struct s_cube
{
	int	map_x;
	int	map_y;
	int	fl_dec;
	int	cei_dec;
}	t_cube;

typedef struct s_game
{
	void	*ptr;
	void	*win;
	int		size_x;
	int		size_y;
}	t_game;

char	**get_info(char **argv);
int		parse_data(char **info, t_data *data);
int		check_data(t_data *data, t_cube *cub);
void	get_map(char **info, t_data *data, int err);
int		check_map_surrounding(char **map, t_cube *cub);

int		check_file_extension(char *argv, char *ext, char *err);
int		str_is_digit(char *str);

#endif

/*
	Cosas a revisar:

	1. Check_error:
		- Extension del .cub
		- Extension de las texturas.
		- Nombre de la variable correcto en el fichero.
		- RGB de suelo y de Cielo deben ser entre 0 y 255.
		- Dentro del mapa:
			· Mirar que los bordes del mapa estén correctamente posicionados.
			· Que no haya mas de una W.
	2.	Reescribir atoi.
	3.	Probablemente necesitemos una estructura para almacenar datos especificos
		del mapa.
	4.	Separar el char_info.

*/