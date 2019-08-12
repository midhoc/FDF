/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 05:01:52 by hmidoun           #+#    #+#             */
/*   Updated: 2019/08/12 07:15:51 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	instruction(t_fdf_info *fdf)
{
	int	i;

	i = -1;
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 70, 40, 100000, "HOW TO USE : FDF");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 100, 100000, "ZOOM 		: [+] [-]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 150, 100000, "MOVE 		: [<] [>]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 200, 100000, "ROTATION 	:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 250, 100000, "X 	: [A] [D]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 300, 100000, "Y 	: [W] [S]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 350, 100000, "Z 	: [Q] [E]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 400, 100000, "PROJECTION 	:");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 450, 100000, "ISO			: [I]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 120, 500, 100000, "PARALLELE	: [P]");
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 20, 550, 100000, "RESET 		: [SPACE]");
	while (++i < Y_SCREEN)
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, 299, i, 100000);
}
