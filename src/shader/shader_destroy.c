/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 20:16:24 by wkorande          #+#    #+#             */
/*   Updated: 2021/07/16 17:06:14 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"
#include <GL/glew.h>

void shader_destroy(t_shader *shader)
{
	glDeleteProgram(shader->program_id);
	free(shader->vert_src);
	free(shader->frag_src);
	free(shader);
}
