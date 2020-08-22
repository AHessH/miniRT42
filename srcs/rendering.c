/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 11:47:59 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/22 15:27:05 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	calc_light(t_scene *scene)
{
	t_vec		normal;
	t_color		color;

	color = color_mult(scene->color,
		color_intens(scene->amb->ambl_ratio, scene->amb->color));
	normal = get_normal(scene, scene->vec_p);
	color = get_color(scene, scene->vec_p, normal, color);
	return (color);
}

void			identify_obj(t_scene *scene, t_elem *obj, t_vec orig, t_vec dir)
{
	if (obj->id == SPHERE)
		sp_intersect(scene, obj, orig, dir);
	else if (obj->id == PLANE)
		pl_intersect(scene, obj, orig, dir);
	else if (obj->id == CYLINDER)
		cy_intersect(scene, obj, orig, dir);
	else if (obj->id == DISK)
		disk_intersect(scene, obj, orig, dir);
	else if (obj->id == TRIANGLE)
		tr_intersect(scene, obj, orig, dir);
	else if (obj->id == SQUARE)
		sq_intersect(scene, obj, orig, dir);
}

static t_color	trace_ray(t_scene *scene)
{
	t_list	*tmp;

	scene->t = INFINITY;
	scene->k = INFINITY;
	scene->obj = NULL;
	tmp = scene->obj_list;
	scene->color = (t_color){0, 0, 0};
	while (tmp)
	{
		identify_obj(scene, tmp->content, scene->ray.orig, scene->ray.dir);
		if (scene->t > 0 && scene->t < scene->k && (scene->k = scene->t))
			scene->obj = tmp->content;
		tmp = tmp->next;
	}
	if (scene->obj)
	{
		scene->vec_p = v_add(scene->ray.orig, v_mult(scene->ray.dir, scene->k));
		scene->color = scene->obj->color;
		scene->color = calc_light(scene);
	}
	return (scene->color);
}

static t_vec	build_ray(t_scene *scene, float x, float y)
{
	float	n_x;
	float	n_y;
	t_vec	dir;
	t_vec	ip;
	t_vec	temp;

	n_x = ((x / (float)scene->rx) - 0.5) * scene->cam->k_fov;
	n_y = ((y / (float)scene->ry) - 0.5) * scene->cam->k_fov *
			(float)scene->ry / (float)scene->rx;
	ip = v_mult(scene->cam->right, n_x);
	temp = v_mult(scene->cam->up, n_y);
	ip = v_add(ip, temp);
	ip = v_add(ip, scene->ray.orig);
	ip = v_add(ip, v_norm(scene->cam->normal));
	dir = v_norm(v_sub(ip, scene->ray.orig));
	return (dir);
}

void			rendering(t_mlx *mlx, t_data *img, t_scene *scene)
{
	int		x;
	int		y;

	scene->ray.orig = (t_vec){scene->cam->coord.x, scene->cam->coord.y,
								scene->cam->coord.z};
	scene->cam->up = (t_vec){0, -1.0, 0};
	check_normal(&scene->cam->normal, scene);
	scene->cam->right = v_cross(v_norm(scene->cam->normal), scene->cam->up);
	scene->cam->up = v_cross(scene->cam->right, v_norm(scene->cam->normal));
	y = -1;
	while (++y <= scene->ry)
	{
		x = -1;
		while (++x <= scene->rx)
		{
			scene->ray.dir = build_ray(scene, x, y);
			scene->color = trace_ray(scene);
			((int*)img->addr)[y * scene->rx + x] = color_to_int(&scene->color);
		}
	}
	if (scene->save)
		save_bmp(scene, BMP_NAME);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->win, img->img, 0, 0);
}
