/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:18:28 by yooshima          #+#    #+#             */
/*   Updated: 2024/12/04 17:41:17 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "miniRT.h"

# define WIDTH 800
# define HEIGHT 800

# define AMBIENT_REFLECTION 0.1
# define DIFFUSE_REFLECTION 0.6
# define SPECULAR_REFLECTION 0.3
# define LIGHT_INTENSITY 1.0
# define AMBIENT_LIGHT_RATIO 0.2
# define LUMINANCE_RATIO 0.6

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void normalize(t_vec *vec)
{
	double vec_size;

	vec_size = sqrt(vec_dot(*vec, *vec));
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

void init_mlx(t_data *mlx_data)
{
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
	{
		printf("Error\nmlx_init failed\n");
		exit(1);
	}
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);//指定されるサイズに変更する必要がある？
	if (!mlx_data->img)
	{
		printf("Error\nmlx_new_image failed\n");
		exit(1);
	}
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, &mlx_data->bits_per_pixel, \
										&mlx_data->line_length, &mlx_data->endian);
	mlx_data->win = mlx_new_window(mlx_data->mlx, WIDTH, HEIGHT, "miniRT");
}

t_abcd hit_sphere(t_vec pw, t_vec camera, t_objs objs)
{
	t_abcd abcd;
	t_vec ray;
	t_vec tmp;

	ray = vec_sub(pw, camera);
	tmp = vec_sub(camera, objs.pos);
	abcd.A = vec_dot(ray, ray);
	abcd.B = 2.0 * vec_dot(tmp, ray);
	abcd.C = vec_dot(tmp, tmp) - objs.diameter * objs.diameter;
	abcd.D = abcd.B * abcd.B - 4 * abcd.A * abcd.C;
	return (abcd);
}

double calc_distance(t_abcd abcd)
{
	double t1;
	double t2;

	if (abcd.D == 0) //交点が1つ
		return (-abcd.B / (2 * abcd.A));
	else if (abcd.D > 0) //交点が2つの場合近い方
	{
		t1 = (-abcd.B + sqrt(abcd.D)) / (2 * abcd.A);
		t2 = (-abcd.B - sqrt(abcd.D)) / (2 * abcd.A);
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	else //無い
		return (0);
}

t_intersection get_intersection_point(t_vec pw, t_vec camera, t_objs objs)
{
	t_intersection intersection;
	t_abcd abcd;
	

	abcd = hit_sphere(pw, camera, objs);
	intersection.t = calc_distance(abcd);//交点までの距離
	if (intersection.t <= 0)
		return (intersection);
	intersection.intersection_pos = vec_add(camera, \
		vec_mult(vec_sub(pw, camera), intersection.t));//交点座標の計算
	return (intersection);
}

void calc_incident_and_normal_vec(t_intersection *intersection, t_vec light, t_vec obj_pos)
{
	intersection->incident_ray_vec = vec_sub(light, intersection->intersection_pos);//入射ベクトルの計算
	normalize(&intersection->incident_ray_vec);//正規化
	intersection->normal_vec = vec_sub(intersection->intersection_pos, obj_pos);//法線ベクトル
	normalize(&intersection->normal_vec);//正規化
	intersection->inner = calc_inner(intersection->incident_ray_vec, intersection->normal_vec);
}
//鏡面反射
double calc_specular_reflection(t_vec camera, t_intersection *intersection)
{
	t_vec normal_reflection_vec;
	t_vec inverse_ray_vec;
	double specular_inner;

	if (intersection->inner <= 0)
		return (0);
	normal_reflection_vec = vec_sub(vec_mult(intersection->normal_vec, \
		vec_dot(intersection->normal_vec, intersection->incident_ray_vec) * 2), intersection->incident_ray_vec);
	inverse_ray_vec = vec_mult(camera, -1);
	normalize(&inverse_ray_vec);
	// specular_inner = calc_inner(normal_reflection_vec, inverse_ray_vec); [0,1]の正規化？わからん
	specular_inner = vec_dot(normal_reflection_vec, inverse_ray_vec);
	return(SPECULAR_REFLECTION * LIGHT_INTENSITY * pow(specular_inner, 8));
}

double calc_radiance(t_intersection *intersection, t_objs objs, t_vec camera, t_vec light)
{
	double radiance_specular;//鏡面輝度
	double radiance_diffuse;//拡散輝度
	double radiance_ambient;//環境輝度

	calc_incident_and_normal_vec(intersection, light, objs.pos);
	radiance_specular = calc_specular_reflection(camera, intersection);
	radiance_diffuse = DIFFUSE_REFLECTION * LUMINANCE_RATIO * intersection->inner;
	radiance_ambient = AMBIENT_REFLECTION * AMBIENT_LIGHT_RATIO;
	return (radiance_ambient + radiance_diffuse + radiance_specular);
}

int	main(void) //drawingのみの実装
{
	t_data mlx_data;
	double radiance;
	t_vec Camera = {0, 0, -5};//FOV, 方向ベクトル が存在する
	t_vec Light = {-5, 5 , -5};//輝度比light brightness ratio
	t_vec pw;//スクリーンの点の座標
	t_objs objs;
	t_intersection intersection;

	objs = sample_input();//球体1つだけ
	init_mlx(&mlx_data);
	for (int i = 0; i < WIDTH; i++)
	{
		pw.y = -2.0 * i / WIDTH + 1.0;//スクリーン座標Yを三次元空間座標に変換する
		for (int j = 0; j < HEIGHT; j++)
		{
			pw.x = 2.0 * j / HEIGHT - 1.0;//スクリーン座標Xを三次元空間座標に変換する
			intersection = get_intersection_point(pw, Camera, objs);//交点が存在する場合カメラから交点までの距離,座標を返す
			if (intersection.t > 0)
			{
				radiance = calc_radiance(&intersection, objs, Camera, Light);
				my_pixel_put(&mlx_data, i, j, create_trgb(0, 230 * radiance, \
					255 * radiance, 255 * radiance));
			}
			else
				my_pixel_put(&mlx_data, i, j, create_trgb(0, 140, 220, 230));
		}
	}
	mlx_put_image_to_window(mlx_data.mlx, mlx_data.win, mlx_data.img, 0, 0);
	mlx_loop(mlx_data.mlx);
	return (0);
}



// parser連結リスト
//  ファイルの読み込み
//  値のエラーチェック
// 実行部分
//  mlx初期化
//  描画
//   交点チェック　種類別
//  mlx loop
