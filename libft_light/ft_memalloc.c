/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:41:06 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:50:42 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_light.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = (void*)malloc(size)))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}
