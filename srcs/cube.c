/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:26:31 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/15 18:16:45 by ldurante         ###   ########.fr       */
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

void	load_files(t_game *g, t_data *data)
{
	g->tex.no.img = mlx_xpm_file_to_image(g->ptr, data->no,
			&g->tex.no.width, &g->tex.no.height);
	g->tex.no.addr = mlx_get_data_addr(g->tex.no.img, &g->tex.no.bpp,
			&g->tex.no.line_len, &g->tex.no.endian);
	g->tex.so.img = mlx_xpm_file_to_image(g->ptr, data->so,
			&g->tex.so.width, &g->tex.so.height);
	g->tex.so.addr = mlx_get_data_addr(g->tex.so.img, &g->tex.so.bpp,
			&g->tex.so.line_len, &g->tex.so.endian);
	g->tex.ea.img = mlx_xpm_file_to_image(g->ptr, data->ea,
			&g->tex.ea.width, &g->tex.ea.height);
	g->tex.ea.addr = mlx_get_data_addr(g->tex.ea.img, &g->tex.ea.bpp,
			&g->tex.ea.line_len, &g->tex.ea.endian);
	g->tex.we.img = mlx_xpm_file_to_image(g->ptr, data->we,
			&g->tex.we.width, &g->tex.we.height);
	g->tex.we.addr = mlx_get_data_addr(g->tex.we.img, &g->tex.we.bpp,
			&g->tex.we.line_len, &g->tex.we.endian);
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
	g->ptr = mlx_init();
	g->win = mlx_new_window(g->ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	g->map = matrix_dup(data->map);
	load_files(g, data);
	free_data(data);
	init_images(g);
	mlx_loop_hook(g->ptr, game_status, g);
	mlx_hook(g->win, 17, 0, close_game, g);
	mlx_hook(g->win, 2, 1L << 0, key_pressed, g);
	mlx_hook(g->win, 3, 1L << 1, key_released, g);
	mlx_hook(g->win, 6, 1L << 6, mouse_input, g);
	mlx_loop(g->ptr);
}
