/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:34:30 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:07:53 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	tr_intersect(t_scene *scene, t_elem *trngl, t_vec orig, t_vec dir)
{
	t_garbage	s;
	t_vec		tvec;
	t_vec		pvec;

	trngl->orient = v_norm(v_cross(v_sub(trngl->point2,
					trngl->point), v_sub(trngl->point3, trngl->point)));
	trngl->cache_vec1 = v_sub(trngl->point2, trngl->point);
	trngl->cache_vec2 = v_sub(trngl->point3, trngl->point);
	pvec = v_cross(dir, trngl->cache_vec2);
	s.discr = v_dot(trngl->cache_vec1, pvec);
	if (fabs(s.discr) < 0.00000001)
		return ;
	s.c = 1 / s.discr;
	tvec = v_sub(orig, trngl->point);
	s.a = v_dot(tvec, pvec) * s.c;
	if (s.a < 0 || s.a > 1)
		return ;
	tvec = v_cross(tvec, trngl->cache_vec1);
	s.b = v_dot(dir, tvec) * s.c;
	if (s.b < 0 || s.a + s.b > 1)
		return ;
	scene->t = v_dot(trngl->cache_vec2, tvec) * s.c;
}
