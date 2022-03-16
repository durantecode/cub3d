/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:15:36 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/16 11:44:53 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_texture_color(t_game *g, t_img *img, t_vector ray, int y)
{
	int	color;
	int	x;

	color = 0;
	x = (int)(img->width * (ray.x + ray.y)) % img->width;
	if (g->map[(int)ray.y][(int)ray.x] == '1')
		color = my_mlx_pixel_get(img, x, y);
	return (color);
}

t_img	get_texture_img(t_game *g, t_vector ray, float ray_angle)
{
	t_img	texture_img;
	float	step_x;
	float	step_y;

	ft_bzero(&texture_img, sizeof(t_img));
	step_x = cos(ray_angle) / 90;
	step_y = sin(ray_angle) / 90;
	if (step_x < 0)
		step_x = -step_x;
	if (step_y < 0)
		step_y = -step_y;
	if (g->map[(int)(ray.y - step_y)][(int)ray.x] != '1')
		texture_img = g->tex.no;
	else if (g->map[(int)(ray.y + step_y)][(int)ray.x] != '1')
		texture_img = g->tex.so;
	else if (g->map[(int)ray.y][(int)(ray.x - step_x)] != '1')
		texture_img = g->tex.we;
	else if (g->map[(int)ray.y][(int)(ray.x + step_x)] != '1')
		texture_img = g->tex.ea;
	return (texture_img);
}

void	draw_walls(t_game *g, t_img texture, t_vector ray, int ray_count)
{
	int		i;
	float	j;
	float	step_y;
	int		color;
	t_bres	draw;

	step_y = g->wall_height * 2 / texture.height;
	draw.x = ray_count;
	draw.end_x = ray_count;
	draw.y = WIN_HALF - g->wall_height;
	i = 0;
	while (i < texture.height)
	{
		color = get_texture_color(g, &texture, ray, i);
		j = draw.y;
		while (j < draw.y + step_y)
			j++;
		draw.end_y = j;
		draw_line(g->bg, draw, color);
		draw.y += step_y;
		i++;
	}
}

void	dist_to_wall(float ray_angle, int ray_count, t_game *g, t_vector ray)
{
	float	distance;
	t_img	texture_img;

	distance = sqrt(pow(ray.x - g->player.x - 0.5, 2)
			+ pow(ray.y - g->player.y - 0.5, 2));
	distance = distance * cos(ray_angle - g->player.angle);
	g->wall_height = 475 / distance;
	texture_img = get_texture_img(g, ray, ray_angle);
	draw_walls(g, texture_img, ray, ray_count);
}

void	raycast(t_game *g)
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
		ray_cos = cos(ray_angle) / 90;
		ray_sin = sin(ray_angle) / 90;
		while (g->map[(int)floor(ray.y)][(int)floor(ray.x)] != '1')
		{
			ray.x += ray_cos;
			ray.y += ray_sin;
		}
		dist_to_wall(ray_angle, ray_count, g, ray);
		ray_angle += FOV_ANGLE / WIN_WIDTH;
		ray_count++;
	}
}
