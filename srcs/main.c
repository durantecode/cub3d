/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/17 17:11:51 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_data(t_data *data)
{
	free(data->cei);
	free(data->no);
	free(data->we);
	free(data->ea);
	free(data->fl);
	free(data->so);
	free_matrix(data->map);
}

int	close_game(t_game *g)
{
	exit (0);
	(void)g;
	return (0);
}

void	my_mlx_pixel_put(t_img *mini_map, int x, int y, long color)
{
	char	*dst;
	//120, 80
	if (x >= 0 && x < MINI_MAP_WIDTH && y >= 0 && y < MINI_MAP_HEIGTH)
	{
		dst = mini_map->addr + (y * mini_map->line_len
				+ x * (mini_map->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	paint_line(t_img mini_map, t_bres bres, long color)
{
	while (bres.x < bres.end_x)
	{
		my_mlx_pixel_put(&mini_map, (bres.x)
			+ 0, (bres.y + 0)
			+ 0, color);
		bres.x++;
	}
}

int	game_status(t_game *g)
{
	// mlx_clear_window(g->ptr, g->win);

	// draw_mini_map(g);
	(void)g;
	return (0);
}


void	draw_square(t_img mini_map, t_bres bres, long color)
{
	while (bres.y < bres.end_y)
	{
		paint_line(mini_map, bres, color);
		bres.y++;
	}
}

void	draw_circle(t_img mini_map, t_bres bres)
{
	int	r;
	int i;

	i = 0;
	r = 4;
	bres.x += 6;
	bres.y += 6;
	while (i < 360)
	{
		bres.end_x = bres.x + r * cos(i);
		bres.end_y = bres.y + r * sin(i);
		write_line_bres(mini_map, bres, 16531322);
		i++;
	}
	bres.x -= 6;
	bres.y -= 6;
}

void	draw_mini_map(t_img mini_map, t_game *g)
{
	int		x;
	int		y;
	t_bres	bres;
	int		tile_size;

	y = 0;
	// if (g->size_x < MINI_MAP_WIDTH && g->size_y < MINI_MAP_HEIGTH)
		// tile_size = 
	tile_size = 12;
	ft_bzero(&bres, sizeof(t_bres));
	while (y < g->size_y)
	{
		x = 0;
		while (x < g->size_x)
		{
				bres.x = x * tile_size;
				bres.y = y * tile_size;
				bres.end_x = bres.x + tile_size;
				bres.end_y = bres.y + tile_size;
			if (g->map[y][x] == '1')
				draw_square(mini_map, bres, WALL_PURPLE);
			else if (g->map[y][x] != '1' && ft_strchr(MAP_CHAR, g->map[y][x]))
				draw_square(mini_map, bres, FLOOR_BEIGE);
			else
				draw_square(mini_map, bres, TRANSPARENT);
			if (x == g->player_x && y == g->player_y)
				draw_circle(mini_map, bres);
			x++;
		}
		y++;
	}
	(void)x;
}

int	key_input(int key, t_game *g)
{
	if (key == KEY_ESC || key == KEY_RIGHT || key == KEY_LEFT
		|| key == KEY_UP || key == KEY_DOWN)
	{		
		if (key == KEY_ESC)
		{
			close_game(g);
			return (0);
		}
	}
	return (0);
}

void	init_cube(t_data *data, t_game *g)
{
	t_img	mini_map;
	t_img	bg;

	printf("Map okay... Init cube\n");
	g->map = matrix_dup(data->map);
	free_data(data);
	g->ptr = mlx_init();
	g->win = mlx_new_window(g->ptr, WIN_WIDTH, WIN_HEIGTH, "cub3D");
	mlx_loop_hook(g->ptr, game_status, (void *) &g);
	mlx_hook(g->win, 17, 0, close_game, (void *) &g);
	mlx_key_hook(g->win, key_input, (void *) &g);
	mini_map.img = mlx_new_image(g->ptr, MINI_MAP_WIDTH, MINI_MAP_HEIGTH);
	mini_map.addr = mlx_get_data_addr(mini_map.img, &mini_map.bpp,
			&mini_map.line_len, &mini_map.endian);
	bg.img = mlx_xpm_file_to_image(g->ptr, "./textures/background.xpm", &bg.width, &bg.heigth);
	mlx_put_image_to_window(g->ptr, g->win, bg.img, 0, 0);
	draw_mini_map(mini_map, g);
	mlx_put_image_to_window(g->ptr, g->win, mini_map.img, 30, 530);
	mlx_loop(g->ptr);
	(void)data;
}

int	main(int argc, char **argv)
{
	char	**info;
	t_data	data;
	t_game	g;

	ft_bzero(&g, sizeof(t_game));
	ft_bzero(&data, sizeof(t_data));
	if (argc == 2 && !check_file_extension(argv[1], ".cub", ERR_EXT_FILE))
	{
		info = get_info(argv);
		if (!info)
			return (0);
		if (!parse_data(info, &data) && !check_data(&data, &g))
		{
			// if (load_files(&g, &data))
			// 	printf("Error\n%s\n", ERR_XPM);
			// else
				init_cube(&data, &g);
		}
		free_data(&data);
	}
	else if (argc != 2)
		printf("Error\n%s\n", ERR_ARG);
	// system("leaks -q cub3d");
	return (0);
}
