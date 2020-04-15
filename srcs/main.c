/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timuryakubov <timuryakubov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 22:03:05 by timuryakubo       #+#    #+#             */
/*   Updated: 2020/04/16 00:59:12 by timuryakubo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractal				*get_fract_params()
{
	static t_fractal 	fract_params[5] = {
		{"mandelbrot", &f_mandelbrot, 1},
		{"julia", &f_julia, 1},
		{"burningship", &f_burningship, 1},
		{"mandelbar", &f_mandelbar, 1},
		{NULL, NULL, 0}
	};
	return (fract_params);
}

t_fractal				*is_fractal(char *str)
{
	t_fractal			*f;
	int					i;

	f = get_fract_params();
	i = -1;
	while (f[++i].name != NULL)
	{
		if (ft_strcmp(f[i].name, str) == 0)
			return (&f[i]);
	}
	return (NULL);
}

int						main(int argc, char **argv)
{
	t_mlx				mlx;
	
	if (argc != 2 || !(mlx.fractal = is_fractal(argv[1])))
		return(usage_out());
	fractal_init(&mlx);
	if (!(mlx_window_img_init(&mlx)))
		return(pr_out("Error : could not initialize mlx\n"));
	draw(&mlx);
	mlx_hook(mlx.win_ptr, 2, 0, handle_key, &mlx);
	mlx_hook(mlx.win_ptr, 4, 0, zoom_change, &mlx);
	if (!(ft_strcmp(mlx.fractal->name, "julia")))
		mlx_hook(mlx.win_ptr, 6, 0, julia_mouse_move, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}