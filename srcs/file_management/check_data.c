/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:55:00 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/16 01:38:40 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Convertir a hex con las fórmulas del fdf de dani */

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
	(*var) = r + g + b;
	return (0);
}

static int	check_floor_ceiling(char *str, int *cub)
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
	if (err || parse_floor_ceiling(split_comma, cub))
	{
		free_matrix(split_comma);
		return (1);
	}
	free_matrix(split_comma);
	return (0);
}

int	check_data(t_data *data, t_cube *cub)
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
	if (check_floor_ceiling(data->fl, &(cub->fl_dec)))
		return (1);
	if (check_floor_ceiling(data->cei, &(cub->cei_dec)))
		return (1);
	cub->map_x = ft_strlen(data->map[0]);
	cub->map_y = matrix_len(data->map);
	map_status = check_map_surrounding(data->map, cub);
	if (map_status == 1)
		printf("Error\n%s %s\n", ERR_MAP_CHAR, MAP_CHAR);
	else if (map_status == 2)
		printf("Error\n%s\n", ERR_MAP_SRND);
	else if (map_status == 3)
		printf("Error\n%s\n", ERR_MAP_POS);
	return (map_status);
}
