/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:52:40 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/15 14:11:33 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_fov(t_game *g, t_img img, t_bres ray)
{
	float		i;
	float		r;
	float		x;
	float		y;

	i = -HFOV_ANGLE;
	x = (g->player.x * TILE_SIZE) + PLAYER_RADIUS;
	y = (g->player.y * TILE_SIZE) + PLAYER_RADIUS;
	while (i < HFOV_ANGLE)
	{
		r = 0;
		ray.end_x = ray.x + r * cos(g->player.angle + i);
		ray.end_y = ray.y + r * sin(g->player.angle + i);
		while (g->map[(int)(y + (int)ray.end_y - (int)ray.y) / TILE_SIZE]
			[(int)(x + (int)ray.end_x - (int)ray.x) / TILE_SIZE] != '1')
		{
			ray.end_x = ray.x + r * cos(g->player.angle + i);
			ray.end_y = ray.y + r * sin(g->player.angle + i);
			r += 0.1;
		}
		ray.end_y = round(ray.end_y);
		ray.end_x = round(ray.end_x);
		draw_line(img, ray, YELLOW);
		i += FOV_ANGLE / WIN_WIDTH;
	}
}

static void	draw_player(t_game *g, t_img minimap)
{
	float	i;
	float	r;
	t_bres	ray;

	ft_bzero(&ray, sizeof(t_bres));
	ray.x = MINI_MAP_CENTER + TILE_SIZE / 2;
	ray.y = MINI_MAP_CENTER + TILE_SIZE / 2;
	draw_fov(g, minimap, ray);
	i = 0;
	r = PLAYER_RADIUS;
	while (i < DEGREES_360)
	{
		ray.end_x = round(ray.x + r * cos(i));
		ray.end_y = round(ray.y + r * sin(i));
		draw_line(minimap, ray, 12386304);
		i += 0.1;
	}
}

static void	draw_mini_map_aux(t_img minimap, t_game *g, t_bres mv)
{
	if (g->map[(int)mv.y / TILE_SIZE][(int)mv.x / TILE_SIZE] == '1')
		my_mlx_pixel_put(&minimap, mv.end_x, mv.end_y, PURPLE_DARK);
	else if (g->map[(int)mv.y / TILE_SIZE][(int)mv.x / TILE_SIZE] == ' ')
		my_mlx_pixel_put(&minimap, mv.end_x, mv.end_y, TRANSPARENT);
	else
		my_mlx_pixel_put(&minimap, mv.end_x, mv.end_y, GREY);
}

void	draw_mini_map(t_img minimap, t_game *g)
{
	t_bres	mv;

	mv.y = (g->player.y * TILE_SIZE - MINI_MAP_CENTER);
	mv.end_y = 0;
	while (mv.y < MINI_MAP_HEIGHT * TILE_SIZE)
	{
		mv.x = (g->player.x * TILE_SIZE - MINI_MAP_CENTER);
		mv.end_x = 0;
		while (mv.x < MINI_MAP_WIDTH * TILE_SIZE)
		{
			if (mv.y / TILE_SIZE < g->size_y && mv.x / TILE_SIZE < g->size_x
				&& mv.y / TILE_SIZE >= 0 && mv.x / TILE_SIZE >= 0)
				draw_mini_map_aux(minimap, g, mv);
			else
				my_mlx_pixel_put(&minimap, mv.end_x, mv.end_y, TRANSPARENT);
			mv.end_x++;
			mv.x++;
		}
		mv.y++;
		mv.end_y++;
	}
	draw_player(g, minimap);
}
