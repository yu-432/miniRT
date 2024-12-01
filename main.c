/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:18:28 by yooshima          #+#    #+#             */
/*   Updated: 2024/12/01 13:07:58 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "miniRT.h"

# define WIDTH 800
# define HEIGHT 800

# define AMBIENT_REFLECTION 0.1
# define DIFFUSE_REFLECTION 0.6
# define SPECULAR_REFLECTION 0.3

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

void my_pixel_put(t_data *data, int x, int y , int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void *mlx;
	void *win;
	t_data img;
	double t;
	double sp_size = 1.0;
	double ambient_light = 0.2;//ambient lighting ratio
	double luminance_ratio = 0.6;
	double ambient_radiance_ratio;
	double luminance_radiance_ratio;
	double direct_light_radiance;
	t_vec Sphere = {0, 0, 5};
	t_vec Camera = {0, 0, -5};//FOV, 方向ベクトル が存在する
	t_vec Light = {-5, 5 , -5};//輝度比light brightness ratio
	t_vec pw;
	t_vec *intersection_pos;
	t_vec *incident_ray;
	t_vec *normal_vec;
	double inner;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
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
				inner = vec_dot(incident_ray, normal_vec);//内積
				if (inner <= 0)
					inner = 0;

				//ここから2-5-2-2
				ambient_radiance_ratio = AMBIENT_REFLECTION * ambient_light;
				luminance_radiance_ratio = DIFFUSE_REFLECTION * luminance_ratio * inner;//???
				
				if (inner > 0)
				{
					t_vec *orthorectified_vec = \
						vec_sub(vec_mult(normal_vec, vec_dot(normal_vec, incident_ray) * 2), incident_ray);

					t_vec *inverse_vec = vec_mult(&Camera, -1);
					normalize(inverse_vec);
					inner = vec_dot(inverse_vec, orthorectified_vec);
					// normalize(inner);
					direct_light_radiance = SPECULAR_REFLECTION * 1.0 //光源の光の強度
						* pow(vec_dot(inverse_vec, orthorectified_vec), 8);
				}
				else
					direct_light_radiance = 0;
				double radiance_reflected_light = ambient_radiance_ratio + luminance_radiance_ratio + direct_light_radiance;
				my_pixel_put(&img, i, j, create_trgb(0, 230 * radiance_reflected_light, 255 * radiance_reflected_light, 255 * radiance_reflected_light));
			}
			else
				my_pixel_put(&img, i, j, create_trgb(0, 140, 220, 230));
		}
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

// parser
//  input argv
//  parse argv
// drawing
//