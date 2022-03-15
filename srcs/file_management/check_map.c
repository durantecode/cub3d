/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:17:45 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/15 18:46:36 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_corners(char **m, int i, int j, t_game *g)
{
	if (j == 0 && i == 0)
	{
		if (!ft_strchr(MAP_SR, m[i][j + 1]) || !ft_strchr(MAP_SR, m[i + 1][j])
			|| !ft_strchr(MAP_SR, m[i + 1][j + 1]))
			return (1);
	}
	if (j == g->size_x - 1 && i == 0)
	{
		if (!ft_strchr(MAP_SR, m[i][j - 1]) || !ft_strchr(MAP_SR, m[i + 1][j])
			|| !ft_strchr(MAP_SR, m[i + 1][j - 1]))
			return (1);
	}
	if (j == 0 && i == g->size_y - 1)
	{
		if (!ft_strchr(MAP_SR, m[i - 1][j]) || !ft_strchr(MAP_SR, m[i][j + 1])
			|| !ft_strchr(MAP_SR, m[i - 1][j + 1]))
			return (1);
	}
	if (j == g->size_x - 1 && i == g->size_y - 1)
	{
		if (!ft_strchr(MAP_SR, m[i - 1][j]) || !ft_strchr(MAP_SR, m[i][j - 1])
			|| !ft_strchr(MAP_SR, m[i - 1][j - 1]))
			return (1);
	}
	return (0);
}

static int	check_border_y(char **m, int i, int j, t_game *g)
{
	if (j == 0 && i > 0 && i < g->size_y - 1)
	{
		if (!ft_strchr(MAP_SR, m[i][j + 1])
			|| !ft_strchr(MAP_SR, m[i + 1][j])
			|| !ft_strchr(MAP_SR, m[i - 1][j])
			|| !ft_strchr(MAP_SR, m[i - 1][j + 1])
			|| !ft_strchr(MAP_SR, m[i + 1][j + 1]))
			return (1);
	}
	if (j == g->size_x - 1 && i > 0 && i < g->size_y - 1)
	{
		if (!ft_strchr(MAP_SR, m[i][j - 1])
			|| !ft_strchr(MAP_SR, m[i + 1][j - 1])
			|| !ft_strchr(MAP_SR, m[i - 1][j])
			|| !ft_strchr(MAP_SR, m[i - 1][j - 1])
			|| !ft_strchr(MAP_SR, m[i + 1][j - 1]))
			return (1);
	}
	return (0);
}

static int	check_border_x(char **m, int i, int j, t_game *g)
{
	if (i == 0 && j > 0 && j < g->size_x - 1)
	{
		if (!ft_strchr(MAP_SR, m[i][j + 1])
			|| !ft_strchr(MAP_SR, m[i][j - 1])
			|| !ft_strchr(MAP_SR, m[i + 1][j])
			|| !ft_strchr(MAP_SR, m[i + 1][j + 1])
			|| !ft_strchr(MAP_SR, m[i + 1][j - 1]))
			return (1);
	}
	if (i == g->size_y - 1 && j > 0 && j < g->size_x - 1)
	{
		if (!ft_strchr(MAP_SR, m[i][j + 1])
			|| !ft_strchr(MAP_SR, m[i][j - 1])
			|| !ft_strchr(MAP_SR, m[i - 1][j])
			|| !ft_strchr(MAP_SR, m[i - 1][j + 1])
			|| !ft_strchr(MAP_SR, m[i - 1][j - 1]))
			return (1);
	}
	return (0);
}

static int	check_space_surrounding(char **map, int i, int j, t_game *g)
{
	if (j > 0 && j < g->size_x - 1 && i > 0 && i < g->size_y - 1)
	{
		if (!ft_strchr(MAP_SR, map[i][j - 1])
			|| !ft_strchr(MAP_SR, map[i][j + 1]))
			return (1);
		if (!ft_strchr(MAP_SR, map[i - 1][j])
			|| !ft_strchr(MAP_SR, map[i + 1][j]))
			return (1);
		if (!ft_strchr(MAP_SR, map[i - 1][j - 1])
			|| !ft_strchr(MAP_SR, map[i - 1][j + 1]))
			return (1);
		if (!ft_strchr(MAP_SR, map[i + 1][j - 1])
			|| !ft_strchr(MAP_SR, map[i + 1][j + 1]))
			return (1);
	}
	else if (check_border_y(map, i, j, g))
		return (1);
	else if (check_border_x(map, i, j, g))
		return (1);
	else if (check_corners(map, i, j, g))
		return (1);
	return (0);
}

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
