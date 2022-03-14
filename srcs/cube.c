/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:15:36 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/14 20:53:41 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_texture(t_game *g, t_vector ray, float step_x, float step_y)
{
	int			texture;

	if (step_x < 0)
		step_x = -step_x;
	if (step_y < 0)
		step_y = -step_y;
	texture = 0;
	if (g->map[(int)(ray.y - step_y)][(int)ray.x] != '1')
		texture = PURPLE_DARK;
	else if (g->map[(int)(ray.y + step_y)][(int)ray.x] != '1')
		texture = GREEN;
	else if (g->map[(int)ray.y][(int)(ray.x - step_x)] != '1')
		texture = RED;
	else if (g->map[(int)ray.y][(int)(ray.x + step_x)] != '1')
		texture = YELLOW;
	return (texture);
}

void	draw_walls(float ray_angle, int ray_count, t_game *g, t_vector ray)
{
	float	step_x;
	float	step_y;
	float	wall_height;
	float	distance;
	int		texture;
	t_bres	draw;

	step_x = cos(ray_angle) / 70;
	step_y = sin(ray_angle) / 70;
	texture = get_texture(g, ray, step_x, step_y);
	// distance = sqrt(pow(g->player.x - ray.x, 2) + pow(g->player.y - ray.y, 2));
	distance = sqrt(pow(ray.x - g->player.x - 0.5, 2) + pow(ray.y - g->player.y - 0.5, 2));
	distance = distance * cos(ray_angle - g->player.angle);
	wall_height = WIN_HEIGHT / (1.4 * distance);
	draw.x = ray_count;
	draw.end_x = ray_count;
	draw.y = WIN_HALF - wall_height;
	draw.end_y = WIN_HALF + wall_height;
	write_line_bres(g->bg, draw, texture);
}

void	draw_cube(t_game *g)
{
	int			ray_count;
	float		ray_angle;
	float		ray_cos;
	float		ray_sin;
	t_vector	ray;

	ray_count = 0;
	ray_angle = g->player.angle - HFOV_ANGLE;
	ft_bzero(&ray, sizeof(t_vector));
	while (ray_count < WIN_WIDTH)
	{
		ray.x = g->player.x + 0.5;
		ray.y = g->player.y + 0.5;
		ray_cos = cos(ray_angle) / 70;
		ray_sin = sin(ray_angle) / 70;
		while (g->map[(int)floor(ray.y)][(int)floor(ray.x)] != '1')
		{
			ray.x += ray_cos;
			ray.y += ray_sin;
		}
		draw_walls(ray_angle, ray_count, g, ray);
		ray_angle += FOV_ANGLE / WIN_WIDTH;
		ray_count++;
	}
}