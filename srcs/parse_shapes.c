/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 00:16:40 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:05:29 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_new_sphere(t_scene *scene, char **temp)
{
	char	**temp_points;
	char	**temp_cols;
	t_elem	*sphere;

	if (!(sphere = (t_elem *)malloc(sizeof(t_elem))))
		ft_perror();
	temp_points = ft_split(temp[1], ',');
	temp_cols = ft_split(temp[3], ',');
	sphere->point.x = ft_atof(temp_points[0]);
	sphere->point.y = ft_atof(temp_points[1]);
	sphere->point.z = ft_atof(temp_points[2]);
	sphere->diam = ft_atof(temp[2]);
	sphere->color.r = (float)ft_atoi(temp_cols[0]) / 255.f;
	sphere->color.g = (float)ft_atoi(temp_cols[1]) / 255.f;
	sphere->color.b = (float)ft_atoi(temp_cols[2]) / 255.f;
	check_color(&sphere->color);
	sphere->id = SPHERE;
	sphere->cache = INFINITY;
	ft_lstadd_front(&scene->obj_list, ft_lstnew(sphere));
	free_mass_str(temp_points);
	free_mass_str(temp_cols);
}

void	init_new_plane(t_scene *scene, char **temp)
{
	char	**temp_points;
	char	**temp_vectors;
	char	**temp_cols;
	t_elem	*plane;

	if (!(plane = (t_elem *)malloc(sizeof(t_elem))))
		ft_perror();
	temp_points = ft_split(temp[1], ',');
	temp_vectors = ft_split(temp[2], ',');
	temp_cols = ft_split(temp[3], ',');
	plane->point = (t_vec){ft_atof(temp_points[0]), ft_atof(temp_points[1]),
							ft_atof(temp_points[2])};
	plane->orient = (t_vec){ft_atof(temp_vectors[0]), ft_atof(temp_vectors[1]),
							ft_atof(temp_vectors[2])};
	check_normal(&plane->orient, scene);
	plane->color = (t_color){(float)ft_atoi(temp_cols[0]) / 255.f,
	(float)ft_atoi(temp_cols[1]) / 255.f, (float)ft_atoi(temp_cols[2]) / 255.f};
	check_color(&plane->color);
	plane->id = PLANE;
	ft_lstadd_front(&scene->obj_list, ft_lstnew(plane));
	free_mass_str(temp_points);
	free_mass_str(temp_vectors);
	free_mass_str(temp_cols);
}

void	init_new_square(t_scene *scene, char **temp)
{
	char	**temp_points;
	char	**temp_vectors;
	char	**temp_cols;
	t_elem	*sqr;

	if (!(sqr = (t_elem *)malloc(sizeof(t_elem))))
		ft_perror();
	temp_points = ft_split(temp[1], ',');
	temp_vectors = ft_split(temp[2], ',');
	temp_cols = ft_split(temp[4], ',');
	sqr->point = (t_vec){ft_atof(temp_points[0]), ft_atof(temp_points[1]),
							ft_atof(temp_points[2])};
	sqr->orient = (t_vec){ft_atof(temp_vectors[0]), ft_atof(temp_vectors[1]),
							ft_atof(temp_vectors[2])};
	check_normal(&sqr->orient, scene);
	sqr->height = ft_atof(temp[3]);
	sqr->color = (t_color){(float)ft_atoi(temp_cols[0]) / 255.f,
	(float)ft_atoi(temp_cols[1]) / 255.f, (float)ft_atoi(temp_cols[2]) / 255.f};
	check_color(&sqr->color);
	sqr->id = SQUARE;
	ft_lstadd_front(&scene->obj_list, ft_lstnew(sqr));
	free_mass_str(temp_points);
	free_mass_str(temp_vectors);
	free_mass_str(temp_cols);
}

void	init_new_cylinder(t_scene *scene, char **temp)
{
	char	**temp_points;
	char	**temp_vectors;
	char	**temp_cols;
	t_elem	*clndr;

	if (!(clndr = (t_elem *)malloc(sizeof(t_elem))))
		ft_perror();
	temp_points = ft_split(temp[1], ',');
	temp_vectors = ft_split(temp[2], ',');
	temp_cols = ft_split(temp[5], ',');
	clndr->point = (t_vec){ft_atof(temp_points[0]), ft_atof(temp_points[1]),
							ft_atof(temp_points[2])};
	clndr->orient = (t_vec){ft_atof(temp_vectors[0]), ft_atof(temp_vectors[1]),
							ft_atof(temp_vectors[2])};
	clndr->diam = ft_atof(temp[3]);
	clndr->height = ft_atof(temp[4]);
	clndr->color = set_color(temp_cols);
	check_color(&clndr->color);
	clndr->id = CYLINDER;
	clndr->orient = v_norm(clndr->orient);
	init_disk_cy(scene, clndr, (clndr->height / 2.f), 1);
	ft_lstadd_front(&scene->obj_list, ft_lstnew(clndr));
	free_mass_str(temp_points);
	free_mass_str(temp_vectors);
	free_mass_str(temp_cols);
}

void	init_new_triangle(t_scene *scene, char **temp)
{
	char	**temp_points;
	char	**temp_cols;
	t_elem	*trngl;

	if (!(trngl = (t_elem *)malloc(sizeof(t_elem))))
		ft_perror();
	temp_points = ft_split(temp[1], ',');
	trngl->point = (t_vec){ft_atof(temp_points[0]), ft_atof(temp_points[1]),
							ft_atof(temp_points[2])};
	free_mass_str(temp_points);
	temp_points = ft_split(temp[2], ',');
	trngl->point2 = (t_vec){ft_atof(temp_points[0]), ft_atof(temp_points[1]),
							ft_atof(temp_points[2])};
	free_mass_str(temp_points);
	temp_points = ft_split(temp[3], ',');
	trngl->point3 = (t_vec){ft_atof(temp_points[0]), ft_atof(temp_points[1]),
							ft_atof(temp_points[2])};
	temp_cols = ft_split(temp[4], ',');
	trngl->color = (t_color){(float)ft_atoi(temp_cols[0]) / 255.f,
	(float)ft_atoi(temp_cols[1]) / 255.f, (float)ft_atoi(temp_cols[2]) / 255.f};
	check_color(&trngl->color);
	trngl->id = TRIANGLE;
	ft_lstadd_front(&scene->obj_list, ft_lstnew(trngl));
	free_mass_str(temp_points);
	free_mass_str(temp_cols);
}
