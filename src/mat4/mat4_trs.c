/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_trs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:23:17 by wkorande          #+#    #+#             */
/*   Updated: 2021/07/16 16:52:39 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

t_mat4	mat4_trs(t_vec3 pos, t_vec3 rot, t_vec3 scale)
{
	t_mat4	trs;
	t_mat4	s;
	t_mat4	r;
	t_mat4	t;

	s = mat4_scale(scale);
	r = mat4_rot_xyz(rot);
	t = mat4_translate(pos);
	trs = mat4_mul(s, r);
	trs = mat4_mul(trs, t);
	return (trs);
}
