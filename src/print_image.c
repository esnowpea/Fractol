/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 15:54:06 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/16 15:54:06 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		img_black(t_img *img)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			img->data[i * 4 + 4 * WIN_WIDTH * j] = 0;
			img->data[i * 4 + 4 * WIN_WIDTH * j + 1] = 0;
			img->data[i * 4 + 4 * WIN_WIDTH * j + 2] = 0;
			img->data[i * 4 + 4 * WIN_WIDTH * j + 3] = 0;
			j++;
		}
		i++;
	}
}

double		step_color_r(int color1, int color2, double step, int r)
{
	return (((color2 >> r & 0xff) - (color1 >> r & 0xff)) / step);
}

t_line		get_start(t_img *img, t_point p1, t_point p2)
{
	t_line		line;

	line.dx = abs(p1.xp - p2.xp);
	line.dy = abs(p1.yp - p2.yp);
	line.ds = sqrt(sqr(line.dx) + sqr(line.dy));
	line.sign_x = p1.xp < p2.xp ? 1 : -1;
	line.sign_y = p1.yp < p2.yp ? 1 : -1;
	line.error = line.dx - line.dy;
	line.color_r = p1.color >> 16 & 0xff;
	line.color_g = p1.color >> 8 & 0xff;
	line.color_b = p1.color >> 0 & 0xff;
	line.step_r = step_color_r(p1.color, p2.color, line.ds, 16);
	line.step_g = step_color_r(p1.color, p2.color, line.ds, 8);
	line.step_b = step_color_r(p1.color, p2.color, line.ds, 0);
	img_pixel_put(img, p2);
	return (line);
}

void		img_pixel_put(t_img *img, t_point p1)
{
	if (p1.xp >= 0 && p1.xp <= WIN_WIDTH && p1.yp >= 0 && p1.yp <= WIN_HEIGHT)
	{
		img->data[p1.xp * 4 + 4 * WIN_WIDTH * p1.yp] =
				(char)(p1.color >> 0 & 0xff);
		img->data[p1.xp * 4 + 4 * WIN_WIDTH * p1.yp + 1] =
				(char)(p1.color >> 8 & 0xff);
		img->data[p1.xp * 4 + 4 * WIN_WIDTH * p1.yp + 2] =
				(char)(p1.color >> 16 & 0xff);
	}
}

void		img_line_put(t_img *img, t_point p1, t_point p2)
{
	t_line		line;

	line = get_start(img, p1, p2);
	while (p1.xp != p2.xp || p1.yp != p2.yp)
	{
		img_pixel_put(img, p1);
		line.color_r += line.step_r;
		line.color_g += line.step_g;
		line.color_b += line.step_b;
		p1.color = ((int)line.color_r << 16) + ((int)line.color_g << 8) +
				(int)line.color_b;
		line.derror = line.error * 2;
		if (line.derror > -line.dy)
		{
			line.error -= line.dy;
			p1.xp += line.sign_x;
		}
		if (line.derror < line.dx)
		{
			line.error += line.dx;
			p1.yp += line.sign_y;
		}
	}
}