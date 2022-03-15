/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:53:25 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/15 17:30:43 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**add_spaces(char **m, char **resized_m, int max_len, int map_len)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map_len)
	{
		j = 0;
		resized_m[i] = malloc(sizeof(char *) * max_len + 1);
		if (!resized_m[i])
			return (NULL);
		while (m[i][j] != '\0')
		{
			resized_m[i][j] = m[i][j];
			j++;
		}
		while (j < max_len)
		{	
			resized_m[i][j] = ' ';
			j++;
		}
		resized_m[i][j] = '\0';
	}
	return (resized_m);
}

static int	max_row(char **first_map)
{
	int	i;
	int	len;

	i = 0;
	while (first_map[i])
	{
		if (first_map[i][0])
			len = i;
		i++;
	}
	return (len + 1);
}

static int	longest_row(char **first_map)
{
	int	i;
	int	j;
	int	len;
	int	prev_len;

	i = 0;
	prev_len = 0;
	while (first_map[i])
	{
		j = 0;
		while (first_map[i][j])
		{
			if (first_map[i][j] != ' ' && first_map[i][j] != '\0')
				len = j;
			j++;
		}
		if (len > prev_len)
			prev_len = len;
		i++;
	}
	return (prev_len + 1);
}

static char	**format_map(char **first_map, char ***map)
{
	int		max_len;
	int		map_len;
	char	**resized_map;

	max_len = longest_row(first_map);
	map_len = max_row(first_map);
	resized_map = malloc(sizeof(char *) * (map_len + 1));
	if (!resized_map)
		return (NULL);
	resized_map[map_len] = NULL;
	*map = add_spaces(first_map, resized_map, max_len, map_len);
	return ((*map));
}

void	get_map(char **info, t_data *data, int err)
{
	int		i;
	char	**aux;

	i = 0;
	if (err)
	{
		printf("Error\n%s\n", ERR_ID);
		return ;
	}
	while (info[i])
	{
		if (info[i][0])
		{
			aux = ft_split(info[i], ' ');
			if (aux[0])
			{
				free_matrix(aux);
				break ;
			}
			free_matrix(aux);
		}
		i++;
	}
	format_map(info, &data->map);
}
