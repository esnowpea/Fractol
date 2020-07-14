
#include "fractol.h"
#include "error_message.h"
#include <pthread.h>

void		img_pixel_put(t_img *img, t_point p)
{
	if (p.x >= 0 && p.x <= WIN_WIDTH && p.y >= 0 && p.y <= WIN_HEIGHT)
	{
		img->data[p.x * 4 + 4 * WIN_WIDTH * p.y] =
				(char)(p.color >> 0 & 0xff);
		img->data[p.x * 4 + 4 * WIN_WIDTH * p.y + 1] =
				(char)(p.color >> 8 & 0xff);
		img->data[p.x * 4 + 4 * WIN_WIDTH * p.y + 2] =
				(char)(p.color >> 16 & 0xff);
	}
}

int			get_color(int iteration, t_fractol *fractol)
{
	int		color;
	double	t;

	t = (double)iteration / fractol->max_itr;
	color = ((int8_t)(9 * (1 - t) * pow(t, 3) * 255) << 16) + \
			((int8_t)(15 * pow((1 - t), 2) * pow(t, 2) * 255) << 8) + \
			(int8_t)(8.5 * pow((1 - t), 3) * t * 255);
	return (color);
}

static void	draw_fractal_part(t_fractol *fractol)
{
	t_point		p;
	t_complex	c;

	p.y = fractol->start_line;
	while (p.y < fractol->finish_line)
	{
		c.im = fractol->max.im - p.y * fractol->factor.im;
		p.x = 0;
		while (p.x < WIN_WIDTH)
		{
			c.re = fractol->min.re + p.x * fractol->factor.re;
			p.color = get_color(fractol->formula(fractol, c), fractol);
			img_pixel_put(fractol->img, p);
			p.x++;
		}
		p.y++;
	}
}

void		draw_to_win(t_fractol *fractol)
{
	mlx_put_image_to_window(fractol->mlx, fractol->win,
							fractol->img->img_ptr, 0, 0);
	mlx_string_put(fractol->mlx, fractol->win, 0, 0, 0xFFFFFF,
			"Controls");
	mlx_string_put(fractol->mlx, fractol->win, 0, 30, 0xFFFFFF,
			"Reset          - R");
	mlx_string_put(fractol->mlx, fractol->win, 0, 60, 0xFFFFFF,
			"Move           - Mouse");
	mlx_string_put(fractol->mlx, fractol->win, 0, 90, 0xFFFFFF,
			"Zoom           - Scroll");
	mlx_string_put(fractol->mlx, fractol->win, 0, 120, 0xFFFFFF,
			"Iterations     - +/-");
	if (fractol->is_julia)
		mlx_string_put(fractol->mlx, fractol->win, 0, 150, 0xFFFFFF,
				"Julia Change   - Space");
}

void		draw_fractal(t_fractol *fractol)
{
	pthread_t	threads[THREADS];
	t_fractol	fractols[THREADS];
	int			i;

	fractol->factor = init_complex(
			(fractol->max.re - fractol->min.re) / (WIN_WIDTH - 1),
			(fractol->max.im - fractol->min.im) / (WIN_HEIGHT - 1));
	i = 0;
	while (i < THREADS)
	{
		fractols[i] = *fractol;
		fractols[i].start_line = i * (WIN_HEIGHT / THREADS);
		fractols[i].finish_line = (i + 1) * (WIN_HEIGHT / THREADS);
		if (pthread_create(&threads[i], NULL,
				(void *(*)(void *))draw_fractal_part, (void *)&fractols[i]))
			terminate(ERR_TREADS);
		i++;
	}
	while (i-- > 0)
		if (pthread_join(threads[i], NULL))
			terminate(ERR_TREADS);
	draw_to_win(fractol);
}
