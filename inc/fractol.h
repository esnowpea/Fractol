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
# include <math.h>
# include <mlx.h>
# include <stdint.h>

# define WIN_HEIGHT		1200
# define WIN_WIDTH		2300
# define THREADS		100

typedef struct			s_point
{
	int					x;
	int					y;
	int					color;
}						t_point;

typedef struct			s_complex
{
	double			re;
	double			im;
}						t_complex;

typedef struct			s_img
{
	void				*img_ptr;
	char				*data;
	int					size_l;
	int					bpp;
	int					endian;
}						t_img;

typedef struct			s_fractol
{
	void				*mlx;
	void				*win;
	t_img				*img;
	int					mouse_press;
	int					space_press;
	int					is_julia;
	int					x_mouse;
	int					y_mouse;
	int					max_itr;
	t_complex			min;
	t_complex			max;
	t_complex			factor;
	t_complex			julia;
	int					start_line;
	int					finish_line;
	int					(*formula)(struct s_fractol *fractol, t_complex c);
}						t_fractol;

typedef struct			s_formula
{
	char				*name;
	int					(*formula)(t_fractol *fractol, t_complex c);
}						t_formula;

void					terminate(char *s);
t_fractol				*init_fractol(char *name);
t_complex				init_complex(double re, double im);
void					draw_fractal(t_fractol *fractol);
void					event_handler(t_fractol *fractol);
int						mandelbrot(t_fractol *fractol, t_complex c);
int						mandelbrot2(t_fractol *fractol, t_complex c);
int						mandelbrot3(t_fractol *fractol, t_complex c);
int						julia(t_fractol *fractol, t_complex c);
int						julia2(t_fractol *fractol, t_complex c);
int						julia3(t_fractol *fractol, t_complex c);
void					set_defaults(t_fractol *fractol);

#endif
