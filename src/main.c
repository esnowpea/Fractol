/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esnowpea <esnowpea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:32:50 by esnowpea          #+#    #+#             */
/*   Updated: 2020/03/16 16:40:02 by esnowpea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "error_message.h"

void	terminate(char *s)
{
	ft_putendl_fd(s, 2);
	exit(0);
}

void	help(void)
{
	ft_putendl("Usage: ./fractol <name>");
	ft_putendl("List of available fractals:");
	ft_putendl(" * Mandelbrot");
	ft_putendl(" * Julia");
	ft_putendl(" * Mandelbrot_z^3");
	ft_putendl(" * Mandelbrot_z^4");
	ft_putendl(" * Julia_z^3");
	ft_putendl(" * Julia_z^4");
}

int		main(int ac, char **av)
{
	t_fractol	*fractol;

	if (ac != 2)
	{
		help();
		exit(0);
	}
	fractol = init_fractol(av[ac - 1]);
	draw_fractal(fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
