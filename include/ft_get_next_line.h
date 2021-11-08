/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 20:39:53 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 20:20:59 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft_light.h"

# define BUFF_SIZE 1
# define MAX_FD 4864

typedef struct s_gnl
{
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;
	int		bytes;
}		t_gnl;

typedef struct s_gnl_tmp
{
	char	*tmp;
	int		len;
}		t_gnl_tmp;

int	ft_get_next_line(const int fd, char **line);

#endif
