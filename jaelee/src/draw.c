/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 04:05:06 by hmidoun           #+#    #+#             */
/*   Updated: 2019/08/11 10:50:25 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	iso(t_info *(*to_draw), int size, int T[3])
// {
// 	int	x;
// 	int y;
// 	int	i;

// 	i = -1;
// 	while (++i < size)
// 	{
// 		x =  (((*to_draw))[i].x - (*to_draw)[i].y) * cos(RAD_30);
// 		y = -(*to_draw)[i].z + ((*to_draw)[i].x + (*to_draw)[i].y) * sin(RAD_30);
// 		(*to_draw)[i].x = x;
// 		(*to_draw)[i].y = y;
// 		(*to_draw)[i] = translation((*to_draw)[i], T[0]/*(X_SCREEN - X_INSTRUCTION) / 2 + X_INSTRUCTION*/ , T[1] /*Y_SCREEN / 2*/, 0);//! translate it to the centre need to be changed
// 	}
// }

void	iso(t_info *to_draw, t_fdf_info *fdf)
{
	int	x;
	int y;
	int	i;

	i = 0;
	while (i < fdf->grid.length)
	{
		x =  (fdf->copy[i].x - fdf->copy[i].y) * cos(RAD_30);
		y = -fdf->copy[i].z + (fdf->copy[i].x + fdf->copy[i].y) * sin(RAD_30);
		fdf->iso[i].x = x;
		fdf->iso[i].y = y;
		i++;
	}
	translation(fdf, fdf->T[0]/*(X_SCREEN - X_INSTRUCTION) / 2 + X_INSTRUCTION*/ , fdf->T[1] /*Y_SCREEN / 2*/, 0);//! translate it to the centre need to be changed
}


void	projection(t_info to_draw, t_fdf_info *fdf)
{
	//t_info	render;
	//render = zoom(to_draw, fdf->zoom, fdf->zoom, fdf->zoom);
	// render = rotation_z(render, fdf->z_rot);
	// render = rotation_x(render, fdf->x_rot);
	// render = rotation_y(render, fdf->y_rot);
	//render = to_draw;
	if (fdf->perspective == ISO)
		iso(fdf->copy, fdf);
	// else if (fdf->perspective == PARALLEL)
	// 	render = translation(render, fdf->T[0], fdf->T[1], 0);
	// render = translation(render, fdf->x_offset, fdf->y_offset, 0);
	//return (render);
}

void	draw(t_info *to_draw, t_fdf_info *fdf)
{
	int		x;
	int		y;
	t_info	render;
	reset_img(fdf->img_string);
	y = -1;
	projection(*to_draw, fdf);
	while (++y < fdf->map_h)
	{
		x = -1;
		while (++x < fdf->map_w)
		{
			// if (x < fdf->map_w - 1)
			// 	draw_line(projection(to_draw[x + y * fdf->map_w], fdf),
			// 		projection(to_draw[x + 1 + y * fdf->map_w], fdf), fdf);
			// if (y < fdf->map_h - 1)
			// 	draw_line(projection(to_draw[x + y * fdf->map_w], fdf),
			// 		projection(to_draw[x + (y+1) * fdf->map_w], fdf), fdf);
			if (x < fdf->map_w - 1)
				draw_line(fdf->iso[x + y * fdf->map_w],
					fdf->iso[x + 1 + y * fdf->map_w], fdf);
			if (y < fdf->map_h - 1)
				draw_line(fdf->iso[x + y * fdf->map_w],
					fdf->iso[x + (y+1) * fdf->map_w], fdf);
		}
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, X_INSTRUCTION, 0);
}
