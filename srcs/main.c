/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavon <pavon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/11 12:52:31 by pavon            ###   ########.fr       */
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

int	check_data(t_data *data)
{
	(void)data;
	return (0);
}

int	main(int argc, char **argv)
{
	char	**info;
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc == 2 && !check_file_extension(argv[1], ".cub"))
	{
		info = get_info(argv);
		if (!info)
			return (0);
		if (!parse_data(info, &data) && !check_data(&data))
			printf("Map okay... Init cube\n");
		free_data(&data);
	}
	else
		printf("Error\n%s\n", ERR_ARG);
	// system("leaks -q cub3d");
	return (0);
}
