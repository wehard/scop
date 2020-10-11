/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_vec4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:04:20 by wkorande          #+#    #+#             */
/*   Updated: 2020/10/11 16:54:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"

t_vec4	ft_div_vec4(t_vec4 v, float t)
{
	t_vec4 new;

	if (t == 0.0)
		return (v);
	new.x = v.x / t;
	new.y = v.y / t;
	new.z = v.z / t;
	return (new);
}
