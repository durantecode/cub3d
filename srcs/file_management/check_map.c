/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:17:45 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/17 23:18:11 by ldurante         ###   ########.fr       */
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

int	check_map_surrounding(char **map, t_game *g)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	pos = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(MAP_CHAR, map[i][j]) && map[i][j] != ' ')
				return (1);
			if (map[i][j] == ' ' && check_space_surrounding(map, i, j, g))
				return (2);
			if (ft_strchr(MAP_POS, map[i][j]))
			{
				if (pos++)
					return (3);
				g->player_x = j;
				g->player_y = i;
			}
			if ((i == 0 || i == g->size_y - 1 || j == 0
					|| j == g->size_x - 1) && !ft_strchr(MAP_SR, map[i][j]))
				return (2);
			j++;
		}
		i++;
	}
	if (!pos)
		return (4);
	return (0);
}
