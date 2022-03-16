/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:55:00 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/16 02:14:55 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_floor_ceiling(char **split_comma, int *var)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(split_comma[0]);
	g = ft_atoi(split_comma[1]);
	b = ft_atoi(split_comma[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
	{
		printf("Error\n%s\n", ERR_ID_INT);
		return (1);
	}
	(*var) = 0 << 24 | r << 16 | g << 8 | b;
	return (0);
}

static int	check_floor_ceiling(char *str, int *g)
{
	int		i;
	char	**split_comma;
	int		err;

	err = 0;
	i = -1;
	if (str[0] == ',' || str[ft_strlen(str) - 1] == ',')
		err++;
	split_comma = ft_split(str, ',');
	if (err || ((matrix_len(split_comma) != 3) && ++err))
		printf("Error\n%s\n", ERR_FL_CEI);
	while (!err && split_comma[++i])
	{
		if (!str_is_digit(split_comma[i]) && ++err)
			printf("Error\n%s\n", ERR_ID_INT);
		if (!str_is_digit(split_comma[i]))
			break ;
	}
	if (err || parse_floor_ceiling(split_comma, g))
	{
		free_matrix(split_comma);
		return (1);
	}
	free_matrix(split_comma);
	return (0);
}

void	map_errors(int map_status)
{
	if (map_status == 1)
		printf("Error\n%s %s\n", ERR_MAP_CHAR, MAP_CHAR);
	else if (map_status == 2)
		printf("Error\n%s\n", ERR_MAP_SRND);
	else if (map_status == 3)
		printf("Error\n%s\n", ERR_MAP_POS);
	else if (map_status == 4)
		printf("Error\n%s\n", ERR_MAP_NO_POS);
}

int	check_data(t_data *data, t_game *g)
{
	int	map_status;

	if (check_file_extension(data->no, ".xpm", ERR_EXT_ID))
		return (1);
	if (check_file_extension(data->so, ".xpm", ERR_EXT_ID))
		return (1);
	if (check_file_extension(data->we, ".xpm", ERR_EXT_ID))
		return (1);
	if (check_file_extension(data->ea, ".xpm", ERR_EXT_ID))
		return (1);
	if (check_floor_ceiling(data->fl, &(g->tex.floor)))
		return (1);
	if (check_floor_ceiling(data->cei, &(g->tex.ceiling)))
		return (1);
	g->size_x = ft_strlen(data->map[0]);
	g->size_y = matrix_len(data->map);
	map_status = check_map_surrounding(data->map, g);
	map_errors(map_status);
	return (map_status);
}
