/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_vec3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:15:48 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 17:36:53 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "libft_light.h"

t_vec3	ft_parse_vec3(char *str)
{
	t_vec3	v;
	char	*token;

	str = ft_strstr(str, " ");
	token = ft_strtok(str, " ");
	if ((!token) && (!(v.x = 0)))
		ft_putendl("Couldn't parse vector3 x, set to 0");
	else
		v.x = (float)ft_strtod(token);
	token = ft_strtok(NULL, " ");
	if ((!token) && (!(v.y = 0)))
		ft_putendl("Couldn't parse vector3 y, set to 0");
	else
		v.y = (float)ft_strtod(token);
	token = ft_strtok(NULL, " ");
	if ((!token) && (!(v.z = 0)))
		ft_putendl("Couldn't parse vector3 z, set to 0");
	else
		v.z = (float)ft_strtod(token);
	return (v);
}
