/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:40:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/16 23:25:29 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_files(t_game *g, t_data *data)
{
	g->text.no.img = mlx_xpm_file_to_image(g->ptr, data->no,
		&g->text.no.width, &g->text.no.heigth);
	if (!g->text.no.img)
		return (1);
	g->text.no.addr = mlx_get_data_addr(g->text.no.img, &g->text.so.bpp,
		&g->text.so.line_len, &g->text.so.endian);
	g->text.so.img = mlx_xpm_file_to_image(g->ptr, data->so,
		&g->text.so.width, &g->text.so.heigth);
	if (!g->text.so.img)
		return (1);
	g->text.so.addr = mlx_get_data_addr(g->text.so.img, &g->text.so.bpp,
		&g->text.so.line_len, &g->text.so.endian);
	g->text.ea.img = mlx_xpm_file_to_image(g->ptr, data->ea,
		&g->text.ea.width, &g->text.ea.heigth);
	if (!g->text.ea.img)
		return (1);
	g->text.ea.addr = mlx_get_data_addr(g->text.ea.img, &g->text.ea.bpp,
		&g->text.ea.line_len, &g->text.ea.endian);
	g->text.we.img = mlx_xpm_file_to_image(g->ptr, data->we,
		&g->text.we.width, &g->text.we.heigth);
	if (!g->text.we.img)
		return (1);
	g->text.we.addr = mlx_get_data_addr(g->text.we.img, &g->text.we.bpp,
		&g->text.we.line_len, &g->text.we.endian);
	return (0);
}
