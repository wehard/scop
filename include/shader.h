/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 20:11:58 by wkorande          #+#    #+#             */
/*   Updated: 2020/09/25 21:04:28 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

#include <stdlib.h>
#include <stdint.h>

#define MAX_SHADER_SRC_SIZE 10000

typedef struct	s_shader
{
	uint32_t	program_id;
	uint32_t	vert_id;
	uint32_t	frag_id;
	char 		*vert_src;
	char 		*frag_src;
}				t_shader;

t_shader 		*create_shader(char *vert_path, char *frag_path);
void 			destroy_shader(t_shader *shader);

#endif
