/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:44:30 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/24 15:01:23 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	player_collision_with_wall(t_game *g, int coord, int key)
{
	t_vector vector;

	if (coord == 'x' && key == 'w')
		g->move_pos_x += g->step_x;
	else if (coord == 'y' && key == 'w')
		g->move_pos_y += g->step_y;
	else if (coord == 'x' && key == 's')
		g->move_pos_x -= g->step_x;
	else if (coord == 'y' && key == 's')
		g->move_pos_y -= g->step_y;
	else if (coord == 'x' && key == 'a')
		g->move_pos_x -= g->step_left_x;
	else if (coord == 'y' && key == 'a')
		g->move_pos_y -= g->step_right_y;
	else if (coord == 'x' && key == 'd')
		g->move_pos_x += g->step_left_x;
	else if (coord == 'y' && key == 'd')
		g->move_pos_y += g->step_right_y;
	vector = get_map_vector(g);
	// y = ((g->player_y * TILE_SIZE)) + g->move_pos_y + PLAYER_RADIUS;
	// x = ((g->player_x * TILE_SIZE)) + g->move_pos_x + PLAYER_RADIUS;
	if (g->map[vector.y/TILE_SIZE][vector.x/TILE_SIZE] == '1')
		return (1);
	return (0);
}

static void	move_forward_back(t_game *g, int key)
{
	if (key == KEY_W)
	{
		if (player_collision_with_wall(g, 'x', 'w'))
			g->move_pos_x -= g->step_x;
		if (player_collision_with_wall(g, 'y', 'w'))
			g->move_pos_y -= g->step_y;
	}
	else if (key == KEY_S)
	{
		if (player_collision_with_wall(g, 'x', 's'))
			g->move_pos_x += g->step_x;
		if (player_collision_with_wall(g, 'y', 's'))
			g->move_pos_y += g->step_y;
	}
}

static void	move_left_right(t_game *g, int key)
{
	if (key == KEY_A)
	{
		if (player_collision_with_wall(g, 'x', 'a'))
			g->move_pos_x += g->step_left_x;
		if (player_collision_with_wall(g, 'y', 'a'))
			g->move_pos_y += g->step_right_y;
	}
	else if (key == KEY_D)
	{
		if (player_collision_with_wall(g, 'x', 'd'))
			g->move_pos_x -= g->step_left_x;
		if (player_collision_with_wall(g, 'y', 'd'))
			g->move_pos_y -= g->step_right_y;
	}
}

static void	move_player(t_game *g, int key)
{
	if (key == KEY_W || key == KEY_S)
		move_forward_back(g, key);
	else if (key == KEY_A || key == KEY_D)
		move_left_right(g, key);
	else if (key == KEY_LEFT)
		g->rotate -= 0.064;
	else if (key == KEY_RIGHT)
		g->rotate += 0.064;
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
}
