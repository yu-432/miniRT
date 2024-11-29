/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:18:28 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/29 12:03:44 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "miniRT.h"

# define WIDTH 800
# define HEIGHT 500



int	main(void)
{
	void *mlx;
	void *win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			mlx_pixel_put(mlx, win, i, j, BLUE);
		}
	}
	mlx_loop(mlx);
	return (0);
}

// parser
//  input argv
//  parse argv
// drawing
//