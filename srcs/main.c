/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/10 18:24:00 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

char	**ft_realloc(char **map, char **line)
{
	int		size;
	char	**aux;
	int		i;

	i = 0;
	aux = NULL;
	if (!(map))
	{
		aux = malloc(sizeof(char *) * 2);
		aux[0] = *line;
		aux[1] = NULL;
		return (aux);
	}
	size = matrix_len(map);
	aux = malloc(sizeof(char *) * (size + 2));
	while (i < size)
	{
		aux[i] = ft_strdup(map[i]);
		i++;
	}	
	aux[size] = *line;
	aux[size + 1] = NULL;
	return (aux);
}

char	**get_info(char **argv)
{
	int		fd;
	char	**map;
	char	*line;
	char	**aux;
	int		ret;

	line = NULL;
	map = NULL;
	fd = open(argv[1], O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret >= 0)
	{
		aux = ft_realloc(map, &line);
		free_matrix(map);
		map = matrix_dup(aux);
		free_matrix(aux);
		if (ret == 0)
			break;
		ret = get_next_line(fd, &line);
	}
	close(fd);
	return (map);
}

int	main(int argc, char **argv)
{
	char	**map;

	if (argc != 2)
	{
		printf("Error\n");
		return (1);
	}
	map = get_info(argv);
	free_matrix(map);
	return (0);
}
