/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:56:54 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/10 21:26:04 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>

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