/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 00:04:40 by hmidoun           #+#    #+#             */
/*   Updated: 2019/08/05 02:50:57 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_x1_dx(t_p_list p1, t_p_list p2, void *mlx_ptr, void *win_ptr)
{
	int dp;
	int deltaE;
	int deltaNE;

	deltaE = 2 * fmin(p1.y, p2.y);
	deltaNE = 2 * (fmin(p1.y, p2.y) - fmin(p1.x, p2.x));
	dp = 2 * fmin(p1.y, p2.y) - fmin(p1.x, p2.x);
	mlx_pixel_put(mlx_ptr, win_ptr, p1.x, p1.y, 100000);
	while (p1.x < p2.x)
	{
		if (dp <= 0)
		{
			dp = dp + deltaE;
			p1.x++;
		}
		else
		{
			dp = dp + deltaNE;
			p1.x++;
			p1.y++;
		}
		mlx_pixel_put(mlx_ptr, win_ptr, p1.x, p1.y, 100000);
	}
}
void	draw_line_x1_dy(t_p_list p1, t_p_list p2, void *mlx_ptr, void *win_ptr)
{
	int dp;
	int deltaE;
	int deltaNE;

	deltaE = 2 * fmin(p1.x, p2.x);
	deltaNE = -2 * (fmin(p1.y, p2.y) - fmin(p1.x, p2.x));
	dp = 2 * fmin(p1.x, p2.x) - fmin(p1.y, p2.y);
	mlx_pixel_put(mlx_ptr, win_ptr, p1.x, p1.y, 100000);
	while (p1.y < p2.y)
	{
		if (dp <= 0)
		{
			dp = dp + deltaE;
			p1.y++;
		}
		else
		{
			dp = dp + deltaNE;
			p1.x++;
			p1.y++;
		}
		mlx_pixel_put(mlx_ptr, win_ptr, p1.x, p1.y, 100000);
	}
}

void	draw_line_x2_dy(t_p_list p1, t_p_list p2, void *mlx_ptr, void *win_ptr)
{
	int dp;
	int deltaE;
	int deltaNE;

	deltaE = 2 * fmin(p1.x, p2.x);
	deltaNE = -2 * (fmin(p1.y, p2.y) - fmin(p1.x, p2.x));
	dp = 2 * fmin(p1.x, p2.x) - fmin(p1.y, p2.y);
	mlx_pixel_put(mlx_ptr, win_ptr, p1.x, p1.y, 100000);
	while (p1.y < p2.y)
	{
		if (dp <= 0)
		{
			dp = dp + deltaE;
			p1.y++;
		}
		else
		{
			dp = dp + deltaNE;
			p1.x--;
			p1.y++;
		}
		mlx_pixel_put(mlx_ptr, win_ptr, p1.x, p1.y, 100000);
	}
}

void	draw_line_x2_dx(t_p_list p1, t_p_list p2, void *mlx_ptr, void *win_ptr)
{
	int dp;
	int deltaE;
	int deltaNE;

	deltaE = 2 * fmin(p1.y, p2.y);
	deltaNE = 2 * (fmin(p1.y, p2.y) - fmin(p1.x, p2.x));
	dp = 2 * fmin(p1.y, p2.y) - fmin(p1.x, p2.x);
	mlx_pixel_put(mlx_ptr, win_ptr, p1.x, p1.y, 100000);
	while (p1.x < p2.x)
	{
		if (dp <= 0)
		{
			dp = dp + deltaE;
			p1.x--;
		}
		else
		{
			dp = dp + deltaNE;
			p1.x--;
			p1.y++;
		}
		mlx_pixel_put(mlx_ptr, win_ptr, p1.x, p1.y, 100000);
	}
}

void	draw_line(t_p_list p1, t_p_list p2, void *mlx_ptr, void *win_ptr)
{
	if (p2.x > p1.x)
	{
		if (fmin(p1.y, p2.y) <= fmin(p1.x, p2.x))
			draw_line_x1_dx(p1, p2, mlx_ptr, win_ptr);
		else
			draw_line_x1_dy(p1, p2, mlx_ptr, win_ptr);
	}
	else
	{
		if (fmin(p1.y, p2.y) <= fmin(p1.x, p2.x))
			draw_line_x2_dx(p1, p2, mlx_ptr, win_ptr);
		else
			draw_line_x2_dy(p1, p2, mlx_ptr, win_ptr);
	}
}
