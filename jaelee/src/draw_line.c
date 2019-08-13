/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 00:04:40 by hmidoun           #+#    #+#             */
/*   Updated: 2019/08/13 02:36:59 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_x(t_info p1, t_info p2, t_fdf_info *fdf)
{
	t_coord	d;
	t_coord curr;
	int yi;
	int diff;

	curr.y = p1.y;
	curr.x = p1.x;
	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	yi = d.y < 0 ? -1 : 1;
	d.y = abs(d.y);
	diff = 2 * d.y - d.x;
	while (curr.x < p2.x)
	{
		pixel_in_img(fdf->img_string, curr.x, curr.y,
			get_color(curr.y, p1, p2, 0));
		if (diff > 0)
		{
			curr.y += yi;
			diff = diff - 2 * d.x;
		}
		diff = diff + 2 * d.y;
		curr.x++;
	}
}

void	draw_line_y(t_info p1, t_info p2, t_fdf_info *fdf)
{
	t_coord	d;
	t_coord	curr;
	int xi;
	int diff;

	curr.x = p1.x;
	curr.y = p1.y;
	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	xi = d.x < 0 ? -1 : 1;
	d.x = abs(d.x);
	diff = 2 * d.x - d.y;
	while (curr.y < p2.y)
	{
		pixel_in_img(fdf->img_string, curr.x, curr.y,
			get_color(curr.y, p1, p2, 0));
		if (diff > 0)
		{
			curr.x += xi;
			diff = diff - 2 * d.y;
		}
		diff = diff + 2 * d.x;
		curr.y++;
	}
}

void	draw_line(t_info p1, t_info p2, t_fdf_info *fdf)
{
	if (abs(p1.y - p2.y) < abs(p1.x - p2.x))
	{
		if (p1.x > p2.x)
			draw_line_x(p2, p1, fdf);
		else
			draw_line_x(p1, p2, fdf);
	}
	else
	{
		if (p1.y > p2.y)
			draw_line_y(p2, p1, fdf);
		else
			draw_line_y(p1, p2, fdf);
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

static	double percent_atan(int start, int end, int current)
{
	double placement;
	double distance;
	double percent;
	int		trans;
	float	offset;


	placement = current - start;
	distance = end - start;


offset = 1; //0  < >2  change it to chage the color variation  0 to see the bottom of the map .... 2 the top
	trans = start + (distance * 0.5) * offset;


	percent = atan(((placement + trans) * 20 / distance )- 10)/(M_PI_2) + 1;
	//printf("%f\t%f\t%f\n", atan(((placement) * 20 / distance )- 10), percent, placement);
	return ((distance == 0) ? 1.0 : percent);
}

// static	double percent_x3(int start, int end, int current)
// {
// 	double placement;
// 	double distance;
// 	double percent;

// 	placement = current - start;
// 	distance = end - start;
// 	percent = powf(((placement) * 6 / distance )- 3,3)/(27);
// 	//printf("%f\t%f\t%f\n", atan(((placement) * 20 / distance )- 10), percent, placement);
// 	return ((distance == 0) ? 1.0 : percent);
// }

int get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int 	get_color(int current, t_info start, t_info end, int i)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (i == 1)
		percentage = percent(start.x, end.x, current);
	else if(i == 0)
		percentage = percent(start.y, end.y, current);
	else
		percentage = percent_atan(start.z, end.z, current);
	red = get_light((start.color >> 16) & 0xFF,
			(end.color >> 16) & 0xFF, percentage);
	green = get_light((start.color >> 8) & 0xFF,
			(end.color >> 8) & 0xFF, percentage);
	blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
	//return (get_light(start.color, end.color, percentage));
}

static	void	z_max_min(t_fdf_info *fdf)
{
	int	i;

	i = -1;
	fdf->z_min = ((t_info*)fdf->grid.ptr)[0].z;
	fdf->z_max = ((t_info*)fdf->grid.ptr)[0].z;
	while (++i < (int)fdf->grid.length)
	{
		if (((t_info*)fdf->grid.ptr)[i].z > fdf->z_max)
			fdf->z_max = ((t_info*)fdf->grid.ptr)[i].z;
		if (((t_info*)fdf->grid.ptr)[i].z < fdf->z_min)
			fdf->z_min = ((t_info*)fdf->grid.ptr)[i].z;
	}
}

void	set_color(t_array grid, t_fdf_info *fdf)
{
	size_t	i;
	t_info	t1;
	t_info	t2;

	z_max_min(fdf);
	t1.z = fdf->z_min;
	t2.z = fdf->z_max;
	// t1.z = -1000;
	// t2.z = 1000;
	t1.color = 0x00ff00;
	t2.color = 0xff0000;
	i = -1;
	while (++i < grid.length)
	{
		if (((t_info*)grid.ptr)[i].y == 1 && ((t_info*)grid.ptr)[i].x == 0)
			break;
	}
	i = -1;
	while (++i < grid.length)
	{
		if (((t_info*)grid.ptr)[i].color == -1)
			((t_info*)grid.ptr)[i].color =
				get_color(((t_info*)grid.ptr)[i].z, t1, t2, -1);
		((t_info*)grid.ptr)[i].x -= fdf->map_w / 2; // dont know if it really matter
		((t_info*)grid.ptr)[i].y -= fdf->map_h / 2;//same
	}
}
