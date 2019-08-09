/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 03:35:33 by hmidoun           #+#    #+#             */
/*   Updated: 2019/08/09 06:52:46 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_output_screen(t_info *to_draw, size_t size ,int T[3])
{
	int xmax;
	int	xmin;
	int	ymax;
	int	ymin;
	size_t i;

	i = 0;
	xmin = to_draw[0].x;
	xmax = to_draw[0].x;
	ymin = to_draw[0].y;
	ymax = to_draw[0].y;
	while (++i < size)
	{
		if ((to_draw)[i].x > xmax)
			xmax = (to_draw)[i].x;
		if ((to_draw)[i].x < xmin)
			xmin = (to_draw)[i].x;
		if ((to_draw)[i].y > ymax)
			ymax = (to_draw)[i].y;
		if ((to_draw)[i].y < ymin)
			ymin = (to_draw)[i].y;
	}
	if (abs(xmax - xmin) > (X_SCREEN - X_INSTRUCTION) || abs(ymin - ymax) > Y_SCREEN)
		return (0);
	T[0] = (-abs(xmax - xmin) + (X_SCREEN - X_INSTRUCTION)) / 2;
	T[1] = (-abs(ymin - ymax) + Y_SCREEN) / 2;
	return (1);
}

static t_info	*all_zoom(t_array grid, int z)
{
	t_info	*to_draw;
	size_t	i;

	i = -1;
	to_draw = (t_info *)malloc(sizeof(t_info) * grid.length);
	while (++i < grid.length)
		to_draw[i] = zoom(((t_info*)grid.ptr)[i], z, z, z);

	iso(&to_draw, (int) grid.length);

	return (to_draw);
}

int		init_zoom(t_array grid, int T[3])
{
	int		zoom;
	t_info	*to_draw;

	zoom = 2;
	to_draw = all_zoom(grid, zoom);
	while (check_output_screen(to_draw, grid.length, T))
	{
		zoom++;
		printf("%d\n", zoom);
		to_draw = all_zoom(grid, zoom);
	}
	return(zoom - 1);
}

