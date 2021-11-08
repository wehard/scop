/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dot_vec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:05:16 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 19:24:38 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

float	ft_dot_vec3(t_vec3 v1, t_vec3 v2)
{
	float	dot;

	dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (dot);
}
