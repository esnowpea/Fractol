/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:32:50 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/16 16:40:02 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*free_fdf(t_map *a)
{
	if (a)
	{
		write(1, "Error.\n", 15);
		free(a);
	}
	return (0);
}

void		initialization(t_map *fdf)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	fdf->img.img_ptr = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.data = mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bpp,
									  &fdf->img.size_l, &fdf->img.endian);
	fdf->angle = (double)(171.1) / 180 * M_PI;
}

int main()
{
	t_map		fdf;

	initialization(&fdf);
	img_put(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img_ptr, 0, 0);
	event_handler((void*)&fdf);
	mlx_loop(fdf.mlx);
}
