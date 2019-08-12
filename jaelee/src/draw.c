/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 04:05:06 by hmidoun           #+#    #+#             */
/*   Updated: 2019/08/12 03:22:08 by hmidoun          ###   ########.fr       */
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

	x =  (to_draw->x - to_draw->y) * cos(RAD_30);
	y = -to_draw->z + (to_draw->x + to_draw->y) * sin(RAD_30);
	to_draw->x = x;
	to_draw->y = y;
	*to_draw = translation(*to_draw, fdf->T[0]/*(X_SCREEN - X_INSTRUCTION) / 2 + X_INSTRUCTION*/ , fdf->T[1] /*Y_SCREEN / 2*/, 0);//! translate it to the centre need to be changed
}


void	projection(t_fdf_info *fdf)
{
	//t_info	render;
	int		i;

	i = -1;
	while (++i < fdf->grid.length)
	{
		fdf->iso[i] = zoom(((t_info*)fdf->grid.ptr)[i], fdf->zoom, fdf->zoom, fdf->zoom);
		fdf->iso[i] = rotation_z(fdf->iso[i], fdf->z_rot);
		fdf->iso[i] = rotation_x(fdf->iso[i], fdf->x_rot);
		fdf->iso[i] = rotation_y(fdf->iso[i], fdf->y_rot);

		if (fdf->perspective == ISO)
			iso(&fdf->iso[i], fdf);
		else if (fdf->perspective == PARALLEL)
			fdf->iso[i] = translation(fdf->iso[i], fdf->T[0], fdf->T[1], 0);
		fdf->iso[i] = translation(fdf->iso[i], fdf->x_offset, fdf->y_offset, 0);
		//fdf->iso[i].z = (t_info*)fdf->grid.ptr)[i].z;
	}
	//return (render);
}

void	draw(t_info *to_draw, t_fdf_info *fdf)
{
	int		x;
	int		y;
	t_info	render;
	reset_img(fdf->img_string);
	projection(fdf);
	y = -1;
	while (++y < fdf->map_h)
	{
		x = -1;
		while (++x < fdf->map_w)
		{
			if (x < fdf->map_w - 1)
				draw_line(fdf->iso[x + y * fdf->map_w],
					fdf->iso[x + 1 + y * fdf->map_w],
						fdf);
			if (y < fdf->map_h - 1)
				draw_line(fdf->iso[x + y * fdf->map_w],
					fdf->iso[x + (y+1) * fdf->map_w],
						fdf);
		}
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, X_INSTRUCTION, 0);
}
