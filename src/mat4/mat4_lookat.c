/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_lookat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:26:14 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/13 23:26:42 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

t_mat4	mat4_lookat(t_vec3 from, t_vec3 to, t_vec3 world_up)
{
	t_mat4	m;
	t_vec3	f;
	t_vec3	s;
	t_vec3	u;

	f = ft_normalize_vec3(ft_sub_vec3(to, from));
	s = ft_normalize_vec3(ft_cross_vec3(f, world_up));
	u = ft_cross_vec3(s, f);

	m = mat4_identity();

	m.data[0] = s.x;
	m.data[4] = s.y;
	m.data[8] = s.z;

	m.data[1] = u.x;
	m.data[5] = u.y;
	m.data[9] = u.z;

	m.data[2] = -f.x;
	m.data[6] = -f.y;
	m.data[10] = -f.z;

	m.data[12] = -ft_dot_vec3(s, from);
	m.data[13] = -ft_dot_vec3(u, from);
	m.data[14] = ft_dot_vec3(f, from);
	return (m);
}
