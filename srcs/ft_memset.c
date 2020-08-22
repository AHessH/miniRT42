/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 11:54:30 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 14:53:47 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*ft_memset(void *buf, int ch, size_t count)
{
	unsigned char *str;

	str = (unsigned char *)buf;
	while (count > 0)
	{
		*str = (unsigned char)ch;
		str++;
		count--;
	}
	return (buf);
}
