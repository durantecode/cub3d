/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:20:13 by pavon             #+#    #+#             */
/*   Updated: 2022/02/17 16:12:28 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	write_line_bres(t_img mini_map, t_bres bres, int color)
{
	float	step_x;
	float	step_y;
	float	dist;
	int		i;

	dist = sqrt(pow(bres.x - bres.end_x, 2)
		+ pow(bres.y - bres.end_y, 2));
	step_x = (bres.end_x - bres.x) / dist;
	step_y = (bres.end_y - bres.y) / dist;
	i = 0;
	while (i < dist)
	{
		my_mlx_pixel_put(&mini_map, (bres.x + step_x * i)
			+ 0, (bres.y + step_y * i)
			+ 0, color);
		i++;
	}
}

int	check_file_extension(char *argv, char *ext, char *err)
{
	int		len;
	char	*aux;

	len = ft_strlen(argv);
	aux = ft_substr(argv, len - 4, len);
	if (ft_strcmp(aux, ext))
	{
		printf("Error\n%s %s extension\n", err, ext);
		free(aux);
		return (1);
	}
	free(aux);
	return (0);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
