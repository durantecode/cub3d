/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:52:40 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/24 18:54:49 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

typedef struct mini_vector
{
	float	x;
	float	x1;
	float	y;
	float	y1;
}	t_mini_vector;

void	draw_line(t_game *g, t_img img)
{
	float		r;
	t_bres		bres;
	t_vector	vector;

	ft_bzero(&bres, sizeof(t_bres));
	vector = get_map_vector(g);
	bres.x = MINI_MAP_HALF + TILE_SIZE / 2;
	bres.y = MINI_MAP_HALF + TILE_SIZE / 2;
	r = 0;
	bres.end_x = round(bres.x + r * cos(g->player.dir + g->player.rotate));
	bres.end_y = round(bres.y + r * sin(g->player.dir + g->player.rotate));
	while (g->map[(vector.y + bres.end_y - bres.y) / TILE_SIZE]
		[(vector.x + bres.end_x - bres.x) / TILE_SIZE] != '1')
	{
		bres.end_x = round(bres.x + r * cos(g->player.dir + g->player.rotate));
		bres.end_y = round(bres.y + r * sin(g->player.dir + g->player.rotate));
		r++;
	}
	g->player.step_vx = cos(g->player.dir + g->player.rotate) * PLAYER_SPEED;
	g->player.step_vy = sin(g->player.dir + g->player.rotate) * PLAYER_SPEED;
	g->player.step_hx = cos((g->player.dir + DEGREES_90) + g->player.rotate) * PLAYER_SPEED;
	g->player.step_hy = sin((g->player.dir + DEGREES_90) + g->player.rotate) * PLAYER_SPEED;
	write_line_bres(img, bres, PLAYER_RED);
}

void	draw_fov(t_game *g, t_img img)
{
	float		i;
	float		r;
	t_bres		bres;
	t_vector	vector;

	vector = get_map_vector(g);
	i = -FOV_ANGLE;
	ft_bzero(&bres, sizeof(t_bres));
	bres.x = MINI_MAP_HALF + TILE_SIZE / 2;
	bres.y = MINI_MAP_HALF + TILE_SIZE / 2;
	while (i < FOV_ANGLE)
	{
		r = 0;
		bres.end_x = round(bres.x + r * cos(g->player.dir + i + g->player.rotate));
		bres.end_y = round(bres.y + r * sin(g->player.dir + i + g->player.rotate));
		while (g->map[(vector.y + bres.end_y - bres.y) / TILE_SIZE]
			[(vector.x + bres.end_x - bres.x) / TILE_SIZE] != '1')
		{
			bres.end_x = round(bres.x + r * cos(g->player.dir + i + g->player.rotate));
			bres.end_y = round(bres.y + r * sin(g->player.dir + i + g->player.rotate));
			r++;
		}
		write_line_bres(img, bres, FOV_BEIGE);
		i += 0.0005;
	}
}

void	draw_player(t_game *g, t_img img)
{
	float	i;
	float	r;
	t_bres	bres;

	ft_bzero(&bres, sizeof(t_bres));
	if (g->map[g->player.y][g->player.x] == 'N')
		g->player.dir = -DEGREES_90;
	if (g->map[g->player.y][g->player.x] == 'S')
		g->player.dir = -DEGREES_270;
	if (g->map[g->player.y][g->player.x] == 'E')
		g->player.dir = DEGREES_0;
	if (g->map[g->player.y][g->player.x] == 'W')
		g->player.dir = DEGREES_180;
	bres.x = MINI_MAP_CENTER + TILE_SIZE / 2;
	bres.y = MINI_MAP_CENTER + TILE_SIZE / 2;
	i = 0;
	r = PLAYER_RADIUS;
	while (i < DEGREES_360)
	{
		bres.end_x = bres.x + r * cos(i);
		bres.end_y = bres.y + r * sin(i);
		write_line_bres(img, bres, PLAYER_RED);
		i += 0.1;
	}
}

void	draw_mini_map_aux(t_img mini_map, t_game *g, t_mini_vector mv)
{
	if (g->map[(int)mv.y / TILE_SIZE][(int)mv.x / TILE_SIZE] == '1')
		my_mlx_pixel_put(&mini_map, mv.x1, mv.y1, WALL_PURPLE);
	else if (g->map[(int)mv.y / TILE_SIZE][(int)mv.x / TILE_SIZE] == ' ')
		my_mlx_pixel_put(&mini_map, mv.x1, mv.y1, TRANSPARENT);
	else
		my_mlx_pixel_put(&mini_map, mv.x1, mv.y1, FLOOR_GREY);
}

void	draw_mini_map(t_img mini_map, t_game *g)
{
	t_mini_vector	mv;

	mv.y = round((g->player.y * TILE_SIZE - MINI_MAP_CENTER) + g->player.move_y);
	mv.y1 = 0;
	while (mv.y < MINI_MAP_HEIGHT * TILE_SIZE)
	{
		mv.x = round((g->player.x * TILE_SIZE - MINI_MAP_CENTER) + g->player.move_x);
		mv.x1 = 0;
		while (mv.x < MINI_MAP_WIDTH * TILE_SIZE)
		{
			if (mv.y / TILE_SIZE < g->size_y && mv.x / TILE_SIZE < g->size_x
				&& mv.y / TILE_SIZE >= 0 && mv.x / TILE_SIZE >= 0)
				draw_mini_map_aux(mini_map, g, mv);
			else
				my_mlx_pixel_put(&mini_map, mv.x1, mv.y1, TRANSPARENT);
			mv.x1++;
			mv.x++;
		}
		mv.y++;
		mv.y1++;
	}
	draw_player(g, mini_map);
	draw_fov(g, mini_map);
	draw_line(g, mini_map);
}
