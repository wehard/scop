/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mul_vec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:03:27 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 19:21:16 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	ft_mul_vec3(t_vec3 v, float t)
{
	t_vec3	new;

	new.x = v.x * t;
	new.y = v.y * t;
	new.z = v.z * t;
	return (new);
}