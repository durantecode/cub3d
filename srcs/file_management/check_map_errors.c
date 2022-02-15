/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:17:45 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/15 18:41:25 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*	1 - Todo son paredes (1)
	2 - Posicion jugador no repetida (NSWE)
	3 - 
*/

static int check_space_surrounding(char **map, int i, int j)
{
	int len;
	
	len = ft_strlen(map[i]);
	if (j > 0 && !ft_strchr(MAP_SRND, map[i][j - 1])
		&& !ft_strchr(MAP_SRND, map[i][j + 1]))
		return (1);
	if (j < len && !ft_strchr(MAP_SRND, map[i][j - 1])
		&& !ft_strchr(MAP_SRND, map[i][j + 1]))
		return (1);
	return (0);
}

static int check_rows(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (!ft_strchr(MAP_CHAR, map[i][j]) && map[i][j] != ' ')
				return (1);
			if (map[i][j] == ' ')
				check_space_surrounding(map, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_errors(char **map)
{

	if (check_rows(map))
		return (1);
	return (0);
}
