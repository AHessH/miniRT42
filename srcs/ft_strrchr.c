/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 12:26:53 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:00:47 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_strrchr(const char *str, int ch)
{
	size_t	len;
	char	*rev;
	char	*ptr;

	ptr = (char *)str;
	len = 0;
	while (ptr[len])
		len++;
	rev = ptr + len;
	while (rev >= ptr)
	{
		if (*rev == (unsigned char)ch)
			return (rev);
		rev--;
	}
	if ((unsigned char)ch == '\0')
		return (ptr + len);
	return (NULL);
}
