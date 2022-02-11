/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavon <pavon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/11 16:35:25 by pavon            ###   ########.fr       */
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

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_colors(char *str, int *cub)
{
	int		i;
	char	**split_comma;

	i = 0;
	split_comma = ft_split(str, ',');
	if (matrix_len(split_comma) != 3)
	{
		print_matrix(split_comma);
		free_matrix(split_comma);
		return (1);
	}
	while (split_comma[i])
	{
		if (!str_is_digit(split_comma[i]))
		{
			printf("Error\n");
			free_matrix(split_comma);
			return (1);
		}
		i++;
	}
	free_matrix(split_comma);
	(void)cub;
	return (0);
}

int	check_data(t_data *data, t_cube *cub)
{
	if (check_file_extension(data->no, ".xpm", ERR_EXT_ID))
		return (1);
	if (check_file_extension(data->so, ".xpm", ERR_EXT_ID))
		return (1);
	if (check_file_extension(data->we, ".xpm", ERR_EXT_ID))
		return (1);
	if (check_file_extension(data->ea, ".xpm", ERR_EXT_ID))
		return (1);
	if (check_colors(data->fl, &(cub->fl_dec)))
		return (1);
	return (0);
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
			print_matrix(data.map);
		}
		free_data(&data);
	}
	else if (argc != 2)
		printf("Error\n%s\n", ERR_ARG);
	// system("leaks -q cub3d");
	return (0);
}
