/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:18:13 by pavon             #+#    #+#             */
/*   Updated: 2022/02/16 17:47:58 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_data_aux(t_data *data, char ***aux)
{
	if ((*aux)[0])
	{
		if (!ft_strncmp((*aux)[0], "NO", 3) && !data->no)
			data->no = ft_strdup((*aux)[1]);
		else if (!ft_strncmp((*aux)[0], "SO", 3) && !data->so)
			data->so = ft_strdup((*aux)[1]);
		else if (!ft_strncmp((*aux)[0], "WE", 3) && !data->we)
			data->we = ft_strdup((*aux)[1]);
		else if (!ft_strncmp((*aux)[0], "EA", 3) && !data->ea)
			data->ea = ft_strdup((*aux)[1]);
		else if (!ft_strncmp((*aux)[0], "F", 2) && !data->fl)
			data->fl = ft_strdup((*aux)[1]);
		else if (!ft_strncmp((*aux)[0], "C", 2) && !data->cei)
			data->cei = ft_strdup((*aux)[1]);
		else
			return (1);
		free_matrix((*aux));
		(*aux) = NULL;
	}
	return (0);
}

static int	all_id_parsed(t_data *data)
{
	if (data->no && data->so && data->we && data->ea && data->fl
		&& data->cei)
		return (1);
	return (0);
}

int	parse_data(char **info, t_data *data)
{
	int		i;
	int		err;
	char	**aux;
	char	**info_ptr;

	i = -1;
	err = 0;
	aux = NULL;
	info_ptr = info;
	while (info[++i])
	{
		if (all_id_parsed(data))
			break ;
		if (info[i][0])
		{
			aux = ft_split(info[i], ' ');
			if (((matrix_len(aux) != 2 && (++err)))
				|| (parse_data_aux(data, &aux) && (++err)))
			{
				free_matrix(aux);
				break ;
			}
			free_matrix(aux);
		}
	}
	get_map(info + i, data, err);
	free_matrix(info_ptr);
	return (err);
}
