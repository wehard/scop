/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 20:11:58 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/15 11:45:48 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

#include <stdlib.h>
#include <stdint.h>
#include "scop.h"

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
void shader_use(t_shader *shader);
void 			shader_set_uniform_mat4(t_shader *shader, char *loc_name, t_mat4 m);
void shader_set_uniform_vec3(t_shader *shader, char *loc_name, t_vec3 v);
void shader_set_uniform_vec4(t_shader *shader, char *loc_name, t_vec4 v);
void shader_set_uniform_vec3_array(t_shader *shader, char *loc_name, t_vec3 *v, size_t count);
void shader_set_uniform_vec4_array(t_shader *shader, char *loc_name, t_vec4 *v, size_t count);

#endif
