/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/10 18:41:20 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

char	**ft_realloc(char **info, char **line)
{
	int		size;
	char	**aux;
	int		i;

	i = 0;
	aux = NULL;
	if (!(info))
	{
		aux = malloc(sizeof(char *) * 2);
		aux[0] = *line;
		aux[1] = NULL;
		return (aux);
	}
	size = matrix_len(info);
	aux = malloc(sizeof(char *) * (size + 2));
	while (i < size)
	{
		aux[i] = ft_strdup(info[i]);
		i++;
	}	
	aux[size] = *line;
	aux[size + 1] = NULL;
	return (aux);
}

char	**get_info(char **argv)
{
	int		fd;
	char	**info;
	char	*line;
	char	**aux;
	int		ret;

	line = NULL;
	info = NULL;
	fd = open(argv[1], O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret >= 0)
	{
		aux = ft_realloc(info, &line);
		free_matrix(info);
		info = matrix_dup(aux);
		free_matrix(aux);
		if (ret == 0)
			break;
		ret = get_next_line(fd, &line);
	}
	close(fd);
	return (info);
}

int	main(int argc, char **argv)
{
	char	**info;

	if (argc != 2)
	{
		printf("Error\n");
		return (1);
	}
	info = get_info(argv);
	free_matrix(info);
	return (0);
}
