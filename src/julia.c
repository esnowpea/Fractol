/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:29:54 by esnowpea          #+#    #+#             */
/*   Updated: 2020/07/15 14:29:54 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int		julia2(t_fractol *fractol, t_complex c)
{
	int			i;
	t_complex	z;

	i = 0;
	z = c;
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
		   && i < fractol->max_itr)
	{
		z = init_complex(
				z.re * (pow(z.re, 2.0) - 3 * pow(z.im, 2.0)) +
				fractol->julia.re,
				z.im * (3 * pow(z.re, 2.0) - pow(z.im, 2.0)) +
				fractol->julia.im);
		i++;
	}
	return (i);
}

int		julia3(t_fractol *fractol, t_complex c)
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
				4 * pow(z.re * z.im, 2.0) + fractol->julia.re,
				4 * z.re * z.im * (z.re - z.im) * (z.re + z.im) +
				fractol->julia.im);
		i++;
	}
	return (i);
}
