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

t_point 			ind(t_point p, double angle)
{
	t_point_double	out;
	t_point_double	out1;
	int i;

	out.x = (double)(p.xp - WIN_WIDTH / 2) / 500;
	out.y = (double)(-p.yp + WIN_HEIGHT / 2) / 500;
	out1.x = out.x + 1;
	out1.y = out.y + 1;
	i = 0;
//	while (i < 500 && len_z(sum_z(out, out1)) >= 0.00001)
	while (i < 500 && len_z(out) < 16)
	{
		out1.x = -out.x;
		out1.y = -out.y;
		out = sum_z(sqr_z(out), fill_z(0.7885 * cos(angle), \
		0.7885 * sin(angle)));
//		out = sum_z(sqr_z(out), fill_z((double)(p.xp - WIN_WIDTH / 2) / 500,
//									   (double)(-p.yp + WIN_HEIGHT / 2) / 500));
		i++;
	}
	if (len_z(out) < 2)
		p.color = (int)(0xff / sqrt((double)i / 4 + 1)) << 16;
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
	pthread_mutex_lock(&(arg->mutex));
	ft_printf("i = %d, x = %d, y = %d\n", i, en.xp, en.yp);
	pthread_mutex_unlock(&(arg->mutex));
	st.xp = en.xp - WIN_WIDTH / (int)sqrt(NUM_OF_THREADS);
	while (st.xp < en.xp)
	{
		st.yp = en.yp - WIN_HEIGHT / (int)sqrt(NUM_OF_THREADS);
		while (st.yp < en.yp)
		{
			p = ind(st, arg->angle);
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