/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk_cy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 22:51:23 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:04:37 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		init_disk_cy(t_scene *scene, t_elem *clndr, double t, int done)
{
	t_elem	*disk;

	if (!(disk = ft_calloc(1, sizeof(t_elem))))
		error_exit("Fail to allocating memory\n", scene);
	disk->id = DISK;
	disk->point = v_add(clndr->point, v_mult(clndr->orient, t));
	disk->orient = clndr->orient;
	disk->diam = clndr->diam;
	disk->color = clndr->color;
	ft_lstadd_back(&scene->obj_list, ft_lstnew(disk));
	if (done)
		return (init_disk_cy(scene, clndr, (clndr->height / -2.f), 0));
	return (0);
}

void	disk_intersect(t_scene *scene, t_elem *disk, t_vec orig, t_vec dir)
{
	t_elem		plane;
	t_vec		p;
	t_vec		v;
	double		d2;

	plane.point = disk->point;
	plane.orient = disk->orient;
	pl_intersect(scene, &plane, orig, dir);
	if (isinf(scene->t))
		return ;
	p = v_add(v_mult(dir, scene->t), orig);
	v = v_sub(p, disk->point);
	d2 = v_dot(v, v);
	if (!disk->cache)
		disk->cache = powf(disk->diam / 2.f, 2.f);
	if (d2 > disk->cache)
		scene->t = INFINITY;
}
