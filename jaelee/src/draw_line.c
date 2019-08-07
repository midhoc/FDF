/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 00:04:40 by hmidoun           #+#    #+#             */
/*   Updated: 2019/08/07 07:18:19 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_x(t_info p1, t_info p2, void *mlx_ptr, void *win_ptr)
{
	int dx;
	int dy;
	int yi;
	int d;
	int	start;

	start = p1.x;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = 2 * dy - dx;
	while (p1.x < p2.x)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, (int)p1.x, (int)p1.y, get_color(p1.x, p1, p2));
		if (d > 0)
		{
			p1.y += yi;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
		p1.x++;
	}
}

void	draw_line_y(t_info p1, t_info p2, void *mlx_ptr, void *win_ptr)
{
	int dx;
	int dy;
	int xi;
	int d;
	int start;

	start = p1.y;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx *= -1;
	}
	d = 2 * dx - dy;
	while (p1.y < p2.y)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, p1.x, p1.y, get_color(p1.y, p1, p2));
		if (d > 0)
		{
			p1.x += xi;
			d = d - 2 * dy;
		}
		d = d + 2 * dx;
		p1.y++;
	}
}

void	draw_line(t_info p1, t_info p2, void *mlx_ptr, void *win_ptr)
{
	if (abs(p1.y - p2.y) < abs(p1.x - p2.x))
	{
		if (p1.x > p2.x)
			draw_line_x(p2, p1, mlx_ptr, win_ptr);
		else
			draw_line_x(p1, p2, mlx_ptr, win_ptr);
	}
	else
	{
		if (p1.y > p2.y)
			draw_line_y(p2, p1, mlx_ptr, win_ptr);
		else
			draw_line_y(p1, p2, mlx_ptr, win_ptr);
	}
}

double percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int get_color(int current, t_info start, t_info end)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	percentage = percent(start.z, end.z, current);
	red = get_light((start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
	blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
