/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 12:53:29 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 16:21:38 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEX_H
# define TEX_H

# include <stdint.h>

typedef struct s_tex
{
	uint32_t		tex_id;
	unsigned int	width;
	unsigned int	height;
	int				num_channels;
}				t_tex;

t_tex	*tex_load(const char *filepath);
void	tex_bind(t_tex *tex);

#endif
