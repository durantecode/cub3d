/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:56:06 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/14 10:45:13 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_vector	get_map_vector(t_game *g, float x, float y)
{
	t_vector	vector;

	vector.x = (g->player.x * TILE_SIZE) + floor(x + PLAYER_RADIUS);
	vector.y = (g->player.y * TILE_SIZE) + floor(y + PLAYER_RADIUS);
	return (vector);
}
