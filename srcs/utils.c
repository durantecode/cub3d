/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:20:13 by pavon             #+#    #+#             */
/*   Updated: 2022/03/15 14:36:04 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, long texture)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->line_len
				+ x * (img->bpp / 8));
		*(unsigned int *)dst = texture;
	}
}

int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_line(t_img img, t_bres bres, int texture)
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
		my_mlx_pixel_put(&img, (bres.x + step_x * i)
			+ 0, (bres.y + step_y * i)
			+ 0, texture);
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
