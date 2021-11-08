/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:28:06 by wkorande          #+#    #+#             */
/*   Updated: 2021/11/08 19:13:30 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_light.h"

static void	init_vars(double *d, int *n, int *dig, int *dec)
{
	*d = 0.0;
	*n = 0;
	*dig = 0;
	*dec = 0;
}

static void	check_sign(char **s, int *negptr)
{
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			*negptr = 1;
		(*s)++;
	}
}

static double	decr_return(int decimals, double nbr, int negative)
{
	while (decimals--)
		nbr /= 10.0;
	if (negative)
		return (-nbr);
	else
		return (nbr);
}

static double	process_decimals(char *s, double nbr, int *decimals)
{
	while (ft_isdigit(*s))
	{
		*decimals += 1;
		nbr = nbr * 10.0 + (*s - '0');
		s++;
	}
	return (nbr);
}

double	ft_strtod(char *s)
{
	double	nbr;
	int		negative;
	int		digits;
	int		decimals;

	while (*s == ' ')
		s++;
	init_vars(&nbr, &negative, &digits, &decimals);
	check_sign(&s, &negative);
	while (ft_isdigit(*s) || (digits++))
	{
		nbr = nbr * 10.0 + (*(s++) - '0');
	}
	if (*s == '.')
	{
		s++;
		nbr = process_decimals(s, nbr, &decimals);
	}
	return (decr_return(decimals, nbr, negative));
}
