
#include "fractol.h"
#include "key_define.h"

static void	move(int key, t_fractol *fractol)
{
	t_complex	delta;

	delta = init_complex(fabs(fractol->max.re - fractol->min.re),
						 fabs(fractol->max.im - fractol->min.im));
	if (key == ARROW_LEFT)
	{
		fractol->min.re -= delta.re * 0.05;
		fractol->max.re -= delta.re * 0.05;
	}
	else if (key == ARROW_RIGHT)
	{
		fractol->min.re += delta.re * 0.05;
		fractol->max.re += delta.re * 0.05;
	}
	else if (key == ARROW_UP)
	{
		fractol->min.im += delta.im * 0.05;
		fractol->max.im += delta.im * 0.05;
	}
	else if (key == ARROW_DOWN)
	{
		fractol->min.im -= delta.im * 0.05;
		fractol->max.im -= delta.im * 0.05;
	}
	draw_fractal(fractol);
}

static void	change_max_iteration(int key, t_fractol *fractol)
{
	if (key == MAIN_PAD_PLUS || key == NUM_PAD_PLUS)
	{
		if (fractol->max_itr < 50)
			fractol->max_itr += 1;
		else if (fractol->max_itr < 1000000000)
			fractol->max_itr = (int)(fractol->max_itr * 1.05);
	}
	if (key == MAIN_PAD_MINUS || key == NUM_PAD_MINUS)
	{
		if (fractol->max_itr > 50)
			fractol->max_itr = (int)(fractol->max_itr * 0.95);
		else if (fractol->max_itr > 1)
			fractol->max_itr -= 1;
	}
	draw_fractal(fractol);
}

int			key_press(int key, t_fractol *fractol)
{
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == MAIN_PAD_R)
	{
		set_defaults(fractol);
		draw_fractal(fractol);
	}
	else if (key == MAIN_PAD_MINUS || key == NUM_PAD_MINUS
			 || key == MAIN_PAD_PLUS || key == NUM_PAD_PLUS)
		change_max_iteration(key, fractol);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT
			 || key == ARROW_UP || key == ARROW_DOWN)
		move(key, fractol);
	else if (key == MAIN_PAD_CTRL)
		fractol->ctrl_press = !fractol->ctrl_press;
	return (0);
}

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int				zoom(int button, int x, int y, t_fractol *fractol)
{
	t_complex	mouse;
	double		interpolation;
	double		zoom;

	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		mouse = init_complex(
				(double)x / (WIN_WIDTH / (fractol->max.re - fractol->min.re))
				+ fractol->min.re,
				(double)y / (WIN_HEIGHT / (fractol->max.im - fractol->min.im))
				* -1 + fractol->max.im);
		if (button == MOUSE_SCROLL_UP)
			zoom = 0.80;
		else
			zoom = 1.20;
		interpolation = 1.0 / zoom;
		fractol->min.re = interpolate(mouse.re, fractol->min.re, interpolation);
		fractol->min.im = interpolate(mouse.im, fractol->min.im, interpolation);
		fractol->max.re = interpolate(mouse.re, fractol->max.re, interpolation);
		fractol->max.im = interpolate(mouse.im, fractol->max.im, interpolation);
		draw_fractal(fractol);
	}
	return (0);
}

int		mouse_press(int button, int x, int y, t_fractol *fractol)
{
	if (button == MOUSE_LEFT)
	{
		fractol->mouse_press = 1;
		fractol->x_mouse = x;
		fractol->y_mouse = y;
	}
	zoom(button, x,  y, fractol);
	return (1);
}

int		mouse_move(int x, int y, t_fractol *fractol)
{
	if (fractol->mouse_press && !fractol->ctrl_press)
	{
		fractol->max.re += (fractol->max.re - fractol->min.re) / WIN_WIDTH *
				(fractol->x_mouse - x);
		fractol->min.re += (fractol->max.re - fractol->min.re) / WIN_WIDTH *
						   (fractol->x_mouse - x);
		fractol->max.im -= (fractol->max.im - fractol->min.im) / WIN_HEIGHT *
						   (fractol->y_mouse - y);
		fractol->min.im -= (fractol->max.im - fractol->min.im) / WIN_HEIGHT *
						   (fractol->y_mouse - y);
		fractol->x_mouse = x;
		fractol->y_mouse = y;
		draw_fractal(fractol);
	}
	else if (fractol->ctrl_press)
	{
		fractol->julia.re = fractol->min.re + \
		(fractol->max.re - fractol->min.re) / WIN_WIDTH * x;
		fractol->julia.im = fractol->min.im + \
		(fractol->max.im - fractol->min.im) / WIN_HEIGHT * y;
		draw_fractal(fractol);
	}
	return (1);
}

int		mouse_release(int button, int x, int y, t_fractol *fractol)
{
	if (button == MOUSE_LEFT)
		fractol->mouse_press = 0;
	else if (button == MAIN_PAD_CTRL)
		fractol->ctrl_press = 0;
	fractol->x_mouse = x;
	fractol->y_mouse = y;
	return (1);
}

int		close_press(void *param)
{
	(void)param;
	exit(0);
}

void	event_handler(t_fractol *fractol)
{
	mlx_hook(fractol->win, 2, 0, key_press, fractol);
	mlx_hook(fractol->win, 17, 0, close_press, fractol);
	mlx_hook(fractol->win, 4, 0, mouse_press, fractol);
	mlx_hook(fractol->win, 6, 0, mouse_move, fractol);
	mlx_hook(fractol->win, 5, 0, mouse_release, fractol);
}