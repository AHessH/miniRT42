/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:56:50 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:02:45 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		calc_shadows(t_scene *scene, t_vec orig, t_vec dir, t_elem *light)
{
	t_list		*tmp;
	t_elem		*obj;

	tmp = scene->obj_list;
	scene->t = INFINITY;
	pl_intersect(scene, light, orig, dir);
	scene->k = scene->t - 0.01;
	while (tmp)
	{
		obj = tmp->content;
		if (scene->obj == obj)
		{
			scene->obj->id == CYLINDER ? tmp = tmp->next->next : 0;
			tmp = tmp->next;
			continue ;
		}
		identify_obj(scene, tmp->content, orig, dir);
		if (scene->t > 0 && scene->t < scene->k)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
