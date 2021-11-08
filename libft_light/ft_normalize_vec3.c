/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_vec3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:05:37 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 19:21:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	ft_normalize_vec3(t_vec3 v)
{
	t_vec3	new;
	float	l;

	l = ft_len_vec3(v);
	new = ft_div_vec3(v, l);
	return (new);
}
