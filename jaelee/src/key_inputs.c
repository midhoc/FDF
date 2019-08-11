/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:59:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/11 10:37:01 by jaelee           ###   ########.fr       */
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
	{
		(fdf)->x_rot += 0.05f;
		rotation_x(fdf, 0.05f);
	}
	else if (key == MAIN_PAD_D)
	{
		(fdf)->x_rot -= 0.05f;
		rotation_x(fdf, -0.05f);
	}
	else if (key == MAIN_PAD_W)
	{
		(fdf)->y_rot += 0.05f;
		rotation_y(fdf, 0.05f);
	}
	else if (key == MAIN_PAD_S)
	{
		(fdf)->y_rot -= 0.05f;
		rotation_y(fdf, -0.05f);
	}
	else if (key == MAIN_PAD_Q)
	{
		(fdf)->z_rot += 0.05f;
		rotation_z(fdf, 0.05f);
	}
	else if (key == MAIN_PAD_E)
	{
		(fdf)->z_rot -= 0.05f;
		rotation_z(fdf, -0.05f);
	}
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
