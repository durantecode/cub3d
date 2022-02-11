/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavon <pavon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:20:13 by pavon             #+#    #+#             */
/*   Updated: 2022/02/11 12:23:17 by pavon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_file_extension(char *argv, char *ext)
{
	int		len;
	char	*aux;

	len = ft_strlen(argv);
	aux = ft_substr(argv, len - 4, len);
	if (ft_strcmp(aux, ext))
	{
		printf("Error\n%s\n", ERR_EXT);
		free(aux);
		exit (0);
	}
	free(aux);
	return (0);
}
