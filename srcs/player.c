/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:44:30 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/15 15:44:28 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move_player(t_game *g, int dir, float angle)
{
	float	new_pos_x;
	float	new_pos_y;
	float	check_pos_x;
	float	check_pos_y;

	g->player.step_x = dir * (cos(angle) * PLAYER_SPEED);
	g->player.step_y = dir * (sin(angle) * PLAYER_SPEED);
	new_pos_x = g->player.x + g->player.step_x;
	new_pos_y = g->player.y + g->player.step_y;
	check_pos_x = g->player.x + 0.5 + (5 * g->player.step_x);
	check_pos_y = g->player.y + 0.5 + (5 * g->player.step_y);
	if (g->map[(int)check_pos_y][(int)(g->player.x + 0.5)] != '1')
		g->player.y = new_pos_y;
	if (g->map[(int)(g->player.y + 0.5)][(int)check_pos_x] != '1')
		g->player.x = new_pos_x;
}

void	check_movement(t_game *g)
{
	if (g->player.key.w)
		move_player(g, 1, g->player.angle);
	if (g->player.key.s)
		move_player(g, -1, g->player.angle);
	if (g->player.key.a)
		move_player(g, -1, g->player.angle + DEGREES_90);
	if (g->player.key.d)
		move_player(g, 1, g->player.angle + DEGREES_90);
	if (g->player.key.left)
		g->player.angle -= PLAYER_ROTATE;
	if (g->player.key.right)
		g->player.angle += PLAYER_ROTATE;
}
