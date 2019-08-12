/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 05:01:52 by hmidoun           #+#    #+#             */
/*   Updated: 2019/08/12 04:07:05 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	instruction(void *mlx_ptr, void *win_ptr)
{
	t_info	p1;
	t_info	p2;

	p1.x = X_INSTR;
	p1.y = 0;
	p1.color = 100000;
	p2.color = 100000;
	p2.x = X_INSTR;
	p2.y = Y_SCREEN;
	mlx_string_put(mlx_ptr, win_ptr, 70, 40, 100000, "HOW TO USE : FDF");
	mlx_string_put(mlx_ptr, win_ptr, 20, 100, 100000, "ZOOM 		: [+] [-]");
	mlx_string_put(mlx_ptr, win_ptr, 20, 150, 100000, "MOVE 		: [<] [>]");
	mlx_string_put(mlx_ptr, win_ptr, 20, 200, 100000, "ROTATION 	:");
	mlx_string_put(mlx_ptr, win_ptr, 120, 250, 100000, "X 	: [A] [D]");
	mlx_string_put(mlx_ptr, win_ptr, 120, 300, 100000, "Y 	: [W] [S]");
	mlx_string_put(mlx_ptr, win_ptr, 120, 350, 100000, "Z 	: [Q] [E]");
	mlx_string_put(mlx_ptr, win_ptr, 20, 400, 100000, "PROJECTION 	:");
	mlx_string_put(mlx_ptr, win_ptr, 120, 450, 100000, "ISO			: [I]");
	mlx_string_put(mlx_ptr, win_ptr, 120, 500, 100000, "PARALLELE	: [P]");
	mlx_string_put(mlx_ptr, win_ptr, 20, 550, 100000, "RESET 		: [SPACE]");
	//draw_line(p1, p2, mlx_ptr, win_ptr);
}
