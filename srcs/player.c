/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:44:30 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/08 18:39:54 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	player_collision_with_wall(t_game *g, int coord, int key)
{
	t_vector	vector;

	if (coord == 'x' && key == 'w')
		g->player.move_x += g->player.step_vx;
	else if (coord == 'y' && key == 'w')
		g->player.move_y += g->player.step_vy;
	else if (coord == 'x' && key == 's')
		g->player.move_x -= g->player.step_vx;
	else if (coord == 'y' && key == 's')
		g->player.move_y -= g->player.step_vy;
	else if (coord == 'x' && key == 'a')
		g->player.move_x -= g->player.step_hx;
	else if (coord == 'y' && key == 'a')
		g->player.move_y -= g->player.step_hy;
	else if (coord == 'x' && key == 'd')
		g->player.move_x += g->player.step_hx;
	else if (coord == 'y' && key == 'd')
		g->player.move_y += g->player.step_hy;
	vector = get_map_vector(g, g->player.move_x, g->player.move_y);
	if (g->map[vector.y / TILE_SIZE][vector.x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

static void	move_forward_back(t_game *g, int key)
{
	if (key == KEY_W)
	{
		if (player_collision_with_wall(g, 'x', 'w'))
			g->player.move_x -= g->player.step_vx;
		if (player_collision_with_wall(g, 'y', 'w'))
			g->player.move_y -= g->player.step_vy;
	}
	else if (key == KEY_S)
	{
		if (player_collision_with_wall(g, 'x', 's'))
			g->player.move_x += g->player.step_vx;
		if (player_collision_with_wall(g, 'y', 's'))
			g->player.move_y += g->player.step_vy;
	}
}

static void	move_left_right(t_game *g, int key)
{
	if (key == KEY_A)
	{
		if (player_collision_with_wall(g, 'x', 'a'))
			g->player.move_x += g->player.step_hx;
		if (player_collision_with_wall(g, 'y', 'a'))
			g->player.move_y += g->player.step_hy;
	}
	else if (key == KEY_D)
	{
		if (player_collision_with_wall(g, 'x', 'd'))
			g->player.move_x -= g->player.step_hx;
		if (player_collision_with_wall(g, 'y', 'd'))
			g->player.move_y -= g->player.step_hy;
	}
}

static void	move_player(t_game *g, int key)
{
	if (key == KEY_W || key == KEY_S)
		move_forward_back(g, key);
	else if (key == KEY_A || key == KEY_D)
		move_left_right(g, key);
	else if (key == KEY_LEFT)
		g->player.angle -= PLAYER_ROTATE;
	else if (key == KEY_RIGHT)
		g->player.angle += PLAYER_ROTATE;
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
		move_player(g, KEY_LEFT);
	if (g->player.key.right)
		move_player(g, KEY_RIGHT);
	g->player.step_vx = cos(g->player.angle) * PLAYER_SPEED;
	g->player.step_vy = sin(g->player.angle) * PLAYER_SPEED;
	g->player.step_hx = cos((g->player.angle + DEGREES_90)) * PLAYER_SPEED;
	g->player.step_hy = sin((g->player.angle + DEGREES_90)) * PLAYER_SPEED;
}
