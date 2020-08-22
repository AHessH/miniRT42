/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:53:37 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:06:14 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_plane_t(t_elem *plane, t_vec orig, t_vec dir)
{
	t_garbage	s;

	s.a = v_dot(v_sub(orig, plane->point), plane->orient);
	s.b = v_dot(dir, plane->orient);
	if (s.b == 0 || (s.a < 0 && s.b < 0) || (s.a > 0 && s.b > 0))
		return (INFINITY);
	s.t1 = -s.a / s.b;
	return (s.t1);
}

void	pl_intersect(t_scene *scene, t_elem *plane, t_vec orig, t_vec dir)
{
	float	t;

	t = get_plane_t(plane, orig, dir);
	if (t < 0 || scene->t < t)
		return ;
	scene->t = t;
}

int		plane_side(t_scene *scene, t_elem *light, t_vec p, t_vec n)
{
	t_elem	cam_plane;
	t_scene	sct;
	t_elem	light2;

	if (scene->obj->id == CYLINDER || scene->obj->id == SPHERE)
		return (1);
	sct.t = INFINITY;
	light2.orient = n;
	light2.point = light->point;
	pl_intersect(&sct, &light2, p, n);
	sct.k = sct.t;
	cam_plane.orient = n;
	cam_plane.point = scene->ray.orig;
	sct.t = INFINITY;
	pl_intersect(&sct, &cam_plane, p, n);
	if (sct.t == INFINITY && sct.k == INFINITY)
		return (-1);
	if (sct.t != INFINITY && sct.k != INFINITY)
		return (1);
	return (0);
}
