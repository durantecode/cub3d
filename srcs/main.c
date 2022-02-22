/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/22 16:20:31 by ldurante         ###   ########.fr       */
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

void	draw_line(t_game *g, t_img img)
{
	float	r;
	t_bres	bres;

	ft_bzero(&bres, sizeof(t_bres));
	bres.x = MINI_MAP_HALF + TILE_SIZE / 2;
	bres.y = MINI_MAP_HALF + TILE_SIZE / 2;
	r = 0;
	bres.end_x = bres.x + r * cos(g->rotate);
	bres.end_y = bres.y + r * sin(g->rotate);
	while (g->map[bres.end_y / TILE_SIZE][bres.end_x / TILE_SIZE] != '1')
	{
		bres.end_x = bres.x + r * cos(g->rotate);
		bres.end_y = bres.y + r * sin(g->rotate);
		r++;
	}
	printf("%f\n", r);
	printf("%d, %d\n", bres.end_y, bres.end_x);
	write_line_bres(img, bres, PLAYER_RED);
}

void	draw_circle(t_img img)
{
	float	i;
	float	r;
	t_bres	bres;
	
	ft_bzero(&bres, sizeof(t_bres));
	bres.x = MINI_MAP_CENTER + TILE_SIZE / 2;
	bres.y = MINI_MAP_CENTER + TILE_SIZE / 2;
	i = 0;
	r = PLAYER_RADIUS;
	while (i < 360)
	{
		bres.end_x = bres.x + r * cos(i);
		bres.end_y = bres.y + r * sin(i);
		write_line_bres(img, bres, PLAYER_RED);
		i++;
	}
}

void	draw_mini_map(t_img mini_map, t_game *g)
{
	float	x;
	float	x1;
	float	y;
	float	y1;

	y = (g->player_y * TILE_SIZE - MINI_MAP_HALF) + g->move_pos_y;
	y1 = 0;
	while (y < MINI_MAP_HEIGHT * TILE_SIZE)
	{
		x = (g->player_x * TILE_SIZE - MINI_MAP_HALF) + g->move_pos_x;
		x1 = 0;
		while (x < MINI_MAP_WIDTH * TILE_SIZE)
		{
			if (y / TILE_SIZE < g->size_y && x / TILE_SIZE < g->size_x
				&& y / TILE_SIZE >= 0 && x / TILE_SIZE >= 0)
			{
				if (g->map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] == '1')
					my_mlx_pixel_put(&mini_map, x1, y1, WALL_PURPLE);
				else if (g->map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] == ' ')
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
	draw_line(g, mini_map);
}

void	check_pos(t_game *g, int key)
{
	float	y;
	float	x;
	if (key == KEY_W)
	{
		g->move_pos_y -= 3;
		y = ((g->player_y * TILE_SIZE)) + g->move_pos_y + PLAYER_RADIUS;
		x = ((g->player_x * TILE_SIZE)) + g->move_pos_x + PLAYER_RADIUS;
		if (g->map[(int)(y/TILE_SIZE)][(int)(x/TILE_SIZE)] == '1')
	   		g->move_pos_y += 3;
	}
	else if (key == KEY_S)
	{
		g->move_pos_y += 3;
		y = ((g->player_y * TILE_SIZE)) + g->move_pos_y + PLAYER_RADIUS;
		x = ((g->player_x * TILE_SIZE)) + g->move_pos_x + PLAYER_RADIUS;
		if (g->map[(int)(y/TILE_SIZE)][(int)(x/TILE_SIZE)] == '1')
   			g->move_pos_y -= 3;
	}
	else if (key == KEY_A)
	{
		g->move_pos_x -= 3;
		y = ((g->player_y * TILE_SIZE)) + g->move_pos_y + PLAYER_RADIUS;
		x = ((g->player_x * TILE_SIZE)) + g->move_pos_x + PLAYER_RADIUS;
		if (g->map[(int)(y/TILE_SIZE)][(int)(x/TILE_SIZE)] == '1')
        	g->move_pos_x += 3;
	}
	else if (key == KEY_D)
	{
		g->move_pos_x += 3;
		y = ((g->player_y * TILE_SIZE)) + g->move_pos_y + PLAYER_RADIUS;
		x = ((g->player_x * TILE_SIZE)) + g->move_pos_x + PLAYER_RADIUS;
		if (g->map[(int)(y/TILE_SIZE)][(int)(x/TILE_SIZE)] == '1')
			g->move_pos_x -= 3;
	}
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
		if (key == KEY_LEFT)
		{
			g->rotate -= 0.08;
		}
		if (key == KEY_RIGHT)
		{
			g->rotate += 0.08;
		}
		return (1);
	}
	else
		return (0);
}

void	draw_bg(t_img bg, int ceiling, int floor)
{
	int x;
	int y;
	int texture;

	y = 0;
	texture = ceiling;
	while (y < bg.height)
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

int	game_status(t_game *g)
{
	t_img	mini_map;
	t_img	bg;

	mlx_clear_window(g->ptr, g->win);
	bg.width = WIN_WIDTH;
	bg.height = WIN_HEIGHT;
	bg.img = mlx_new_image(g->ptr, bg.width, bg.height);
	bg.addr = mlx_get_data_addr(bg.img, &bg.bpp,
			&bg.line_len, &bg.endian);
	draw_bg(bg, g->tex.ceiling, g->tex.floor);
	mini_map.width = MINI_MAP_WIDTH;
	mini_map.height = MINI_MAP_HEIGHT;
	mini_map.img = mlx_new_image(g->ptr, mini_map.width, mini_map.height);
	mini_map.addr = mlx_get_data_addr(mini_map.img, &mini_map.bpp,
			&mini_map.line_len, &mini_map.endian);
	draw_mini_map(mini_map, g);
	mlx_put_image_to_window(g->ptr, g->win, bg.img, 0, 0);
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
	// g->rotate = 90;
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
