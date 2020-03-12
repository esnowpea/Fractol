/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:32:50 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/12 16:13:39 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int main()
{
	t_map		fdf;
	t_point		p1, p2;

	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
	fdf.img.img_ptr = mlx_new_image(fdf.mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf.img.data = mlx_get_data_addr(fdf.img.img_ptr, &fdf.img.bpp,
									  &fdf.img.size_l, &fdf.img.endian);
	p1.xp = WIN_WIDTH / 3;
	p1.yp = WIN_HEIGHT / 3;
	p1.color = 0xff0000;
	p2.xp = WIN_WIDTH / 3 * 2;
	p2.yp = WIN_HEIGHT / 3 * 2;
	p2.color = 0xff;
	img_line_put(&fdf.img, p1, p2);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img_ptr, 0, 0);
	mlx_loop(fdf.mlx);
}
