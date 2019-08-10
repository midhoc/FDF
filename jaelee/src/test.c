/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 04:38:56 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/10 07:34:55 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int flag = 0;

int		main(int argc, char **argv)
{
	int			fd;
	t_fdf_info	fdf;

	if (!flag)
	{
		ft_bzero(&fdf, sizeof(fdf));
		fdf.T[0] = 0;
		fdf.T[1] = 0;
		fdf.T[2] = 0;
	}
	flag++;
	printf("flag?\n");
	array_init(&fdf.grid, sizeof(t_info));
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, X_SCREEN, Y_SCREEN, "fdf");

	instruction(fdf.mlx_ptr, fdf.win_ptr);

	(void) argv;
	if (argc != 2)
	{
		ft_putendl("usage: ./fdf [file.fdf]");
		//exit(0);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	if(!parse_file(&fdf.grid, fd))
	{
		return(0);
	}
/*
	int		minz = ((t_info*)grid.ptr)[0].z;
	int		maxz = ((t_info*)grid.ptr)[0].z;*/

	int		x_line;

	set_color(fdf.grid, &x_line);

	//int T[3];

	fdf.init_zoom = init_zoom(fdf.grid, fdf.T);
	fdf.to_draw = malloc(fdf.grid.length * (sizeof(t_info)));
	ft_memcpy(fdf.to_draw, (t_info*)fdf.grid.ptr, fdf.grid.length * sizeof(t_info));
	fdf.zoom = fdf.init_zoom;

	fdf.T[2] = x_line;

	/* key-hook */

	printf("%f %f\n", fdf.x_rot, fdf.y_rot);
	draw(fdf.to_draw, fdf.T, (int)fdf.grid.length, &fdf);

	mlx_hook(fdf.win_ptr, KEY_PRESS, 0, key_press, &fdf);
	mlx_loop(fdf.mlx_ptr);
	return (1);
}
