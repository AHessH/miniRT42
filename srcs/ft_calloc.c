/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:50:05 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 14:51:00 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		*ft_calloc(size_t num, size_t size)
{
	unsigned char	*p;

	if (!(p = (unsigned char *)malloc(size * num)))
		return (NULL);
	ft_memset(p, 0, num * size);
	return ((void *)p);
}
