/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:03:19 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:50:13 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_light.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *sub;

	if (!s || !(sub = (char*)ft_memalloc(len + 1)))
		return (NULL);
	sub = ft_strncpy(sub, s + start, len);
	return (sub);
}
