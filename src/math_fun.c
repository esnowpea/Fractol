/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 15:53:59 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/16 18:30:55 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double		sqr(double a)
{
	return (a * a);
}

t_point_double	sqr_z(t_point_double a)
{
	t_point_double	out;

	out.x = sqr(a.x) - sqr(a.y);
	out.y = 2 * a.x * a.y;
	return (out);
}

t_point_double	sum_z(t_point_double a, t_point_double b)
{
	t_point_double	out;

	out.x = a.x + b.x;
	out.y = a.y + b.y;
	return (out);
}

t_point 		fill_point(int x, int y, int color)
{
	t_point		p;

	p.xp = x;
	p.yp = y;
	p.color = color;
	return (p);
}

t_point_double	fill_z(double x, double y)
{
	t_point_double	out;

	out.x = x;
	out.y = y;
	return (out);
}

double	len_z(t_point_double a)
{
	return (sqrt(sqr(a.x) + sqr(a.y)));
}

t_point 			ind(t_point p)
{
	t_point_double	out;
	t_point_double	out1;
	double 			angle;
	int i;

	out.x = (double)(p.xp - WIN_WIDTH / 2) / 500;
	out.y = (double)(-p.yp + WIN_HEIGHT / 2) / 500;
	out1.x = 500;
	out1.y = 500;
	angle = (double)(171.1) / 180 * M_PI;
	i = 0;
	while (i < 500 && len_z(sum_z(out, out1)) >= 0.00001)
	{
		out1.x = -out.x;
		out1.y = -out.y;
		out = sum_z(sqr_z(out), fill_z(0.7885 * cos(angle), 0.7885 * sin(angle)));
		i++;
	}
	if (len_z(out) < 2)
		p.color = (int)(0xff / sqrt((double)i / 4 + 1)) << 16;
	else
		p.color = (int)(0xff / sqrt((double)i / 4 + 1)) << 8;
	return (p);
}

void 			img_put(t_img *img)
{
	int			i;
	int			j;
	t_point		p;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			p = fill_point(i, j, 0x0);
			img_pixel_put(img, ind(p));
			j++;
		}
		i++;
	}
}