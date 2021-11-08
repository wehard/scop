/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 20:39:53 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:44:19 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft_light.h"

# define BUFF_SIZE 1
# define MAX_FD 4864

int ft_get_next_line(const int fd, char **line);

#endif
