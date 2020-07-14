
#include "fractol.h"
#include "key_define.h"

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
	else if (key == MAIN_PAD_MINUS || key == NUM_PAD_MINUS ||
	key == MAIN_PAD_PLUS || key == NUM_PAD_PLUS)
		change_max_iteration(key, fractol);
	else if (key == MAIN_PAD_SPACE)
		fractol->space_press = !fractol->space_press;
	return (0);
}

int			zoom(int button, int x, int y, t_fractol *fractol)
{
	t_complex	mouse;
	double		zoom;

	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		mouse = init_complex(
				(double)x / (WIN_WIDTH / (fractol->max.re - fractol->min.re))
				+ fractol->min.re,
				(double)y / (WIN_HEIGHT / (fractol->max.im - fractol->min.im))
				* -1 + fractol->max.im);
		zoom = button == MOUSE_SCROLL_UP ? 0.8 : 1.2;
		fractol->min.re = mouse.re + (fractol->min.re - mouse.re) / zoom;
		fractol->min.im = mouse.im + (fractol->min.im - mouse.im) / zoom;
		fractol->max.re = mouse.re + (fractol->max.re - mouse.re) / zoom;
		fractol->max.im = mouse.im + (fractol->max.im - mouse.im) / zoom;
		draw_fractal(fractol);
	}
	return (0);
}

int			move(int x, int y, t_fractol *fractol)
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
	return (1);
}

int			mouse_press(int button, int x, int y, t_fractol *fractol)
{
	if (button == MOUSE_LEFT)
	{
		fractol->mouse_press = 1;
		fractol->x_mouse = x;
		fractol->y_mouse = y;
	}
	zoom(button, x, y, fractol);
	return (1);
}

int			mouse_move(int x, int y, t_fractol *fractol)
{
	if (fractol->mouse_press)
		move(x, y, fractol);
	if (fractol->space_press && !fractol->mouse_press && fractol->is_julia)
	{
		fractol->julia.re = 0.7885 * cos((double)x / WIN_WIDTH * 2 * M_PI);
		fractol->julia.im = 0.7885 * sin((double)x / WIN_WIDTH * 2 * M_PI);
		draw_fractal(fractol);
	}
	return (1);
}

int			mouse_release(int button, int x, int y, t_fractol *fractol)
{
	if (button == MOUSE_LEFT)
		fractol->mouse_press = 0;
	fractol->x_mouse = x;
	fractol->y_mouse = y;
	return (1);
}

int			close_press(void *param)
{
	(void)param;
	exit(0);
}

void		event_handler(t_fractol *fractol)
{
	mlx_hook(fractol->win, 2, 0, key_press, fractol);
	mlx_hook(fractol->win, 17, 0, close_press, fractol);
	mlx_hook(fractol->win, 4, 0, mouse_press, fractol);
	mlx_hook(fractol->win, 6, 0, mouse_move, fractol);
	mlx_hook(fractol->win, 5, 0, mouse_release, fractol);
}
