/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:56:06 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/24 15:00:53 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_vector get_map_vector(t_game *g)
{
	t_vector vector;

	vector.y = (g->player_y * TILE_SIZE) + g->move_pos_y + PLAYER_RADIUS;
	vector.x = (g->player_x * TILE_SIZE) + g->move_pos_x + PLAYER_RADIUS;
	return(vector);
}
