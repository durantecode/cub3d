/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:17:45 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/15 19:01:53 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_map_aux(t_vector c, int *pos, char **map, t_game *g)
{
	if (!ft_strchr(MAP_CHAR, map[(int)c.y][(int)c.x])
		&& map[(int)c.y][(int)c.x] != ' ')
		return (1);
	if (map[(int)c.y][(int)c.x] == ' '
		&& check_space_surrounding(map, c.y, c.x, g))
		return (2);
	if (ft_strchr(MAP_POS, map[(int)c.y][(int)c.x]))
	{
		if (*pos)
			return (3);
		*pos += 1;
		g->player.x = c.x;
		g->player.y = c.y;
	}
	if ((c.y == 0 || c.y == g->size_y - 1 || c.x == 0
			|| c.x == g->size_x - 1)
		&& !ft_strchr(MAP_SR, map[(int)c.y][(int)c.x]))
		return (2);
	return (0);
}

int	check_map_surrounding(char **map, t_game *g)
{
	t_vector	c;
	int			pos;
	int			res;

	c.y = 0;
	pos = 0;
	while (map[(int)c.y])
	{
		c.x = 0;
		while (map[(int)c.y][(int)c.x])
		{
			res = check_map_aux(c, &pos, map, g);
			if (res)
				return (res);
			c.x++;
		}
		c.y++;
	}
	if (!pos)
		return (4);
	return (0);
}
