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

int main(int ac, char **av)
{
	t_fractol	*fractol;
	void		*mlx;

	mlx = mlx_init();
	fractol = init_fractol(av[ac - 1] ,mlx);
	draw_fractal(fractol);
	mlx_loop(fractol->mlx);
}
