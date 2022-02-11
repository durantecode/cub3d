/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavon <pavon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:13:11 by pavon             #+#    #+#             */
/*   Updated: 2022/02/11 13:02:23 by pavon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**ft_realloc(char **info, char **line)
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
	if (fd < 0)
		printf("Error\n%s\n", ERR_FILE);
	ret = get_next_line(fd, &line);
	while (ret >= 0)
	{
		aux = ft_realloc(info, &line);
		free_matrix(info);
		info = matrix_dup(aux);
		free_matrix(aux);
		if (ret == 0)
			break ;
		ret = get_next_line(fd, &line);
	}
	if (fd != -1)
		close(fd);
	return (info);
}
