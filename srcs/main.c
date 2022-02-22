/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/22 02:43:10 by ldurante         ###   ########.fr       */
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
	if (x >= 0 && x < MINI_MAP_WIDTH && y >= 0 && y < MINI_MAP_HEIGHT)
	{
		dst = mini_map->addr + (y * mini_map->line_len
				+ x * (mini_map->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_game *g, t_bres bres, t_img mini_map)
{
	bres.x = 93;
	bres.y = 90;
	bres.end_x = g->rotate_x;
	bres.end_y = g->rotate_y;
	write_line_bres(mini_map, bres, RAY_GREY);

	// while (bres.x < bres.end_x)
	// {
	// 	my_mlx_pixel_put(&mini_map, (bres.x)
	// 		+ g->rotate, (bres.y)
	// 		+ g->rotate, RAY_GREY);
	// 	bres.x++;
	// }
	(void)g;
}

void	draw_circle(t_img mini_map)
{
	float	i;
	float	r;
	t_bres	bres;
	
	bres.x = 90;
	bres.y = 90;
	i = 0;
	r = 3.5;
	bres.x += 4;
	bres.y += 4;
	while (i < 360)
	{
		bres.end_x = bres.x + r * cos(i);
		bres.end_y = bres.y + r * sin(i);
		write_line_bres(mini_map, bres, PLAYER_RED);
		i++;
	}
}

void	draw_mini_map(t_img mini_map, t_game *g)
{
	float	x;
	float	x1;
	float	y;
	float	y1;
	t_bres	bres;
	int		tile_size;

	tile_size = 9;
	ft_bzero(&bres, sizeof(t_bres));
	y = (g->player_y * tile_size - 89) + g->move_pos_y;
	y1 = 0;
	while (y < MINI_MAP_HEIGHT * tile_size)
	{
		x = (g->player_x * tile_size - 89) + g->move_pos_x;
		x1 = 0;
		while (x < MINI_MAP_WIDTH * tile_size)
		{
			if (y / tile_size < g->size_y && x / tile_size < g->size_x
				&& y / tile_size >= 0 && x / tile_size >= 0)
			{
				if (g->map[(int)y / tile_size][(int)x / tile_size] == '1')
					my_mlx_pixel_put(&mini_map, x1, y1, WALL_PURPLE);
				else if (g->map[(int)y / tile_size][(int)x / tile_size] == ' ')
					my_mlx_pixel_put(&mini_map, x1, y1, TRANSPARENT);
				else 
					my_mlx_pixel_put(&mini_map, x1, y1, FLOOR_BEIGE);
			}
			else
				my_mlx_pixel_put(&mini_map, x1, y1, TRANSPARENT);
			x1++;
			x++;
		}
		y++;
		y1++;
	}
	draw_circle(mini_map);
	draw_line(g, bres, mini_map);
}

void	check_pos(t_game *g, int key)
{
	float	y;
	float	x;
	y = ((g->player_y * 9)) + g->move_pos_y;
	x = ((g->player_x * 9)) + g->move_pos_x;
	printf("%f, %f\n\n", y/9, x/9);
	if (key == KEY_W)
	{
		g->move_pos_y -= 3;
		y = ((g->player_y * 9)) + g->move_pos_y + 3.5;
		x = ((g->player_x * 9)) + g->move_pos_x + 3.5;
		if (g->map[(int)(y/9)][(int)(x/9)] == '1')
	   		g->move_pos_y += 3;
	}
	else if (key == KEY_S)
	{
		g->move_pos_y += 3;
		y = ((g->player_y * 9)) + g->move_pos_y + 3.5;
		x = ((g->player_x * 9)) + g->move_pos_x + 3.5;
		if (g->map[(int)(y/9)][(int)(x/9)] == '1')
   			g->move_pos_y -= 3;
	}
	else if (key == KEY_A)
	{
		g->move_pos_x -= 3;
		y = ((g->player_y * 9)) + g->move_pos_y + 3.5;
		x = ((g->player_x * 9)) + g->move_pos_x + 3.5;
		if (g->map[(int)(y/9)][(int)(x/9)] == '1')
        	g->move_pos_x += 3;
	}
	else if (key == KEY_D)
	{
		g->move_pos_x += 3;
		y = ((g->player_y * 9)) + g->move_pos_y + 3.5;
		x = ((g->player_x * 9)) + g->move_pos_x + 3.5;
		if (g->map[(int)(y/9)][(int)(x/9)] == '1')
			g->move_pos_x -= 3;
	}
		printf("%f, %f\n\n", y/9, x/9);
}

int	mouse_input(int mouse, t_game *g)
{
	(void)g;
	(void)mouse;
	return (0);
}

int	key_input(int key, t_game *g)
{
	if (key == KEY_ESC || key == KEY_D || key == KEY_A
		|| key == KEY_W || key == KEY_S
		|| key == KEY_LEFT || key == KEY_RIGHT)
	{		
		if (key == KEY_ESC)
		{
			close_game(g);
			return (0);
		}
		else
			check_pos(g, key);
		// if (key == KEY_UP)
		// 	g->move_pos_y -= 3;
		// if (key == KEY_DOWN)
		// 	g->move_pos_y += 3;
		if (key == KEY_LEFT)
		{
			g->rotate_x--;
			g->rotate_y++;
		}
		if (key == KEY_RIGHT)
		{
			g->rotate_x++;
			g->rotate_y--;
		}
		// if (key == KEY_RIGHT)
		// 	g->move_pos_x += 3;
		// re_write(g);
		return (1);
	}
	else
		return (0);
}

int	game_status(t_game *g)
{
	t_img	mini_map;

	mlx_clear_window(g->ptr, g->win);
	mini_map.img = mlx_new_image(g->ptr, MINI_MAP_WIDTH, MINI_MAP_HEIGHT);
	mini_map.addr = mlx_get_data_addr(mini_map.img, &mini_map.bpp,
			&mini_map.line_len, &mini_map.endian);
	draw_mini_map(mini_map, g);
	mlx_put_image_to_window(g->ptr, g->win, mini_map.img, 30, 490);
	return (0);
}

void	init_cube(t_data *data, t_game *g)
{
	t_img	mini_map;

	ft_bzero(&mini_map, sizeof(t_img));
	g->mini_map = mini_map;
	printf("Map okay... Init cube\n");
	g->map = matrix_dup(data->map);
	free_data(data);
	g->ptr = mlx_init();
	g->rotate_x = 90;
	g->rotate_x = 93;
	g->win = mlx_new_window(g->ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	mlx_loop_hook(g->ptr, game_status, g);
	mlx_hook(g->win, 17, 0, close_game, g);
	mlx_hook(g->win, 2, 1L<<0, key_input, g);
	mlx_hook(g->win, 6, 1L<<6, mouse_input, g);
	// mlx_key_hook(g->win, key_input, g);
	mlx_loop(g->ptr);
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
