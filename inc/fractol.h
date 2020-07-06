/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:32:30 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/16 18:40:49 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <limits.h>
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <pthread.h>

# define WIN_HEIGHT		1300
# define WIN_WIDTH		2300
# define ESC			53
# define SCROLL_UP		4
# define SCROLL_DOWN	5
#define NUM_OF_THREADS	625

typedef struct			s_point
{
	int					xp;
	int					yp;
	int					color;
}						t_point;

typedef struct			s_point_double
{
	double				x;
	double				y;
}						t_point_double;

typedef struct			s_line
{
	int					dx;
	int					dy;
	double				ds;
	int					sign_x;
	int					sign_y;
	int					error;
	int					derror;
	double				color_r;
	double				color_g;
	double				color_b;
	double				step_r;
	double				step_g;
	double				step_b;
}						t_line;

typedef struct			s_img
{
	void				*img_ptr;
	char				*data;
	int					size_l;
	int					bpp;
	int					endian;
}						t_img;

typedef struct			s_map
{
	t_point				y;
	t_point				v[3];
	double				angle;
	int					mouse_press;
	int					ctrl_press;
	int					x_mouse;
	int					y_mouse;
	int					shift_x;
	int					shift_y;
	int					width;
	int					height;
	void				*mlx;
	void				*win;
	t_img				img;
	pthread_mutex_t		mutex;
	pthread_t			threads[NUM_OF_THREADS];
}						t_map;

double					sqr(double a);
void					img_line_put(t_img *img, t_point p1, t_point p2);
void					img_put(t_map *fdf);
void					img_pixel_put(t_img *img, t_point p1);
void					img_black(t_img *img);
void					event_handler(void *param);
t_point 				fill_point(int x, int y, int color);

#endif
