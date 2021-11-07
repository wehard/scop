/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:13:30 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/07 16:17:58 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_H
# define MAT4_H

# include "vec3.h"

/*
** m0 m4 m8  m12
** m1 m5 m9  m13
** m2 m6 m10 m14
** m3 m7 m11 m15
**
** 00 01 02 03
** 10 11 12 13
** 20 21 22 23
** 30 31 32 33
*/

typedef struct s_mat4
{
	float		data[16];
}				t_mat4;

t_mat4			mat4_init(void);
t_mat4			mat4_identity(void);
t_mat4			mat4_translate(t_vec3 translation);
t_mat4			mat4_scale(t_vec3 scale);
t_mat4			mat4_rot_x(float angle);
t_mat4			mat4_rot_y(float angle);
t_mat4			mat4_rot_z(float angle);
t_mat4			mat4_mul(t_mat4 a, t_mat4 b);
t_mat4			mat4_lookat(t_vec3 from, t_vec3 to, t_vec3 world_up);
t_mat4			mat4_perspective(float fov, float aspect, float zn, float zf);
t_mat4			mat4_rot_x(float angle);
t_mat4			mat4_rot_y(float angle);
t_mat4			mat4_rot_z(float angle);
t_mat4			mat4_rot_xyz(t_vec3 rotation);
t_mat4			mat4_trs(t_vec3 pos, t_vec3 rot, t_vec3 scale);

#endif
