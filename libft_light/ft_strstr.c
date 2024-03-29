/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:43:37 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 18:22:24 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	c1;
	int	c2;

	if (!*needle)
		return ((char *)haystack);
	c1 = 0;
	while (haystack[c1] != '\0')
	{
		if (haystack[c1] == needle[0])
		{
			c2 = 0;
			while (haystack[c1 + c2] == needle[c2] && needle[c2] != '\0')
			{
				if (needle[c2 + 1] == '\0')
				{
					haystack += c1;
					return ((char *)haystack);
				}
				c2++;
			}
		}
		c1++;
	}
	return (0);
}
