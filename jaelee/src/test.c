/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 04:38:56 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/11 07:43:24 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	int			fd;
	t_fdf_info	fdf;

	ft_bzero(&fdf, sizeof(fdf));
	fdf.perspective = ISO;

	array_init(&fdf.grid, sizeof(t_info));
	(void) argv;
	if (argc != 2)
	{
		ft_putendl("usage: ./fdf [file.fdf]");
		//exit(0);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	if(!parse_file(&fdf.grid, fd, &fdf))
	{
		array_clear(&fdf.grid, NULL);
		return(0);
	}
/*
	int		minz = ((t_info*)grid.ptr)[0].z;
	int		maxz = ((t_info*)grid.ptr)[0].z;*/

	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, X_SCREEN, Y_SCREEN, "fdf");

	instruction(fdf.mlx_ptr, fdf.win_ptr);
	set_color(fdf.grid, &fdf);

	fdf.init_zoom = init_zoom(fdf.grid, fdf.T);
	fdf.zoom = fdf.init_zoom;

	draw((t_info*)fdf.grid.ptr, &fdf);

	mlx_hook(fdf.win_ptr, KEY_PRESS, 0, key_press, &fdf);
	mlx_loop(fdf.mlx_ptr);

	array_clear(&fdf.grid, NULL);
	return (1);
}
