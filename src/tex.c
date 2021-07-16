/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 12:53:10 by wkorande          #+#    #+#             */
/*   Updated: 2021/07/16 17:02:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include "scop.h"
#include "tex.h"
#include "stb_image.h"

t_tex	*tex_load(const char *filepath)
{
	t_tex			*tx;
	unsigned char	*data;

	tx = (t_tex *)malloc(sizeof(t_tex));
	if (!tx)
		exit_message("Failed to allocate t_tex!");
	data = stbi_load(filepath, &tx->width, &tx->height, &tx->num_channels, 0);
	if (!data)
		exit_message("Failed to load texture file!");
	glGenTextures(1, &tx->tex_id);
	glBindTexture(GL_TEXTURE_2D, tx->tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tx->width, tx->height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return (tx);
}

void	tex_bind(t_tex *tex)
{
	if (!tex)
	{
		return ;
	}
	glBindTexture(GL_TEXTURE_2D, tex->tex_id);
}
