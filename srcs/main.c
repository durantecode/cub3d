/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/17 12:38:37 by dpavon-g         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_img *mini_map, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < 1080 && y > 0 && y < 720)
	{
		dst = mini_map->addr + (y * mini_map->line_len
				+ x * (mini_map->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	write_line(t_img mini_map)
{
	int		start_x = 0;
	int		start_y = 0;
	int		end_x = 100;
	int		end_y = 100;
	float	step_x;
	float	step_y;
	float	dist;
	int		i;

	dist = sqrt(pow(start_x - end_x, 2) + pow(start_y - end_y, 2));
	step_x = (end_x - start_x) / dist;
	step_y = (end_y - start_y) / dist;
	i = 0;
	while (i < dist)
	{
		my_mlx_pixel_put(&mini_map, (start_x + step_x * i)
			+ 0, (start_y + step_y * i)
			+ 0, 65439);
		i++;
	}
}

int	game_status(t_game *g)
{
	// mlx_clear_window(g->ptr, g->win);
	
	// draw_mini_map(g);
	(void)g;
	return (0);
}

void	init_cube(t_data *data, t_game *g)
{
	t_img	mini_map;

	printf("Map okay... Init cube\n");
	g->map = matrix_dup(data->map);
	free_data(data);
	g->ptr = mlx_init();
	g->win = mlx_new_window(g->ptr, 1080, 720, "cub3D");
	mlx_loop_hook(g->ptr, game_status, (void *) &g);
	mlx_hook(g->win, 17, 0, close_game, (void *) &g);
	// mlx_key_hook(g->win, key_input, (void *) &g);
	mini_map.img = mlx_new_image(g->ptr, 1080, 720);
	mini_map.addr = mlx_get_data_addr(mini_map.img, &mini_map.bpp,
			&mini_map.line_len, &mini_map.endian);
	write_line(mini_map);
	mlx_put_image_to_window(g->ptr, g->win, mini_map.img, 0, 0);
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
