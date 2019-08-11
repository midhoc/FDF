/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:59:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/11 01:37:15 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	press_zoom(int key, t_fdf_info *fdf)
{
	if (key == NUMBER_PAD_PLUS)
	{
		if (fdf->zoom < fdf->init_zoom * 10)
			fdf->zoom++;
	}
	else if (key == NUMBER_PAD_MINUS)
	{
		if (fdf->zoom > 1)
			fdf->zoom--;
	}
}

void	move(int key, t_fdf_info *fdf)
{
	if (key == ARROW_DOWN)
		fdf->y_offset += 5;
	else if (key == ARROW_UP)
		fdf->y_offset -= 5;
	else if (key == ARROW_RIGHT)
		fdf->x_offset += 5;
	else if (key == ARROW_LEFT)
		fdf->x_offset -= 5;
}

void	rotation(int key, t_fdf_info *fdf)
{
	if (key == MAIN_PAD_A)
		(fdf)->x_rot += 0.05f;
	else if (key == MAIN_PAD_D)
		(fdf)->x_rot -= 0.05f;
	else if (key == MAIN_PAD_W)
		(fdf)->y_rot += 0.05f;
	else if (key == MAIN_PAD_S)
		(fdf)->y_rot -= 0.05f;
	else if (key == MAIN_PAD_Q)
		(fdf)->z_rot += 0.05f;
	else if (key == MAIN_PAD_E)
		(fdf)->z_rot -= 0.05f;
}

void	reset_transformation(t_fdf_info *fdf)
{
	fdf->x_rot = 0;
	fdf->y_rot = 0;
	fdf->z_rot = 0;
	fdf->x_offset = 0;
	fdf->y_offset = 0;
	fdf->zoom = fdf->init_zoom;
	fdf->perspective = ISO;
}

void	perspective(int key, t_fdf_info *fdf)
{
	if (key == MAIN_PAD_I)
	{
		reset_transformation(fdf);
		fdf->perspective = ISO;
	}
	else if (key == MAIN_PAD_P)
	{
		reset_transformation(fdf);
		fdf->perspective = PARALLEL;
	}
}

int		key_press(int keycode, void *param)
{
	t_fdf_info	*fdf;
	fdf = (t_fdf_info*)param;

	if (keycode == MAIN_PAD_W || keycode == MAIN_PAD_A ||
		keycode == MAIN_PAD_S || keycode == MAIN_PAD_D ||
		keycode == MAIN_PAD_Q || keycode == MAIN_PAD_E)
		rotation(keycode, (t_fdf_info*)param);
	else if (keycode == ARROW_UP || keycode == ARROW_DOWN ||
		keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		move(keycode, (t_fdf_info*)param);
	else if (keycode == NUMBER_PAD_PLUS || keycode == NUMBER_PAD_MINUS)
		press_zoom(keycode, (t_fdf_info*)param);
	else if (keycode == MAIN_PAD_I || keycode == MAIN_PAD_P)
		perspective(keycode, fdf);
	else if (keycode == MAIN_PAD_SPACE)
	 	reset_transformation(fdf);
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	draw((t_info*)fdf->grid.ptr, (t_fdf_info*)param);
	return (0);
}
