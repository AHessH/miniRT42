/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:28:30 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:07:36 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sq_intersect(t_scene *scene, t_elem *square, t_vec orig, t_vec dir)
{
	double	t;
	t_vec	d;

	t = get_plane_t(square, orig, dir);
	d = v_sub(v_add(v_mult(dir, t), orig), square->point);
	square->cache = 0;
	if (!square->cache)
		square->cache = square->height / 2;
	if (t <= 0 || fabs(d.x) > square->cache || fabs(d.y) > square->cache
	|| fabs(d.z) > square->cache)
		return ;
	scene->t = t;
}
