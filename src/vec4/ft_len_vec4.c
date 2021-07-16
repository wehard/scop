/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_vec4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:04:52 by wkorande          #+#    #+#             */
/*   Updated: 2021/07/16 16:58:12 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"
#include <math.h>

float	ft_len_vec3(t_vec4 v)
{
	float	l;

	if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f)
		return (0.0f);
	l = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return (l);
}
