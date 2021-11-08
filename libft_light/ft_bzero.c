/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:48:31 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:45:29 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_light.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char *p;

	if (n <= 0)
		return ;
	p = (unsigned char*)s;
	while (n-- > 0)
		*(p++) = 0;
}
