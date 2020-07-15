/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:31:09 by esnowpea          #+#    #+#             */
/*   Updated: 2020/07/15 14:31:09 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				(z.re - z.im) * (z.re + z.im) + c.re,
				2.0 * z.re * z.im + c.im);
		i++;
	}
	return (i);
}

int		mandelbrot2(t_fractol *fractol, t_complex c)
{
	int			i;
	t_complex	z;

	i = 0;
	z = c;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
		   && i < fractol->max_itr)
	{
		z = init_complex(
				z.re * (pow(z.re, 2.0) - 3 * pow(z.im, 2.0)) + c.re,
				z.im * (3 * pow(z.re, 2.0) - pow(z.im, 2.0)) + c.im);
		i++;
	}
	return (i);
}

int		mandelbrot3(t_fractol *fractol, t_complex c)
{
	int			i;
	t_complex	z;

	i = 0;
	z = c;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
		   && i < fractol->max_itr)
	{
		z = init_complex(
				pow((z.re - z.im) * (z.re + z.im), 2.0) -
				4 * pow(z.re * z.im, 2.0) + c.re,
				4 * z.re * z.im * (z.re - z.im) * (z.re + z.im) + c.im);
		i++;
	}
	return (i);
}
