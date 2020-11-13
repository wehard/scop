/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:21:00 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/13 23:21:09 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

t_mat4	mat4_scale(t_vec3 scale)
{
	t_mat4 mat;

	mat = mat4_identity();
	mat.data[0] = scale.x;
	mat.data[5] = scale.y;
	mat.data[10] = scale.z;
	return (mat);
}
