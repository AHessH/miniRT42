/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 09:45:53 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 14:59:38 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*ft_strdup(char *str)
{
	char	*cp;
	char	*p_cp;

	if (!str)
		return (NULL);
	if (!(cp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	p_cp = cp;
	while (*str)
		*cp++ = *str++;
	*cp = '\0';
	return (p_cp);
}
