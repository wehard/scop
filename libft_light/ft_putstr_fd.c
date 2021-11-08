/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:32:35 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:35:57 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft_light.h"

void	ft_putstr_fd(char const *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
