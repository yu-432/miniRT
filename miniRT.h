/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:53 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/30 19:25:51 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define BLUE 0x004169e1
#define BLUE_R 41
#define BLUE_G 69
#define BLUE_B 241
#define RED 0x00ff6347
#define GREEN 0x0090ee90

typedef struct s_vec
{
	double x;
	double y;
	double z;
}	t_vec;

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}	t_data;

t_vec	*vec_add(t_vec *a, t_vec *b);
t_vec	*vec_sub(t_vec *a, t_vec *b);
t_vec	*vec_mult(t_vec *a, double mult);
double vec_dot(t_vec *a, t_vec *b);


# endif