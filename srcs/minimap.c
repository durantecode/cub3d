/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:52:40 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/02 01:50:54 by ldurante         ###   ########.fr       */
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
	t_bres		ray;
	t_vector	vector;

	ft_bzero(&ray, sizeof(t_bres));
	vector = get_map_vector(g);
	ray.x = MINI_MAP_CENTER + TILE_SIZE / 2;
	ray.y = MINI_MAP_CENTER + TILE_SIZE / 2;
	r = 0;
	ray.end_x = ray.x + r * cos(g->player.dir + g->player.rotate);
	ray.end_y = ray.y + r * sin(g->player.dir + g->player.rotate);
	while (g->map[(vector.y + (int)ray.end_y - (int)ray.y) / TILE_SIZE]
		[(vector.x + (int)ray.end_x - (int)ray.x) / TILE_SIZE] != '1')
	{
		ray.end_x = ray.x + r * cos(g->player.dir + g->player.rotate);
		ray.end_y = ray.y + r * sin(g->player.dir + g->player.rotate);
		r++;
	}
	g->player.step_vx = cos(g->player.dir + g->player.rotate) * PLAYER_SPEED;
	g->player.step_vy = sin(g->player.dir + g->player.rotate) * PLAYER_SPEED;
	g->player.step_hx = cos((g->player.dir + DEGREES_90) + g->player.rotate) * PLAYER_SPEED;
	g->player.step_hy = sin((g->player.dir + DEGREES_90) + g->player.rotate) * PLAYER_SPEED;
	// write_line_bres(img, bres, PLAYER_RED);
	(void)img;
}

// int	ft_colorcmp(int y, int x, int color, t_img *img)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line_len
// 				+ x * (img->bpp / 8));
// 	if (*(int *)dst == color)
// 		return (1);
// 	return (0);
// }

int	get_texture(t_game *g, t_bres ray)
{
	float	small;
	int		texture;

	// small = 0.1106666;
	// small = 0.0509;
	// small = 0.00599;
	small = 0.005;
	texture = 0;
	(void)g;
	if (ray.end_y - (int)ray.end_y < small && \
			ray.end_x > (int)ray.end_x + small && ray.end_x < (int)ray.end_x + 1 - small)
		texture = WALL_PURPLE;
	else if ((int)ray.end_y + 1 - ray.end_y < small && \
		ray.end_x > (int)ray.end_x + small && ray.end_x < (int)ray.end_x + 1 - small)
		texture = WALL_PURPLE_DARK;
	else if (ray.end_x - (int)ray.end_x < small && \
		ray.end_y > (int)ray.end_y + small && ray.end_y < (int)ray.end_y + 1 - small)
		texture = PLAYER_RED;
	else if ((int)ray.end_x + 1 - ray.end_x < small && \
		ray.end_y > (int)ray.end_y + small && ray.end_y < (int)ray.end_y + 1 - small)
		texture = FOV_BEIGE;
	return (texture);
}

void	draw_walls(float r, float i, int column, t_game *g, t_bres ray)
{
	float	wall_height;
	float	distance;
	int		texture;

	texture = get_texture(g, ray);
	ray.x = column;
	ray.end_x = column;
	distance = r * cos(i);
	wall_height = 2000 / distance;
	ray.y = WIN_HALF - wall_height;
	ray.end_y = WIN_HALF + wall_height;
	write_line_bres(g->bg, ray, texture);
}

void	draw_fov(t_game *g, t_img img)
{
	float		i;
	float		r;
	t_bres		ray;
	t_vector	vector;
	int			ray_count;

	ray_count = 0;
	i = -FOV_ANGLE;
	vector = get_map_vector(g);
	ft_bzero(&ray, sizeof(t_bres));
	ray.x = MINI_MAP_CENTER + TILE_SIZE / 2;
	ray.y = MINI_MAP_CENTER + TILE_SIZE / 2;
	while (ray_count < WIN_WIDTH)
	{
		r = 0;
		ray.end_x = ray.x + r * cos(g->player.dir + i + g->player.rotate);
		ray.end_y = ray.y + r * sin(g->player.dir + i + g->player.rotate);
		while (g->map[(vector.y + (int)ray.end_y - (int)ray.y) / TILE_SIZE]
			[(vector.x + (int)ray.end_x - (int)ray.x) / TILE_SIZE] != '1')
		{
			ray.end_x = ray.x + r * cos(g->player.dir + i + g->player.rotate);
			ray.end_y = ray.y + r * sin(g->player.dir + i + g->player.rotate);
			r += 0.005;
		}
		draw_walls(r, i, ray_count, g, ray);
		ray.end_y = round(ray.end_y);
		ray.end_x = round(ray.end_x);
		write_line_bres(img, ray, FOV_BEIGE);
		i += FOV_ANGLE * 2 / WIN_WIDTH;
		ray_count++;
	}
}

void	draw_player(t_game *g, t_img img)
{
	float	i;
	float	r;
	t_bres	ray;

	ft_bzero(&ray, sizeof(t_bres));
	if (g->map[g->player.y][g->player.x] == 'N')
		g->player.dir = -DEGREES_90;
	if (g->map[g->player.y][g->player.x] == 'S')
		g->player.dir = -DEGREES_270;
	if (g->map[g->player.y][g->player.x] == 'E')
		g->player.dir = DEGREES_0;
	if (g->map[g->player.y][g->player.x] == 'W')
		g->player.dir = DEGREES_180;
	ray.x = MINI_MAP_CENTER + TILE_SIZE / 2;
	ray.y = MINI_MAP_CENTER + TILE_SIZE / 2;
	i = 0;
	r = PLAYER_RADIUS;
	while (i < DEGREES_360)
	{
		ray.end_x = round(ray.x + r * cos(i));
		ray.end_y = round(ray.y + r * sin(i));
		write_line_bres(img, ray, PLAYER_RED);
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
	draw_fov(g, mini_map);
	draw_line(g, mini_map);
	draw_player(g, mini_map);
}
