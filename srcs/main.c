/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/16 23:32:56 by ldurante         ###   ########.fr       */
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

int	game_status(t_game *g)
{
	// mlx_clear_window(g->ptr, g->win);
	
	// draw_mini_map(g);
	(void)g;
	return (0);
}

void	init_cube(t_data *data, t_cube *cub)
{
	t_game	g;

	if (load_files(&g, data))
	{
		printf("Error\n%s\n", ERR_XPM);
		return ;
	}
	g.ptr = mlx_init();
	g.win = mlx_new_window(g.ptr, 1080, 720, "cub3D");
	mlx_loop_hook(g.ptr, game_status, (void *) &g);
	mlx_hook(g.win, 17, 0, close_game, (void *) &g);
	// mlx_key_hook(g.win, key_input, (void *) &g);
	mlx_loop(g.ptr);
	(void)data;
	(void)cub;
}

int	main(int argc, char **argv)
{
	char	**info;
	t_data	data;
	t_cube	cub;

	ft_bzero(&cub, sizeof(t_cube));
	ft_bzero(&data, sizeof(t_data));
	if (argc == 2 && !check_file_extension(argv[1], ".cub", ERR_EXT_FILE))
	{
		info = get_info(argv);
		if (!info)
			return (0);
		if (!parse_data(info, &data) && !check_data(&data, &cub))
		{
			// printf("Map okay... Init cube\n");
			init_cube(&data, &cub);
		}
		free_data(&data);
	}
	else if (argc != 2)
		printf("Error\n%s\n", ERR_ARG);
	// system("leaks -q cub3d");
	return (0);
}
