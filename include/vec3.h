/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:47:41 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 20:23:13 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

t_vec3			ft_make_vec3(float x, float y, float z);
void			ft_set_vec3(t_vec3 *v, float x, float y, float z);
t_vec3			ft_add_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			ft_sub_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			ft_mul_vec3(t_vec3 v, float t);
t_vec3			ft_mul_vec3_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			ft_div_vec3(t_vec3 v, float t);
float			ft_len_vec3(t_vec3 v1);
float			ft_dot_vec3(t_vec3 v1, t_vec3 v2);
t_vec3			ft_normalize_vec3(t_vec3 v);
t_vec3			ft_invert_vec3(t_vec3 v);
t_vec3			ft_reflect_vec3(t_vec3 v, t_vec3 n);
t_vec3			ft_refract_vec3(t_vec3 i, t_vec3 normal, float ior);
t_vec3			ft_cross_vec3(t_vec3 a, t_vec3 b);
t_vec3			ft_rotate_vec3(t_vec3 v, t_vec3 rot);
t_vec3			ft_rotate_vec3_x(t_vec3 v, float a);
t_vec3			ft_rotate_vec3_y(t_vec3 v, float a);
t_vec3			ft_rotate_vec3_z(t_vec3 v, float a);
t_vec3			ft_parse_vec3(char *str);
t_vec3			ft_clamp_vec3(t_vec3 v, float min, float max);

#endif
