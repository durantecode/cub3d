/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:55:00 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/15 00:21:33 by ldurante         ###   ########.fr       */
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
	(*var) = r + g + b;// Convertir a hex con las fórmulas del fdf de dani.
	return (0);
}

static int	check_floor_ceiling(char *str, int *cub)
{
	int		i;
	char	**split_comma;

	i = 0;
	split_comma = ft_split(str, ',');
	if (matrix_len(split_comma) != 3)
	{
		printf("Error\n%s\n", ERR_FL_CEI); // y si tiene una coma al principio o final... ?
		free_matrix(split_comma);
		return (1);
	}
	while (split_comma[i])
	{
		if (!str_is_digit(split_comma[i]))
		{
			printf("Error\n%s\n", ERR_ID_INT);
			free_matrix(split_comma);
			return (1);
		}
		i++;
	}
	if (parse_floor_ceiling(split_comma, cub))
		return (1);
	free_matrix(split_comma);
	return (0);
}

int	check_data(t_data *data, t_cube *cub)
{
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
	if (check_map_errors(data->map))
		return (1);
	return (0);
}
