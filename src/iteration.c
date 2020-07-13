
#include "fractol.h"

int		mandelbrot(t_fractol *fractol, t_complex c)
{
	int			i;
	t_complex	z;

	i = 0;
	z = c;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
		   && i < fractol->max_itr)
	{
		z = init_complex(
				pow(z.re, 2.0) - pow(z.im, 2.0) + c.re,
				2.0 * z.re * z.im + c.im);
		i++;
	}
	return (i);
}

int		julia(t_fractol *fractol, t_complex c)
{
	int			i;
	t_complex	z;

	i = 0;
	z = c;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
		   && i < fractol->max_itr)
	{
		z = init_complex(
				pow(z.re, 2.0) - pow(z.im, 2.0) + fractol->julia.re,
				2.0 * z.re * z.im + fractol->julia.im);
		i++;
	}
	return (i);
}