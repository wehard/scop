/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:31:04 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:43:35 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft_light.h"

void	ft_putstr(char const *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}
