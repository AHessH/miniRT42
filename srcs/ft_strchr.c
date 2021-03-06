/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 09:46:51 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 14:59:18 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		*ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	return (0);
}
