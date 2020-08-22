/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 14:49:42 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 14:49:47 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int			sign;
	int			result;
	int			i;
	int			k;

	sign = 0;
	i = 0;
	result = 0;
	k = 0;
	while ((str[i] == '\t') || (str[i] == '\n') || (str[i] == ' ')
		|| (str[i] == '\f') || (str[i] == '\v') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		sign = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		k++;
		if (k >= 21)
			return (-1 * (result > 0) + sign);
		result = (result * 10) + (str[i++] - '0');
	}
	return (sign ? (result * -1) : result);
}
