/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 04:05:06 by hmidoun           #+#    #+#             */
/*   Updated: 2019/08/12 08:16:29 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(t_info *draw, t_fdf_info *fdf)
{
	int	x;
	int y;

	x =  (draw->x - draw->y) * cos(RAD_30);
	y = -draw->z + (draw->x + draw->y) * sin(RAD_30);
	draw->x = x;
	draw->y = y;
	*draw = translation(*draw, fdf->center[0]/*(X_SCREEN - X_INSTRUCTION) / 2 + X_INSTRUCTION*/ , fdf->center[1] /*Y_SCREEN / 2*/, 0);//! translate it to the centre need to be changed
}

void	projection(t_fdf_info *fdf)
{
	int		i;
	t_info *copy;

	copy = fdf->copy;
	i = -1;
	while (++i < (int)fdf->grid.length)
	{
		copy[i] = zoom(((t_info*)fdf->grid.ptr)[i],
			fdf->zoom, fdf->zoom, fdf->zoom);
		copy[i] = rotation_z(copy[i], fdf->z_rot);
		copy[i] = rotation_x(copy[i], fdf->x_rot);
		copy[i] = rotation_y(copy[i], fdf->y_rot);
		if (fdf->perspective == ISO)
			isometric(&copy[i], fdf);
		else if (fdf->perspective == PARALLEL)
			copy[i] = translation(copy[i],
				fdf->center[0], fdf->center[1], 0);
		copy[i] = translation(copy[i], fdf->x_offset, fdf->y_offset, 0);
	}
}

void	draw(t_fdf_info *fdf)
{
	int		x;
	int		y;
	t_info	*copy;

	copy = fdf->copy;
	reset_img(fdf->img_string);
	projection(fdf);
	y = -1;
	while (++y < fdf->map_h)
	{
		x = -1;
		while (++x < fdf->map_w)
		{
			if (x < fdf->map_w - 1)
				draw_line(copy[x + y * fdf->map_w],
					copy[(x + 1) + y * fdf->map_w], fdf);
			if (y < fdf->map_h - 1)
				draw_line(copy[x + y * fdf->map_w],
					copy[x + (y + 1) * fdf->map_w], fdf);
		}
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
		fdf->img_ptr, X_INSTR, 0);
}
