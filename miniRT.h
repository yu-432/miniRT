/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:53 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/29 12:04:03 by yooshima         ###   ########.fr       */
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

#define BLUE 0x004169e1
#define RED 0x00ff6347
#define GREEN 0x0090ee90

t_vec	*vec_add(t_vec *a, t_vec *b);
t_vec	*vec_sub(t_vec *a, t_vec *b);
t_vec	*vec_mult(t_vec *a, double mult);


# endif