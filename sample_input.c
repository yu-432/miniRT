/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:46:03 by yooshima          #+#    #+#             */
/*   Updated: 2024/12/05 14:05:09 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_objs sample_input(void)
{
	t_objs obj;

	obj.pos.x = 0;
	obj.pos.y = -1.5;
	obj.pos.z = 15;
	obj.diameter = 1;
	obj.rgb[R] = 230;
	obj.rgb[G] = 255;
	obj.rgb[B] = 255;
	obj.next = NULL;
	obj.next = malloc(sizeof(t_objs));
	obj.next->pos.x = 0;
	obj.next->pos.y = 0;
	obj.next->pos.z = 15;
	obj.next->diameter = 1;
	obj.next->rgb[R] = 255;
	obj.next->rgb[G] = 230;
	obj.next->rgb[B] = 255;
	obj.next->next = NULL;
	obj.next->next = malloc(sizeof(t_objs));
	obj.next->next->pos.x = 0;
	obj.next->next->pos.y = 1.5;
	obj.next->next->pos.z = 15;
	obj.next->next->diameter = 1;
	obj.next->next->rgb[R] = 255;
	obj.next->next->rgb[G] = 255;
	obj.next->next->rgb[B] = 230;
	obj.next->next->next = NULL;
	return (obj);
}
