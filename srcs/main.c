/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/15 17:10:20 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	leaks(void)
{
	system("leaks -q cub3D");
}

void	free_data(t_data *data)
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
	mlx_destroy_image(g->ptr, g->bg.img);
	mlx_destroy_image(g->ptr, g->mini_map.img);
	mlx_destroy_image(g->ptr, g->tex.no.img);
	mlx_destroy_image(g->ptr, g->tex.so.img);
	mlx_destroy_image(g->ptr, g->tex.ea.img);
	mlx_destroy_image(g->ptr, g->tex.we.img);
	mlx_destroy_window(g->ptr, g->win);
	free_matrix(g->map);
	exit (0);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**info;
	t_data	data;
	t_game	g;

	atexit(leaks);
	ft_bzero(&g, sizeof(t_game));
	ft_bzero(&data, sizeof(t_data));
	g.ptr = mlx_init();
	if (argc == 2 && !check_file_extension(argv[1], ".cub", ERR_EXT_FILE))
	{
		info = get_info(argv);
		if (!info)
			return (0);
		if (!parse_data(info, &data) && !check_data(&data, &g))
		{
			if (load_files(&g, &data))
				printf("Error\n%s\n", ERR_XPM);
			else
				init_cube(&data, &g);
		}
		free_data(&data);
	}
	else if (argc != 2)
		printf("Error\n%s\n", ERR_ARG);
	return (0);
}
