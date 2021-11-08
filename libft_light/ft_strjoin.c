/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:15:53 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:38:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_light.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(join = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_bzero(join, len + 1);
	join = ft_strcat(join, (char*)s1);
	join = ft_strcat(join, (char*)s2);
	return (join);
}
