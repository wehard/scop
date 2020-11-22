/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:20:00 by wkorande          #+#    #+#             */
/*   Updated: 2020/11/22 13:48:40 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_LOADER_H
# define OBJ_LOADER_H

# include "mesh.h"

# define AXIS_X 0
# define AXIS_Y 1
# define AXIS_Z 2

t_mesh			*obj_load(const char *filename);

#endif
