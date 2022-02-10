/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:02:49 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/10 21:28:41 by dpavon-g         ###   ########.fr       */
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

int		parse_data_aux(t_data *data, char ***aux)
{
	if ((*aux)[0])
	{
		if (!ft_strncmp((*aux)[0], "NO", 3) && !data->no)
			data->no = matrix_dup((*aux));
		else if (!ft_strncmp((*aux)[0], "SO", 3) && !data->so)
			data->so = matrix_dup((*aux));
		else if (!ft_strncmp((*aux)[0], "WE", 3) && !data->we)
			data->we = matrix_dup((*aux));
		else if (!ft_strncmp((*aux)[0], "EA", 3) && !data->ea)
			data->ea = matrix_dup((*aux));
		else if (!ft_strncmp((*aux)[0], "F", 2) && !data->fl)
			data->fl = matrix_dup((*aux));
		else if (!ft_strncmp((*aux)[0], "C", 2) && !data->cei)
			data->cei = matrix_dup((*aux));
		else
		{
			printf("Error: invalid map identifier\n");
			free_matrix ((*aux));
			return (1);
		}
		free_matrix((*aux));
		(*aux) = NULL;
	}
	return (0);
}

void	get_map(char **info, t_data *data)
{
	int		i;
	char	**aux;
	
	i = 0;
	while (info[i])
	{
		if (info[i][0])
		{
			aux = ft_split(info[i], ' ');
			if (aux[0])
			{
				free_matrix(aux);
				break;
			}
		}
		i++;
	}
	data->map = info + i;
	(void)data;
}

void	parse_data(char **info, t_data *data)
{
	int		i;
	int		err;
	char	**aux;

	i = -1;
	err = 0;
	aux = NULL;
	while (info[++i])
	{
		if (data->no && data->so && data->we && data->ea && data->fl
		&& data->cei)
			break;
		if (info[i][0])
		{
			aux = ft_split(info[i], ' ');
			if (parse_data_aux(data, &aux))
			{
				err = 1;
				break;
			}
			free_matrix(aux);
		}
	}
	if (err == 0)
		get_map(info + i, data);
}

int	main(int argc, char **argv)
{
	char	**info;
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc != 2)
	{
		printf("Error\n");
		return (1);
	}
	info = get_info(argv);
	parse_data(info, &data);
	free_matrix(info);
	// system("leaks -q cub3d");
	return (0);
}
