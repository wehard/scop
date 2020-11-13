/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:24:30 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/13 23:35:21 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

t_mat4	mat4_mul(t_mat4 a, t_mat4 b)
{
	int		y;
	int		x;
	int		i;
	t_mat4	c;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			i = 0;
			c.data[y * 4 + x] = 0;
			while (i < 4)
			{
				c.data[y * 4 + x] += a.data[y * 4 + i] * b.data[i * 4 + x];
				i++;
			}
			x++;
		}
		y++;
	}
	return (c);
}
