
#include "fractol.h"
#include "error_message.h"

t_img		*init_image(void *mlx)
{
	t_img		*image;

	if (!(image = (t_img *)ft_memalloc(sizeof(t_img))))
		terminate(ERR_IMAGE_INIT);
	if (!(image->img_ptr = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT)))
		terminate(ERR_IMAGE_INIT);
	image->data = mlx_get_data_addr(
			image->img_ptr,
			&(image->bpp),
			&(image->size_l),
			&(image->endian));
	return (image);
}

t_complex	init_complex(double re, double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

void		set_defaults(t_fractol *fractol)
{
	fractol->max_itr = 50;
	fractol->min = init_complex(-2.0 * WIN_WIDTH / WIN_HEIGHT, -2.0);
	fractol->max = init_complex(2.0 * WIN_WIDTH / WIN_HEIGHT, 2.0);
	fractol->mouse_press = 0;
	fractol->ctrl_press = 0;
	fractol->julia = init_complex(-0.77, 0.122);
}

static int			(*get_formula(char *name)) (t_fractol *fractol, t_complex c)
{
	size_t				i;
	int					(*formula)(t_fractol *, t_complex);
	static t_formula	formulas[] = {
			{ "Mandelbrot", &mandelbrot },
			{ "Julia", &julia }
	};

	i = 0;
	formula = NULL;
	while (i < (sizeof(formulas) / sizeof(t_formula)))
	{
		if (ft_strequ(name, formulas[i].name))
			formula = formulas[i].formula;
		i++;
	}
	return (formula);
}

t_fractol	*init_fractol(char *name, void *mlx)
{
	t_fractol	*fractol;

	if (!(fractol = (t_fractol *)ft_memalloc(sizeof(t_fractol))))
		terminate(ERR_FRACTOL_INIT);
	fractol->mlx = mlx;
	if (!(fractol->win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, name)))
		terminate(ERR_WINDOW_INIT);
	fractol->img = init_image(mlx);
	set_defaults(fractol);
	if (!(fractol->formula = get_formula(name)))
		terminate(ERR_FRACTAL_NAME);
	event_handler(fractol);
	return (fractol);
}