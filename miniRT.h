/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:53 by yooshima          #+#    #+#             */
/*   Updated: 2024/12/05 13:53:37 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <strings.h>

typedef struct s_vec
{
	double x;
	double y;
	double z;
}	t_vec;


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

typedef enum s_obj_kind
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_kind;

typedef struct s_objs
{
	t_obj_kind kind;
	t_vec pos;
	double diameter;
	int rgb[3];
	struct s_objs *next;
}	t_objs;

typedef struct s_hit
{
	double A;
	double B;
	double C;
	double D;
	t_objs *obj;
}	t_hit;

typedef struct s_intersection
{
	t_objs *obj;
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