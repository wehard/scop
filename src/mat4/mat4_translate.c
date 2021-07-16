/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:20:13 by wkorande          #+#    #+#             */
/*   Updated: 2021/07/16 16:51:40 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

t_mat4	mat4_translate(t_vec3 translation)
{
	t_mat4	mat;

	mat = mat4_identity();
	mat.data[12] = translation.x;
	mat.data[13] = translation.y;
	mat.data[14] = translation.z;
	return (mat);
}
