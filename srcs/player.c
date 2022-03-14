/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:44:30 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/14 20:38:46 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static int	player_collision_with_wall(t_game *g, int coord, int key)
// {
// 	// t_vector	vector;

// 	if (coord == 'x' && key == 'w')
// 		g->player.x += g->player.step_vx;
// 	else if (coord == 'y' && key == 'w')
// 		g->player.y += g->player.step_vy;
// 	else if (coord == 'x' && key == 's')
// 		g->player.x += g->player.step_vx;
// 	else if (coord == 'y' && key == 's')
// 		g->player.y += g->player.step_vy;
// 	else if (coord == 'x' && key == 'a')
// 		g->player.x += g->player.step_vx;
// 	else if (coord == 'y' && key == 'a')
// 		g->player.y += g->player.step_vy;
// 	else if (coord == 'x' && key == 'd')
// 		g->player.x += g->player.step_vx;
// 	else if (coord == 'y' && key == 'd')
// 		g->player.y += g->player.step_vy;
// 	// vector = get_map_vector(g, g->player.x, g->player.y);
// 	if (g->map[(int)floor(g->player.y)][(int)floor(g->player.x)] == '1')
// 		return (1);
// 	return (0);
// }

// static void	move_forward_back(t_game *g, int key)
// {
// 	if (key == KEY_W)
// 	{
// 		if (player_collision_with_wall(g, 'x', 'w'))
// 			g->player.x -= g->player.step_vx;
// 		if (player_collision_with_wall(g, 'y', 'w'))
// 			g->player.y -= g->player.step_vy;
// 	}
// 	else if (key == KEY_S)
// 	{
// 		if (player_collision_with_wall(g, 'x', 's'))
// 			g->player.x -= g->player.step_vx;
// 		if (player_collision_with_wall(g, 'y', 's'))
// 			g->player.y -= g->player.step_vy;
// 	}
// }

// static void	move_left_right(t_game *g, int key)
// {
// 	if (key == KEY_A)
// 	{
// 		if (player_collision_with_wall(g, 'x', 'a'))
// 			g->player.x -= g->player.step_vx;
// 		if (player_collision_with_wall(g, 'y', 'a'))
// 			g->player.y -= g->player.step_vy;
// 	}
// 	else if (key == KEY_D)
// 	{
// 		if (player_collision_with_wall(g, 'x', 'd'))
// 			g->player.x -= g->player.step_vx;
// 		if (player_collision_with_wall(g, 'y', 'd'))
// 			g->player.y -= g->player.step_vy;
// 	}
// }

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
