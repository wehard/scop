/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 12:53:29 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/22 13:20:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEX_H
# define TEX_H

# include <stdint.h>

typedef struct	s_tex
{
	uint32_t	tex_id;
	int			width;
	int			height;
	int			num_channels;
}				t_tex;


t_tex	*tex_load(const char *filepath);
void	tex_bind(t_tex *tex);

#endif
