/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 17:47:41 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 20:22:54 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

typedef struct s_vec2i
{
	int			x;
	int			y;
}				t_vec2i;

typedef struct s_vec2
{
	float		x;
	float		y;
}				t_vec2;

t_vec2i			ft_make_vec2i(int x, int y);
void			ft_set_vec2i(t_vec2i *v2i, t_vec2 v2);
t_vec2i			ft_get_vec2i(t_vec2 v);
t_vec2			ft_make_vec2(float x, float y);
t_vec2			ft_add_vec2(t_vec2 v1, t_vec2 v2);
t_vec2			ft_div_vec2(t_vec2 v, float t);
float			ft_dot_vec2(t_vec2 v1, t_vec2 v2);
t_vec2			ft_invert_vec2(t_vec2 v);
float			ft_len_vec2(t_vec2 v);
t_vec2			ft_normalize_vec2(t_vec2 v);
t_vec2			ft_sub_vec2(t_vec2 v1, t_vec2 v2);
t_vec2			ft_mul_vec2(t_vec2 v, float t);
t_vec2			ft_parse_vec2(char *str);

#endif
