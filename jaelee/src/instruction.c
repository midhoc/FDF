/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 05:01:52 by hmidoun           #+#    #+#             */
/*   Updated: 2019/08/13 16:37:27 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	instruction2(t_fdf_info *fdf, int y)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 50 * y++, 100000,
		"PROJECTION 	:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 50 * y++, 100000,
		"ISO			: [I]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 50 * y++, 100000,
		"PARALLELE	: [P]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 50 * y++, 100000,
		"COLOR 		: [9] [6]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 50 * y++, 100000,
		"TOP		: [9]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 50 * y++, 100000,
		"BOTTOM	: [6]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 50 * y++, 100000,
		"RESET 		: [SPACE]");
}

void		instruction(t_fdf_info *fdf)
{
	int	i;
	int	y;

	y = 2;
	i = -1;
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 70, 40, 100000,
		"HOW TO USE : FDF");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 50 * y++, 100000,
		"ZOOM 		: [+] [-]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 50 * y++, 100000,
		"MOVE 		: [<] [>]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 50 * y++, 100000,
		"ROTATION 	:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 50 * y++, 100000,
		"X 	: [A] [D]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 50 * y++, 100000,
		"Y 	: [W] [S]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 50 * y++, 100000,
		"Z 	: [Q] [E]");
	instruction2(fdf, y);
	while (++i < Y_SCREEN)
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, 299, i, 100000);
}
