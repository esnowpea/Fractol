/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:30:52 by esnowpea          #+#    #+#             */
/*   Updated: 2020/07/15 15:04:41 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "key_define.h"

static void	change_max_iteration(int key, t_fractol *fractol)
{
	if (key == MAIN_PAD_PLUS || key == NUM_PAD_PLUS)
	{
		if (fractol->max_itr < 50)
			fractol->max_itr += 1;
		else if (fractol->max_itr < 1000000000)
			fractol->max_itr = (int)(fractol->max_itr * 1.05);
	}
	if (key == MAIN_PAD_MINUS || key == NUM_PAD_MINUS)
	{
		if (fractol->max_itr > 50)
			fractol->max_itr = (int)(fractol->max_itr * 0.95);
		else if (fractol->max_itr > 1)
			fractol->max_itr -= 1;
	}
	draw_fractal(fractol);
}

int			key_press(int key, t_fractol *fractol)
{
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == MAIN_PAD_R)
	{
		set_defaults(fractol);
		draw_fractal(fractol);
	}
	else if (key == MAIN_PAD_MINUS || key == NUM_PAD_MINUS ||
	key == MAIN_PAD_PLUS || key == NUM_PAD_PLUS)
		change_max_iteration(key, fractol);
	else if (key == MAIN_PAD_SPACE)
		fractol->space_press = 1;
	return (0);
}

int			key_release(int key, t_fractol *fractol)
{
	if (key == MAIN_PAD_SPACE)
		fractol->space_press = 0;
	return (0);
}

int			close_press(void *param)
{
	(void)param;
	exit(0);
}

void		event_handler(t_fractol *fractol)
{
	mlx_hook(fractol->win, 2, 0, key_press, fractol);
	mlx_hook(fractol->win, 3, 0, key_release, fractol);
	mlx_hook(fractol->win, 17, 0, close_press, fractol);
	mlx_hook(fractol->win, 4, 0, mouse_press, fractol);
	mlx_hook(fractol->win, 6, 0, mouse_move, fractol);
	mlx_hook(fractol->win, 5, 0, mouse_release, fractol);
}
