/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:49:14 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/22 15:28:47 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_atof(char *str)
{
	double	div;
	double	razr;
	int		num;
	int		sign;

	num = ft_atoi(str);
	sign = 1;
	while ((*str == '\t') || (*str == '\n') || (*str == ' ')
		|| (*str == '\f') || (*str == '\v') || (*str == '\r'))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	div = 0;
	razr = 1.0;
	if (*str++ == '.')
		while (*str && ft_isdigit(*str))
		{
			razr *= 0.1;
			div += sign * razr * (*str++ - '0');
		}
	return (num + div);
}
