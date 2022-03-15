/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:26:31 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/15 14:33:49 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	game_status(t_game *g)
{
	mlx_clear_window(g->ptr, g->win);
	check_movement(g);
	draw_background(g->bg, g->tex.ceiling, g->tex.floor);
	raycast(g);
	draw_mini_map(g->mini_map, g);
	mlx_put_image_to_window(g->ptr, g->win, g->bg.img, 0, 0);
	mlx_put_image_to_window(g->ptr, g->win, g->mini_map.img, 20, 511);
	return (0);
}

static void	init_images(t_game *g)
{
	g->bg.width = WIN_WIDTH;
	g->bg.height = WIN_HEIGHT;
	g->bg.img = mlx_new_image(g->ptr, WIN_WIDTH, WIN_HEIGHT);
	g->bg.addr = mlx_get_data_addr(g->bg.img, &g->bg.bpp,
			&g->bg.line_len, &g->bg.endian);
	g->mini_map.width = MINI_MAP_WIDTH;
	g->mini_map.height = MINI_MAP_HEIGHT;
	g->mini_map.img = mlx_new_image(g->ptr, MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
	g->mini_map.addr = mlx_get_data_addr(g->mini_map.img, &g->mini_map.bpp,
			&g->mini_map.line_len, &g->mini_map.endian);
	if (g->map[(int)g->player.y][(int)g->player.x] == 'N')
		g->player.angle = -DEGREES_90;
	if (g->map[(int)g->player.y][(int)g->player.x] == 'S')
		g->player.angle = -DEGREES_270;
	if (g->map[(int)g->player.y][(int)g->player.x] == 'E')
		g->player.angle = DEGREES_0;
	if (g->map[(int)g->player.y][(int)g->player.x] == 'W')
		g->player.angle = DEGREES_180;
}

void	init_cube(t_data *data, t_game *g)
{
	printf("Map okay... Init cube\n");
	g->map = matrix_dup(data->map);
	free_data(data);
	g->win = mlx_new_window(g->ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	init_images(g);
	mlx_loop_hook(g->ptr, game_status, g);
	mlx_hook(g->win, 17, 0, close_game, g);
	mlx_hook(g->win, 2, 1L << 0, key_pressed, g);
	mlx_hook(g->win, 3, 1L << 1, key_released, g);
	mlx_hook(g->win, 6, 1L << 6, mouse_input, g);
	mlx_loop(g->ptr);
}
