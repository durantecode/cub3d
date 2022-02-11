/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:56:54 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/11 00:51:05 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>

# define ERR_ARG "usage: ./cub3d [path_to_map]"
# define ERR_FILE "could not open map file"
# define ERR_ID "invalid map identifier"
# define ERR_EXT "map file must be have .cub extension"

typedef struct s_data
{
	char	**no;
	char	**so;
	char	**we;
	char	**ea;
	char	**fl;
	char	**cei;
	char	**map;
}	t_data;

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