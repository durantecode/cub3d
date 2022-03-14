/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:44:30 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/14 11:45:05 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static int	player_collision_with_wall(t_game *g, int coord, int key)
// {
// 	t_vector	vector;

// 	if (coord == 'x' && key == 'w')
// 		g->player.move_x += g->player.step_vx;
// 	else if (coord == 'y' && key == 'w')
// 		g->player.move_y += g->player.step_vy;
// 	else if (coord == 'x' && key == 's')
// 		g->player.move_x += g->player.step_vx;
// 	else if (coord == 'y' && key == 's')
// 		g->player.move_y += g->player.step_vy;
// 	else if (coord == 'x' && key == 'a')
// 		g->player.move_x += g->player.step_vx;
// 	else if (coord == 'y' && key == 'a')
// 		g->player.move_y += g->player.step_vy;
// 	else if (coord == 'x' && key == 'd')
// 		g->player.move_x += g->player.step_vx;
// 	else if (coord == 'y' && key == 'd')
// 		g->player.move_y += g->player.step_vy;
// 	vector = get_map_vector(g, g->player.move_x, g->player.move_y);
// 	if (g->map[vector.y / TILE_SIZE][vector.x / TILE_SIZE] == '1')
// 		return (1);
// 	return (0);
// }

// static void	move_forward_back(t_game *g, int key)
// {
// 	if (key == KEY_W)
// 	{
// 		if (player_collision_with_wall(g, 'x', 'w'))
// 			g->player.move_x -= g->player.step_vx;
// 		if (player_collision_with_wall(g, 'y', 'w'))
// 			g->player.move_y -= g->player.step_vy;
// 	}
// 	else if (key == KEY_S)
// 	{
// 		if (player_collision_with_wall(g, 'x', 's'))
// 			g->player.move_x -= g->player.step_vx;
// 		if (player_collision_with_wall(g, 'y', 's'))
// 			g->player.move_y -= g->player.step_vy;
// 	}
// }

// static void	move_left_right(t_game *g, int key)
// {
// 	if (key == KEY_A)
// 	{
// 		if (player_collision_with_wall(g, 'x', 'a'))
// 			g->player.move_x -= g->player.step_vx;
// 		if (player_collision_with_wall(g, 'y', 'a'))
// 			g->player.move_y -= g->player.step_vy;
// 	}
// 	else if (key == KEY_D)
// 	{
// 		if (player_collision_with_wall(g, 'x', 'd'))
// 			g->player.move_x -= g->player.step_vx;
// 		if (player_collision_with_wall(g, 'y', 'd'))
// 			g->player.move_y -= g->player.step_vy;
// 	}
// }

static void	move_player(t_game *g, int key)
{
	t_vector vector;
	float	angle;
	float	newX;
	float	newY;
	float	checkX;
	float	checkY;

	angle = g->player.angle;
	if (key == KEY_S)
		angle = g->player.angle - DEGREES_180;
	if (key == KEY_A)
		angle = g->player.angle - DEGREES_90;
	if (key == KEY_D)
		angle = g->player.angle + DEGREES_90;
	g->player.step_vx = cos(angle) * PLAYER_SPEED;
	g->player.step_vy = sin(angle) * PLAYER_SPEED;
	newX = g->player.move_x + g->player.step_vx;
	newY = g->player.move_y + g->player.step_vy;
	checkX = floor(newX + g->player.step_vx);
	checkY = floor(newY + g->player.step_vy);
	// vector = get_map_vector(g, g->player.move_x, checkY);
	if (g->map[(int)checkY][g->player.x] != '1')
        g->player.move_y = newY;
	vector = get_map_vector(g, checkX, g->player.move_y);
	if (g->map[g->player.y][(int)checkX] != '1')
        g->player.move_x = newX;
	(void)key;
}

void	check_movement(t_game *g)
{
	if (g->player.key.w)
		move_player(g, KEY_W);
	if (g->player.key.s)
		move_player(g, KEY_S);
	if (g->player.key.a)
		move_player(g, KEY_A);
	if (g->player.key.d)
		move_player(g, KEY_D);
	if (g->player.key.left)
		g->player.angle -= PLAYER_ROTATE;
	if (g->player.key.right)
		g->player.angle += PLAYER_ROTATE;
}
