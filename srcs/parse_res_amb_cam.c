/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_res_amb_cam.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 20:16:49 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:05:13 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			parse_res(t_scene *scene, char **line)
{
	char	**temp;

	while (**line != 'R')
		line++;
	temp = ft_split(*line, ' ');
	scene->rx = ft_atoi(temp[1]);
	scene->ry = ft_atoi(temp[2]);
	scene->rx = scene->rx > 1920 ? 1920 : scene->rx;
	scene->ry = scene->ry > 1080 ? 1080 : scene->ry;
	free_mass_str(temp);
}

void			parse_amb(t_scene *scene, char **line)
{
	char	**temp;
	char	**temp_color;
	t_amb	*amb;

	while (**line != 'A')
		line++;
	if (!(amb = (t_amb *)malloc(sizeof(t_amb))))
		ft_perror();
	temp = ft_split(*line, ' ');
	amb->ambl_ratio = ft_atof(temp[1]);
	if (amb->ambl_ratio < 0.f || amb->ambl_ratio > 1.f)
		error_exit("Wrong ambient lighting ratio parameter\n", scene);
	temp_color = ft_split(temp[2], ',');
	amb->color.r = (float)ft_atoi(temp_color[0]) / 255.f;
	amb->color.g = (float)ft_atoi(temp_color[1]) / 255.f;
	amb->color.b = (float)ft_atoi(temp_color[2]) / 255.f;
	amb->k_color = color_intens(amb->ambl_ratio, amb->color);
	scene->amb = amb;
	free_mass_str(temp);
	free_mass_str(temp_color);
}

static t_cam	*init_new_cam(t_cam *cam, char **temp, t_scene *scene)
{
	char	**temp_coords;
	char	**temp_vectors;

	if (!(cam = (t_cam *)malloc(sizeof(t_cam))))
		ft_perror();
	temp_coords = ft_split(temp[1], ',');
	temp_vectors = ft_split(temp[2], ',');
	cam->serial = scene->count_cam;
	cam->coord.x = ft_atof(temp_coords[0]);
	cam->coord.y = ft_atof(temp_coords[1]);
	cam->coord.z = ft_atof(temp_coords[2]);
	cam->normal.x = ft_atof(temp_vectors[0]);
	cam->normal.y = ft_atof(temp_vectors[1]);
	cam->normal.z = ft_atof(temp_vectors[2]);
	cam->fov = ft_atoi(temp[3]);
	if (cam->fov > 180)
		error_exit("Wrong FOV camera parameter\n", scene);
	cam->k_fov = 2 * tan(cam->fov * M_PI / 360);
	cam->next = cam;
	cam->prev = cam;
	free_mass_str(temp_coords);
	free_mass_str(temp_vectors);
	return (cam);
}

static t_cam	*add_new_cam(t_cam *cam, char **temp, t_scene *scene)
{
	t_cam	*new;
	t_cam	*tmp;

	new = NULL;
	new = init_new_cam(new, temp, scene);
	tmp = cam->next;
	cam->next = new;
	new->next = tmp;
	new->prev = cam;
	if (tmp != NULL)
		tmp->prev = new;
	return (new);
}

void			parse_cams(t_scene *scene, char **line)
{
	char	**temp;
	t_cam	*cam;

	scene->count_cam = 0;
	while (*line)
	{
		if (ft_strncmp(*line, "c ", 2) == 0)
		{
			scene->count_cam++;
			temp = ft_split(*line, ' ');
			if (scene->count_cam == 1)
				cam = init_new_cam(cam, temp, scene);
			else if (scene->count_cam > 1)
				cam = add_new_cam(cam, temp, scene);
			free_mass_str(temp);
		}
		line++;
	}
	scene->cam = cam->next;
}
