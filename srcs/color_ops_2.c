/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 14:22:48 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:04:09 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_intens(float intens, t_color color)
{
	if (intens > 1)
		return (color);
	color.r = color.r * intens;
	color.g = color.g * intens;
	color.b = color.b * intens;
	return (color);
}

int		color_to_int(t_color *color)
{
	int	out_color;

	*color = (t_color){color->r * 255, color->g * 255, color->b * 255};
	out_color = 0;
	out_color |= (int)color->r << 16;
	out_color |= (int)color->g << 8;
	out_color |= (int)color->b;
	return (out_color);
}
