/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/16 17:48:37 by dpavon-g         ###   ########.fr       */
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

int	ft_close(t_game *g)
{
	exit (0);
	(void)g;
	return (0);
}

void	my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char	*dst;

	printf("coords %d, %d\n", x, y);
	if (x > 0 && x < 1080 && y > 0 && y < 720)
	{
		dst = data->addr + (y * data->line_length
				+ x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	write_line(t_game mlx)
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
		printf("%d\n", i);
		my_mlx_pixel_put(&mlx, (start_x + step_x * i)
			+ 0, (start_y + step_y * i)
			+ 0, 65439);
		i++;
	}
	printf("%d\n", i);
	(void)mlx;

}



void	init_cube(t_data *data, t_cube *cub)
{
	t_game g;


	g.ptr = mlx_init();
	g.win = mlx_new_window(g.ptr, 1080, 720, "cub3D");
	g.img = mlx_new_image(g.ptr, 1080, 720);
	mlx_hook(g.win, 17, 0, ft_close, (void *) &g);
	g.addr = mlx_get_data_addr(g.img, &g.bits_per_pixel,
			&g.line_length, &g.endian);
	// my_mlx_pixel_put(&g, 100, 100, 65439);
	
	write_line(g);
	mlx_put_image_to_window(g.ptr, g.win, g.img, 0, 0);
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
			printf("Map okay... Init cube\n");
			init_cube(&data, &cub);
			// print_matrix(data.map);
		}
		free_data(&data);
	}
	else if (argc != 2)
		printf("Error\n%s\n", ERR_ARG);
	// system("leaks -q cub3d");
	return (0);
}
