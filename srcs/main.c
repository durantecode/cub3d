/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/16 12:01:58 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_data(t_data *data)
{
	if (data->no)
		free(data->no);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->so)
		free(data->so);
	if (data->cei)
		free(data->cei);
	if (data->fl)
		free(data->fl);
	if (data->map)
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

int	check_xpm_files(t_data *data)
{
	int	fd;

	fd = open(data->no, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(data->so, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(data->ea, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(data->we, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
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
			if (check_xpm_files(&data))
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
