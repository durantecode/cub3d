/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:17:45 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/15 20:53:42 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*	1 - Todo son paredes (1)
	2 - Posicion jugador no repetida (NSWE)
	3 - 
*/

static int check_corners(char **m, int i, int j, t_cube *cub)
{
	if (j == 0 && i == 0)
	{
		if (!ft_strchr(MAP_SR, m[i][j + 1]) || !ft_strchr(MAP_SR, m[i + 1][j])
			|| !ft_strchr(MAP_SR, m[i + 1][j + 1]))
			return (1);
	}
	if (j == cub->map_x - 1 && i == 0)
	{
		if (!ft_strchr(MAP_SR, m[i][j - 1]) || !ft_strchr(MAP_SR, m[i + 1][j])
			|| !ft_strchr(MAP_SR, m[i + 1][j - 1]))
			return (1);
	}
	if (j == 0 && i == cub->map_y - 1)
	{
		if (!ft_strchr(MAP_SR, m[i - 1][j]) || !ft_strchr(MAP_SR, m[i][j + 1])
			|| !ft_strchr(MAP_SR, m[i - 1][j + 1]))
			return (1);
	}
	if (j == cub->map_x - 1 && i == cub->map_y - 1)
	{
		if (!ft_strchr(MAP_SR, m[i - 1][j]) || !ft_strchr(MAP_SR, m[i][j - 1])
			|| !ft_strchr(MAP_SR, m[i - 1][j - 1]))
			return (1);
	}
	return (0);
}

static int check_border_y(char **m, int i, int j, t_cube *cub)
{
	if (j == 0 && i > 0 && i < cub->map_y - 1)
	{
		printf("AA\n");
		if (!ft_strchr(MAP_SR, m[i][j + 1]) 
			|| !ft_strchr(MAP_SR, m[i + 1][j])
			|| !ft_strchr(MAP_SR, m[i - 1][j])
			|| !ft_strchr(MAP_SR, m[i - 1][j + 1])
			|| !ft_strchr(MAP_SR, m[i + 1][j + 1]))
			return (1);
	}
	if (j == cub->map_x - 1 && i > 0 && i < cub->map_y - 1)
	{
		printf("BB\n");
		if (!ft_strchr(MAP_SR, m[i][j - 1]) 
			|| !ft_strchr(MAP_SR, m[i + 1][j - 1])
			|| !ft_strchr(MAP_SR, m[i - 1][j])
			|| !ft_strchr(MAP_SR, m[i - 1][j - 1])
			|| !ft_strchr(MAP_SR, m[i + 1][j - 1]))
			return (1);
	}
	// if (!ft_strchr(MAP_SR, m[i][j]))
	// 	return (1);
	return (0);
}

static int check_space_surrounding(char **map, int i, int j, t_cube *cub)
{
	if (j > 0 && j < cub->map_x - 1 && i > 0 && i < cub->map_y - 1)
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
	else if (check_border_y(map, i, j, cub))
		return (1);
	// else if (check_border_x(map, i, j, cub))
	// 	return (1);
	else if (check_corners(map, i, j, cub))
		return (1);
	return (0);
}

static int check_map_surrounding(char **map, t_cube *cub)
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
			if (map[i][j] == ' ' &&	check_space_surrounding(map, i, j, cub))
				return (2);
			// else if (check_border_y(map, i, j, cub))
			// 	return (2);
			// else if ((i == 0 || j == 0) && !ft_strchr(MAP_SR, map[i][j]))
			// 	return (2);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_errors(char **map, t_cube *cub)
{
	int	map_status;
	
	print_matrix(map);
	cub->map_x = ft_strlen(map[0]);
	cub->map_y = matrix_len(map);
	map_status = check_map_surrounding(map, cub);
	return (map_status);
}
