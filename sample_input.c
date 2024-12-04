/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:46:03 by yooshima          #+#    #+#             */
/*   Updated: 2024/12/02 15:50:07 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_objs sample_input(void)
{
	t_objs obj;

	obj.pos.x = 0;
	obj.pos.y = 0;
	obj.pos.z = 5;
	obj.diameter = 1;
	obj.rgb[R] = 230;
	obj.rgb[G] = 255;
	obj.rgb[B] = 255;
	return (obj);
}
