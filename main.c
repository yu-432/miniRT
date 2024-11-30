/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:18:28 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/30 14:59:52 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "miniRT.h"

# define WIDTH 800
# define HEIGHT 800

// bool hit_sphere(t_vec *Camera, t_vec *Sphere, double sp_size)
// {
	
// }

// t_vec	trans_coord(t_vec *vec)
// {
// 	t_vec res;

// 	res.x = 
// }


int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void normalize(t_vec *vec)
{
	double vec_size;

	vec_size = sqrt(vec_dot(vec, vec));
	vec->x = vec->x / vec_size;
	vec->y = vec->y / vec_size;
	vec->z = vec->z / vec_size;
}

int	main(void)
{
	void *mlx;
	void *win;
	double t;
	double sp_size = 1.0;
	t_vec Sphere = {0, 0, 5};
	t_vec Camera = {0, 0, -5};
	t_vec Light = {-5, 5 , -5};
	t_vec pw;
	t_vec *intersection_pos;
	t_vec *incident_ray;
	t_vec *normal_vec;
	double inner;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	for (int i = 0; i < WIDTH; i++)
	{
		pw.y = -2.0 * i / WIDTH + 1.0;
		for (int j = 0; j < HEIGHT; j++)
		{
			pw.x = 2.0 * j / HEIGHT - 1.0;

			t_vec *ray_de = vec_sub(&pw, &Camera);
			t_vec *tmp = vec_sub(&Camera, &Sphere);

			double A = vec_dot(ray_de, ray_de);
			double B = 2.0 * vec_dot(tmp, ray_de);
			double C = vec_dot(tmp, tmp) - sp_size * sp_size;
			double D = B * B - 4 * A * C;
			if (D == 0)
			{
				t = -B / (2 * A);
			}
			else if (D > 0)
			{
				double t1 = (- B + sqrt(D)) / (2 * A);
				double t2 = (- B - sqrt(D)) / (2 * A);
				t = (t1 < t2) ? t1 : t2;
			}
			else
				t = 0;
			if (t > 0)
			{
				intersection_pos = vec_add(&Camera, vec_mult(ray_de, t));
				incident_ray = vec_sub(&Light, intersection_pos);
				normalize(incident_ray);
				normal_vec = vec_sub(intersection_pos, &Sphere);
				normalize(normal_vec);
				inner = vec_dot(incident_ray, normal_vec);
				if (inner <= 0)
					inner = 0;
				mlx_pixel_put(mlx, win, i, j, create_trgb(0, 255 * inner, 255 * inner, 255 * inner));
			}
			else
				mlx_pixel_put(mlx, win, i, j, );
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