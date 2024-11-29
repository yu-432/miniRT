/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:40 by yooshima          #+#    #+#             */
/*   Updated: 2024/11/29 11:23:38 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	*vec_add(t_vec *a, t_vec *b)
{
	t_vec *res;

	res = calloc(1, sizeof(t_vec));
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	return (res);
}

t_vec	*vec_sub(t_vec *a, t_vec *b)
{
	t_vec *res;

	res = calloc(1, sizeof(t_vec));
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	return (res);
}

t_vec	*vec_mult(t_vec *a, double mult)
{
	t_vec *res;

	res = calloc(1, sizeof(t_vec));
	res->x = a->x * mult;
	res->y = a->y * mult;
	res->z = a->z * mult;
	return (res);
}