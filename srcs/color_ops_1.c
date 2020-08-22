/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ops_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 19:13:48 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:03:55 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_color(t_color *color)
{
	if (color->r < 0 || color->r > 1)
		color->r = 1;
	if (color->g < 0 || color->g > 1)
		color->g = 1;
	if (color->b < 0 || color->b > 1)
		color->b = 1;
}

t_color	color_mult(t_color color1, t_color color2)
{
	t_color		color;

	color.r = color1.r * color2.r;
	color.g = color1.g * color2.g;
	color.b = color1.b * color2.b;
	return (color);
}

t_color	color_div(t_color color, float av)
{
	t_color	c;

	c.r = color.r / av;
	c.g = color.g / av;
	c.b = color.b / av;
	return (c);
}

t_color	color_add(t_color color1, t_color color2)
{
	t_color		color;

	color.r = color1.r + color2.r;
	color.r > 1 ? color.r = 1 : 0;
	color.g = color1.g + color2.g;
	color.g > 1 ? color.g = 1 : 0;
	color.b = color1.b + color2.b;
	color.b > 1 ? color.b = 1 : 0;
	return (color);
}

t_color	set_color(char **temp_cols)
{
	return ((t_color){(float)ft_atoi(temp_cols[0]) / 255.f,
					(float)ft_atoi(temp_cols[1]) / 255.f,
					(float)ft_atoi(temp_cols[2]) / 255.f});
}
