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

t_point_double	pow_z(t_point_double a, double n)
{
	t_point_double	out;
	double r, fi;

	r = sqrt(sqr(a.x) + sqr(a.y));
	fi = atan(a.y/ a.x);
	out.x = pow(r, n) * cos(n * fi);
	out.y = pow(r, n) * sin(n * fi);
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

double	len_z2(t_point_double a)
{
	return (sqr(a.x) + sqr(a.y));
}

t_point 			julia(t_point p, double angle)
{
	t_point_double	out, c;
	double			r;
	int i;

	out.x = (double)(p.xp - WIN_WIDTH / 2) / 300;
	out.y = (double)(-p.yp + WIN_HEIGHT / 2) / 300;
	c = fill_z(0.7885 * cos(angle), 0.7885 * sin(angle));
	r = (1 + sqrt(1 + 4 * sqrt(len_z2(c)))) / 2;
	i = 0;
	while (i < 500 && len_z2(out) < r * r)
	{
		out = sum_z(pow_z(out, 2), c);
		i++;
	}
	if (len_z2(out) < r * r)
	{
		if (i != 500)
			ft_printf("i = %d\n", i);
		p.color = (int) (0xff / sqrt((double) i / 4 + 1)) << 16;
	}
	else
		p.color = (int)(0xff / sqrt((double)i / 4 + 1)) << 0;
	return (p);
}

t_point 			mandelbrot(t_point p, double angle)
{
	t_point_double	out;
	t_point_double	tmp[500];
	int i, j, k, flag;

	out.x = (double)(p.xp - WIN_WIDTH / 2 * 1.3) / 300;
	out.y = (double)(-p.yp + WIN_HEIGHT / 2) / 300;
	i = 0;
	j = 0;
	flag = 1;
	angle = angle + 1 - 1;
	while (i < 500 && len_z2(out) < 4 && flag)
	{
		tmp[j++] = out;
		out = sum_z(pow_z(out, 2),
					fill_z((double) (p.xp - WIN_WIDTH / 2 * 1.3) / 300,
						   (double) (-p.yp + WIN_HEIGHT / 2) / 300));
		k = 0;
		while (k < j && flag)
		{
			if (tmp[k].x == out.x && tmp[k].y == out.y)
				flag = 0;
			k++;
		}
		i++;
	}
	if (len_z2(out) < 4)
		p.color = (int) (0xff / sqrt((double) i / 4 + 1)) << 16;
	else
		p.color = (int)(0xff / sqrt((double)i / 4 + 1)) << 0;
	return (p);
}

void 			*img_put_help(void *args)
{
	t_point		st;
	t_point		en;
	t_point		p;
	int 		i;
	t_map		*arg = (t_map*) args;

	i = 0;
	while (pthread_self() != arg->threads[i])
		i++;
	en.xp = (i % (int)sqrt(NUM_OF_THREADS) + 1) * trunc(WIN_WIDTH /
			(int)sqrt(NUM_OF_THREADS));
	en.yp = (i / (int)sqrt(NUM_OF_THREADS) + 1) * trunc(WIN_HEIGHT /
			(int)sqrt(NUM_OF_THREADS));
	st.xp = en.xp - WIN_WIDTH / (int)sqrt(NUM_OF_THREADS);
	while (st.xp < en.xp)
	{
		st.yp = en.yp - WIN_HEIGHT / (int)sqrt(NUM_OF_THREADS);
		while (st.yp < en.yp)
		{
			p = julia(st, arg->angle);
			pthread_mutex_lock(&(arg->mutex));
			img_pixel_put(&arg->img, p);
			pthread_mutex_unlock(&(arg->mutex));
			st.yp++;
		}
		st.xp++;
	}
	return (0);
}

void 			img_put(t_map *fdf)
{
	int		i;

	i = 0;
	pthread_mutex_init(&(fdf->mutex), NULL);
	while (i < NUM_OF_THREADS)
		pthread_create(&fdf->threads[i++], NULL, img_put_help, fdf);
	while (i > 0)
	{
		pthread_join(fdf->threads[NUM_OF_THREADS - i], NULL);
		ft_printf("end %d thread\n", NUM_OF_THREADS - i);
		i--;
	}
	pthread_mutex_destroy(&(fdf->mutex));
	ft_printf("mutex_destroy\n");
}