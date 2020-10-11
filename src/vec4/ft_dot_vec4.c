/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dot_vec4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:05:16 by wkorande          #+#    #+#             */
/*   Updated: 2020/10/11 16:55:34 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"

float	ft_dot_vec4(t_vec4 a, t_vec4 b)
{
	float d;

	d = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (d);
}