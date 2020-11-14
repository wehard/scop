/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:25:47 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/14 20:39:19 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void camera_update(t_camera *camera)
{
	camera->view_matrix = mat4_lookat(camera->position, ft_add_vec3(camera->position, camera->forward), ft_make_vec3(0,1,0));
}

void camera_init(t_camera *camera, t_vec3 pos, t_vec3 forward, float yaw, float pitch)
{
	if (!camera)
		return;
	camera->position = pos;
	camera->forward = forward;
	camera->yaw = yaw;
	camera->pitch = pitch;
	camera_update(camera);
}
