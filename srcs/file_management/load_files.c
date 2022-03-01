/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:40:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/03/01 02:53:19 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_files(t_game *g, t_data *data)
{
	g->tex.no.img = mlx_xpm_file_to_image(g->ptr, data->no,
			&g->tex.no.width, &g->tex.no.heigth);
	if (!g->tex.no.img)
		return (1);
	g->tex.no.addr = mlx_get_data_addr(g->tex.no.img, &g->tex.so.bpp,
			&g->tex.so.line_len, &g->tex.so.endian);
	g->tex.so.img = mlx_xpm_file_to_image(g->ptr, data->so,
			&g->tex.so.width, &g->tex.so.heigth);
	if (!g->tex.so.img)
		return (1);
	g->tex.so.addr = mlx_get_data_addr(g->tex.so.img, &g->tex.so.bpp,
			&g->tex.so.line_len, &g->tex.so.endian);
	g->tex.ea.img = mlx_xpm_file_to_image(g->ptr, data->ea,
			&g->tex.ea.width, &g->tex.ea.heigth);
	if (!g->tex.ea.img)
		return (1);
	g->tex.ea.addr = mlx_get_data_addr(g->tex.ea.img, &g->tex.ea.bpp,
			&g->tex.ea.line_len, &g->tex.ea.endian);
	g->tex.we.img = mlx_xpm_file_to_image(g->ptr, data->we,
			&g->tex.we.width, &g->tex.we.heigth);
	if (!g->tex.we.img)
		return (1);
	g->tex.we.addr = mlx_get_data_addr(g->tex.we.img, &g->tex.we.bpp,
			&g->tex.we.line_len, &g->tex.we.endian);
	return (0);
}
