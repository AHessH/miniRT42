/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:31:20 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:04:25 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec			get_clndr_normal(t_elem *clndr, t_vec p)
{
	t_vec	v;

	v = v_sub(p, clndr->point);
	v = v_sub(v, v_proj(v, clndr->orient));
	return (v_norm(v));
}

int				discriminant(t_garbage *s)
{
	s->discr = pow(s->b, 2) - (4 * s->a * s->c);
	if (s->discr < 0)
		return (1);
	s->discr = sqrt(s->discr);
	s->a = 2 * s->a;
	s->t1 = (-s->b - s->discr) / s->a;
	s->t2 = (-s->b + s->discr) / s->a;
	return (0);
}

static	void	cy_next(t_scene *scene, t_elem *clndr, t_garbage s,
					t_scene temp)
{
	t_elem		plane;
	t_vec		inter;
	double		t;

	t = INFINITY;
	if (s.t1 >= 0 && scene->t > s.t1)
		t = s.t1;
	else if (s.t2 >= 0 && scene->t > s.t2)
		t = s.t2;
	if (t == INFINITY)
		return ;
	inter = v_add(temp.ray.orig, v_mult(temp.ray.dir, t));
	plane.orient = clndr->orient;
	plane.point = clndr->point;
	temp.t = INFINITY;
	pl_intersect(&temp, &plane, inter, clndr->orient);
	temp.t <= clndr->height / 2 ? scene->t = t : 0;
	pl_intersect(&temp, &plane, inter, v_mult(clndr->orient, -1));
	temp.t <= clndr->height / 2 ? scene->t = t : 0;
}

void			cy_intersect(t_scene *scene, t_elem *clndr, t_vec orig,
							t_vec dir)
{
	t_garbage	s;
	t_scene		temp;
	t_vec		cross2;

	clndr->cache = 0;
	temp.ray.orig = orig;
	temp.ray.dir = dir;
	s.cross = v_cross(temp.ray.dir, clndr->orient);
	s.sub = v_sub(temp.ray.orig, clndr->point);
	cross2 = v_cross(s.sub, clndr->orient);
	s.a = v_dot(s.cross, s.cross);
	s.b = 2 * v_dot(s.cross, cross2);
	if (!clndr->cache)
		clndr->cache = powf(clndr->diam / 2.f, 2.f) * v_dot(clndr->orient,
															clndr->orient);
	s.c = v_dot(cross2, cross2) - clndr->cache;
	if (discriminant(&s))
		return ;
	cy_next(scene, clndr, s, temp);
}
