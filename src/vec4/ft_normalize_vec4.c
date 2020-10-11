/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_vec4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:05:37 by wkorande          #+#    #+#             */
/*   Updated: 2020/10/11 16:57:15 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4.h"

t_vec4	ft_normalize_vec4(t_vec4 v)
{
	t_vec4 new;
	double l;

	l = ft_len_vec4(v);
	new = ft_div_vec4(v, l);
	return (new);
}
