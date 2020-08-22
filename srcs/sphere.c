/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:49:00 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:07:21 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sp_intersect(t_scene *scene, t_elem *sphere, t_vec orig, t_vec dir)
{
	t_garbage	g;

	g.sub = v_sub(orig, sphere->point);
	g.a = v_dot(dir, dir);
	g.b = 2 * v_dot(dir, g.sub);
	g.c = v_dot(g.sub, g.sub) - powf(sphere->diam / 2, 2);
	g.discr = powf(g.b, 2) - (4 * g.a * g.c);
	if (g.discr < 0)
		return ;
	g.discr = sqrtf(g.discr);
	g.t1 = (-g.b - g.discr) / (2 * g.a);
	g.t2 = (-g.b + g.discr) / (2 * g.a);
	if (g.t1 > 1.f && scene->t > g.t1 && g.t1 < g.t2)
		scene->t = g.t1;
	if (g.t2 > 1.f && scene->t > g.t2 && g.t2 < g.t1)
		scene->t = g.t2;
}
