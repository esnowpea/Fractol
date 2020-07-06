
#include "fractol.h"

int		key_press(int keycode, void *param)
{
	t_map	*fdf;

	fdf = (t_map *)param;
	if (keycode == ESC)
		exit(0);
	if (keycode == 69)
		fdf->angle += (double)(1) / 180 * M_PI;
	if (keycode == 78)
		fdf->angle -= (double)(1) / 180 * M_PI;
	ft_printf("angle = %f deg\n", fdf->angle * 180 / M_PI);
	img_put(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img_ptr, 0, 0);
//	print_image(fdf);
	return (1);
}

int		close_press(void *param)
{
	(void)param;
	exit(0);
}

void	event_handler(void *param)
{
	t_map *fdf;

	fdf = (t_map*)param;
	mlx_hook(fdf->win, 2, 0, key_press, param);
	mlx_hook(fdf->win, 17, 0, close_press, param);
}