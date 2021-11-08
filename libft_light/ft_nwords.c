/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nwords.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:28:18 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 19:20:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_light.h"

int	ft_nwords(char *str, char delim)
{
	int	word;
	int	n;
	int	i;

	if (!str || !delim)
		return (0);
	word = 0;
	n = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != delim)
		{
			if (word == 0)
			{
				word = 1;
				n++;
			}
		}
		else if (str[i] == delim)
			word = 0;
		i++;
	}
	return (n);
}
