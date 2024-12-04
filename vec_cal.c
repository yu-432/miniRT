/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:40 by yooshima          #+#    #+#             */
/*   Updated: 2024/12/04 17:26:24 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vec	vec_mult(t_vec a, double mult)
{
	t_vec res;

	res.x = a.x * mult;
	res.y = a.y * mult;
	res.z = a.z * mult;
	return (res);
}

double vec_dot(t_vec a, t_vec b)
{
	return(a.x * b.x + a.y * b.y + a.z * b.z);
}

double vec_length(t_vec a)
{
	return (sqrt(vec_dot(a, a)));
}

double calc_inner(t_vec a, t_vec b)
{
	double inner;
	double normalized_inner;
	double norm_a;
	double norm_b;

	inner = vec_dot(a, b);
	norm_a = vec_length(a);
	norm_b = vec_length(b);
	normalized_inner = inner / (norm_a * norm_b);
	return (fmax(0, fmin(1.0, normalized_inner)));
}