/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:17:17 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/28 13:25:49 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background(t_img bg, int ceiling, int floor)
{
	int	x;
	int	y;
	int	texture;

	y = 0;
	texture = ceiling;
	while (y < bg.heigth)
	{
		if (y == WIN_HALF)
			texture = floor;
		x = 0;
		while (x < bg.width)
		{
			my_mlx_pixel_put(&bg, x, y, texture);
			x++;
		}
		y++;
	}
}
