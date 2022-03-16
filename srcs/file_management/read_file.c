/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:13:11 by pavon             #+#    #+#             */
/*   Updated: 2022/03/16 11:59:56 by ldurante         ###   ########.fr       */
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

static char	**get_info_aux(int ret, char **line, int fd)
{
	char	**info;
	char	**aux;
	int		empty;

	info = NULL;
	empty = 0;
	while (ret >= 0)
	{
		if (*line[0])
			empty = 1;
		aux = ft_realloc(info, line);
		free_matrix(info);
		info = matrix_dup(aux);
		free_matrix(aux);
		if (ret == 0)
			break ;
		ret = get_next_line(fd, line);
	}
	if (empty)
		return (info);
	free_matrix(info);
	return (NULL);
}

char	**get_info(char **argv)
{
	char	**info;
	int		fd;
	char	*line;
	int		ret;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		printf("Error\n%s\n", ERR_FILE);
	ret = get_next_line(fd, &line);
	if (!ret)
	{
		printf("Error\n%s\n", ERR_MAP_EMPTY);
		close(fd);
		return (NULL);
	}
	info = get_info_aux(ret, &line, fd);
	close(fd);
	return (info);
}
