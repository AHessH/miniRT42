/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 09:44:26 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 14:59:54 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*ft_strjoin(char *s1, char *s2)
{
	char		*str;
	char		*p_str;
	size_t		len1;
	size_t		len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(str = (char *)(malloc(sizeof(char) * len1 + len2 + 1))))
		return (NULL);
	p_str = str;
	while (*s1)
		*str++ = *s1++;
	free(s1 - len1);
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (p_str);
}
