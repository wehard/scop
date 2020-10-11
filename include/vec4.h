/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 16:21:15 by wkorande          #+#    #+#             */
/*   Updated: 2020/10/11 16:57:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4_H
# define VEC4_H

typedef struct 	s_vec4
{
	union { float x, r;};
	union { float y, g;};
	union { float z, b;};
	union { float w, a;};
}				t_vec4;

t_vec4	ft_add_vec4(t_vec4 a, t_vec4 b);
t_vec4	ft_sub_vec4(t_vec4 a, t_vec4 b);
t_vec4	ft_mul_vec4(t_vec4 v, float t);
t_vec4	ft_cross_vec4(t_vec4 a, t_vec4 b);
float	ft_len_vec3(t_vec4 v);
t_vec4	ft_div_vec4(t_vec4 v, float t);
float	ft_dot_vec4(t_vec4 a, t_vec4 b);
t_vec4	ft_normalize_vec4(t_vec4 v);

#endif
