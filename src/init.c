/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:31:24 by esnowpea          #+#    #+#             */
/*   Updated: 2020/07/15 14:32:19 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "error_message.h"

t_img				*init_image(void *mlx)
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

t_complex			init_complex(double re, double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

void				set_defaults(t_fractol *fractol)
{
	fractol->max_itr = 50;
	fractol->min = init_complex(-2.0 * WIN_WIDTH / WIN_HEIGHT, -2.0);
	fractol->max = init_complex(2.0 * WIN_WIDTH / WIN_HEIGHT, 2.0);
	fractol->mouse_press = 0;
	fractol->space_press = 0;
	fractol->change_color = 0;
	fractol->julia = init_complex(-0.77, 0.122);
}

static int			(*get_formula(char *name)) (t_fractol *fractol, t_complex c)
{
	size_t				i;
	int					(*formula)(t_fractol *, t_complex);
	static t_formula	formulas[] = {
			{ "Mandelbrot", &mandelbrot },
			{ "Mandelbrot_V2", &mandelbrot2 },
			{ "Mandelbrot_V3", &mandelbrot3 },
			{ "Julia", &julia },
			{ "Julia_V2", &julia2 },
			{ "Julia_V3", &julia3 }
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

t_fractol			*init_fractol(char *name)
{
	t_fractol	*fractol;

	if (!(fractol = (t_fractol *)ft_memalloc(sizeof(t_fractol))))
		terminate(ERR_FRACTOL_INIT);
	if (!(fractol->mlx = mlx_init()))
		terminate(ERR_MLX_INIT);
	if (!(fractol->win = mlx_new_window(fractol->mlx, WIN_WIDTH, WIN_HEIGHT,
			name)))
		terminate(ERR_WINDOW_INIT);
	fractol->img = init_image(fractol->mlx);
	set_defaults(fractol);
	if (ft_strequ(name, "Julia") || ft_strequ(name, "Julia_V2") ||
			ft_strequ(name, "Julia_V3"))
		fractol->is_julia = 1;
	else
		fractol->is_julia = 0;
	if (!(fractol->formula = get_formula(name)))
		terminate(ERR_FRACTAL_NAME);
	event_handler(fractol);
	return (fractol);
}
