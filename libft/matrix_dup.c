/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 23:32:24 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/10 17:27:53 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**matrix_dup(char **matrix)
{
	char	**out;
	int		size;
	int		i;

	i = 0;
	size = matrix_len(matrix);
	out = malloc(sizeof(char *) * (size + 1));
	if (!out)
		return (NULL);
	while (matrix[i])
	{
		out[i] = ft_strdup(matrix[i]);
		if (!out[i])
		{
			free_matrix(out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}
