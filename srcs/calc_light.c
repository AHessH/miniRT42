/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:47:23 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/22 18:19:42 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_normal(t_scene *scene, t_vec p)
{
	t_vec		normal;

	if (scene->obj->id == PLANE || scene->obj->id == SQUARE
		|| scene->obj->id == TRIANGLE || scene->obj->id == DISK)
		normal = scene->obj->orient;
	else if (scene->obj->id == CYLINDER)
		normal = get_clndr_normal(scene->obj, p);
	else
		normal = v_norm(v_sub(p, scene->obj->point));
	return (normal);
}

t_elem	*elem_cpy(t_elem *elem)
{
	t_elem	*new_elem;

	if (!(new_elem = ft_calloc(1, sizeof(t_elem))))
		return (NULL);
	ft_memcpy(new_elem, elem, sizeof(t_elem));
	return (new_elem);
}

t_vec	get_light_vec(t_elem *light, t_vec p)
{
	t_vec	l;

	l = v_norm(v_sub(light->point, p));
	light->orient = l;
	return (l);
}

float	light_intersect(t_scene *scene, double dot, t_vec p, t_elem *light)
{
	t_list		*tmp2;
	t_scene		s;

	ft_memcpy(&s, scene, sizeof(t_scene));
	tmp2 = s.obj_list;
	s.t = INFINITY;
	s.k = INFINITY;
	while (tmp2)
	{
		identify_obj(&s, tmp2->content, light->point,
					v_norm(v_sub(p, light->point)));
		if (s.t > 0 && s.t < s.k && (s.k = s.t))
			s.obj = tmp2->content;
		tmp2 = tmp2->next;
	}
	if (dot > 0 && s.obj != scene->obj)
		dot = -1;
	return (dot);
}

t_color	get_color(t_scene *scene, t_vec p, t_vec n, t_color color)
{
	float		dot;
	t_vec		l;
	t_list		*tmp;
	t_elem		*light;

	tmp = scene->light_list;
	while (tmp)
	{
		if (!(light = elem_cpy(tmp->content)))
			free_all_scene(scene);
		l = get_light_vec(light, p);
		dot = v_dot(n, l) * plane_side(scene, light, scene->obj->point, n);
		dot = light_intersect(scene, dot, p, light);
		if (dot <= 0 || calc_shadows(scene, p, l, light))
		{
			tmp = tmp->next;
			free(light);
			continue;
		}
		color = color_add(color, color_mult(scene->color,
				color_intens(light->ratio * dot, light->color)));
		tmp = tmp->next;
		free(light);
	}
	return (color);
}
