/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:55:33 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/24 15:02:32 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_input(int mouse, t_game *g)
{
	(void)g;
	(void)mouse;
	return (0);
}

int	key_pressed(int key, t_game *g)
{
	if (key == KEY_ESC)
		close_game(g);
	else if (key == KEY_W)
		g->player.key.w = 1;
	else if (key == KEY_A)
		g->player.key.a = 1;
	else if (key == KEY_S)
		g->player.key.s = 1;
	else if (key == KEY_D)
		g->player.key.d = 1;
	else if (key == KEY_LEFT)
		g->player.key.left = 1;
	else if (key == KEY_RIGHT)
		g->player.key.right = 1;
	return (0);
}

int	key_released(int key, t_game *g)
{
	if (key == KEY_W)
		g->player.key.w = 0;
	else if (key == KEY_A)
		g->player.key.a = 0;
	else if (key == KEY_S)
		g->player.key.s = 0;
	else if (key == KEY_D)
		g->player.key.d = 0;
	else if (key == KEY_LEFT)
		g->player.key.left = 0;
	else if (key == KEY_RIGHT)
		g->player.key.right = 0;
	return (0);
}
