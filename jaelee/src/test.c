/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 04:38:56 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/11 09:42:55 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <mlx.h>

int		key_press(int keycode, void *param)
{
	t_fdf_info	*fdf;
	fdf = (t_fdf_info*)param;

	if (keycode == MAIN_PAD_W || keycode == MAIN_PAD_A ||
		keycode == MAIN_PAD_S || keycode == MAIN_PAD_D ||
		keycode == MAIN_PAD_Q || keycode == MAIN_PAD_E)
		rotation(keycode, (t_fdf_info*)param);
	else if (keycode == ARROW_UP || keycode == ARROW_DOWN ||
		keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		move(keycode, (t_fdf_info*)param);
	else if (keycode == NUMBER_PAD_PLUS || keycode == NUMBER_PAD_MINUS)
		press_zoom(keycode, (t_fdf_info*)param);
	else if (keycode == MAIN_PAD_I || keycode == MAIN_PAD_P)
		perspective(keycode, fdf);
	else if (keycode == MAIN_PAD_SPACE)
		reset_transformation(fdf);
	else if (keycode == MAIN_PAD_ESC)
		exit(0);
	draw((t_info*)fdf->grid.ptr, (t_fdf_info*)param);
	return (0);
}

static void	initialize_mlx(t_fdf_info *fdf)
{
	int			bpp;
	int			s_l;
	int			endian;

	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, X_SCREEN, Y_SCREEN, "fdf");
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, X_IMG, Y_IMG);
	fdf->img_string = mlx_get_data_addr(fdf->img_ptr, &bpp, &s_l, &endian);
}

static void	initialize_fdf(t_fdf_info *fdf)
{
	ft_bzero(fdf, sizeof(*fdf));
	array_init(&fdf->grid, sizeof(t_info));
	fdf->perspective = ISO;
}

static void	setup_fdf(t_fdf_info *fdf)
{
	instruction(fdf->mlx_ptr, fdf->win_ptr);
	set_color(fdf->grid, fdf);
	fdf->init_zoom = init_zoom(fdf->grid, fdf->T);
	fdf->zoom = fdf->init_zoom;
}

int			main(int argc, char **argv)
{
	int			fd;
	t_fdf_info	fdf;

	initialize_fdf(&fdf);
	if (argc != 2)
	{
		ft_putendl("usage: ./fdf [file.fdf]");
		exit(0);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	if(!parse_file(&fdf.grid, fd, &fdf))
	{
		array_clear(&fdf.grid, NULL);
		return(0);
	}
	close(fd);
	initialize_mlx(&fdf);
	setup_fdf(&fdf);
	draw((t_info*)fdf.grid.ptr, &fdf);
	mlx_hook(fdf.win_ptr, KEY_PRESS, 0, key_press, &fdf);
	mlx_loop(fdf.mlx_ptr);
	array_clear(&fdf.grid, NULL);
	return (1);
}
