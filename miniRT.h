/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:53 by yooshima          #+#    #+#             */
/*   Updated: 2024/12/04 17:25:31 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct s_vec
{
	double x;
	double y;
	double z;
}	t_vec;

typedef struct s_discriminant
{
	double A;
	double B;
	double C;
	double D;
}	t_abcd;

typedef struct s_data
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}	t_data;

typedef struct s_obj
{
	// t_obj_kind kind;一旦球体しか存在しません
	t_vec pos;
	double diameter;
	int rgb[3];
}	t_objs;

typedef struct s_intersection
{
	double t;
	t_vec intersection_pos;
	t_vec incident_ray_vec;
	t_vec normal_vec;
	double inner;
}	t_intersection;

typedef enum s_rgb
{
	R,
	G,
	B,
}	t_rgb;

t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mult(t_vec a, double mult);
double vec_dot(t_vec a, t_vec b);
double calc_inner(t_vec a, t_vec b);
t_objs sample_input(void);
double calc_inner(t_vec a, t_vec b);



# endif