/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmidoun <hmidoun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 04:38:56 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/11 07:35:33 by hmidoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>

int		main(int argc, char **argv)
{
	int			fd;
	t_fdf_info	fdf;
	int			bpp;
	int			s_l;
	int			endian;

	ft_bzero(&fdf, sizeof(fdf));
	fdf.perspective = ISO;

	array_init(&fdf.grid, sizeof(t_info));
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, X_SCREEN, Y_SCREEN, "fdf");
	fdf.img_ptr = mlx_new_image(fdf.mlx_ptr, X_IMG, Y_IMG);
	fdf.img_string = mlx_get_data_addr(fdf.img_ptr, &(bpp), &(s_l), &(endian));

/*
	void	*mlx_ptr = NULL;
	void	*win_ptr;

	//void	*img_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, X_SCREEN, Y_SCREEN, "fdf");*/

	//instruction(fdf.mlx_ptr, fdf.win_ptr);

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

	set_color(fdf.grid, &fdf);

	fdf.init_zoom = init_zoom(fdf.grid, fdf.T);
	fdf.zoom = fdf.init_zoom;
	fdf.copy = (t_inf*)malloc(sizeof(t_info) * fdf.grid.length);
	ft_memcpy(fdf.copy, (t_info*)fdf.grid.ptr, sizeof(t_info) * fdf.grid.length));
	draw((t_info*)fdf.grid.ptr, &fdf);

	mlx_hook(fdf.win_ptr, KEY_PRESS, 0, key_press, &fdf);
	mlx_loop(fdf.mlx_ptr);

	array_clear(&fdf.grid, NULL);
	return (1);
}

//2,0x820505
