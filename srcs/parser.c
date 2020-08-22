/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 12:23:36 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:05:57 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	*init_new_light(t_scene *scene, char **temp)
{
	char	**temp_points;
	char	**temp_colors;
	t_elem	*light;

	if (!(light = (t_elem *)malloc(sizeof(t_elem))))
		ft_perror();
	temp_points = ft_split(temp[1], ',');
	temp_colors = ft_split(temp[3], ',');
	light->point.x = ft_atof(temp_points[0]);
	light->point.y = ft_atof(temp_points[1]);
	light->point.z = ft_atof(temp_points[2]);
	light->ratio = ft_atof(temp[2]);
	light->color.r = (float)ft_atoi(temp_colors[0]) / 255.f;
	light->color.g = (float)ft_atoi(temp_colors[1]) / 255.f;
	light->color.b = (float)ft_atoi(temp_colors[2]) / 255.f;
	scene->count_light++;
	ft_lstadd_front(&scene->light_list, ft_lstnew(light));
	free_mass_str(temp_points);
	free_mass_str(temp_colors);
	return (light);
}

static void	parse_res_amb_cam(t_scene *scene, char **line)
{
	parse_res(scene, line);
	parse_amb(scene, line);
	parse_cams(scene, line);
}

void		parse_scene(t_scene *scene, char **line)
{
	char		**temp;

	parse_res_amb_cam(scene, line);
	while (*line)
	{
		temp = ft_split(*line, ' ');
		if (ft_strncmp(*line, "sp", 2) == 0)
			init_new_sphere(scene, temp);
		else if (ft_strncmp(*line, "pl", 2) == 0)
			init_new_plane(scene, temp);
		else if (ft_strncmp(*line, "sq", 2) == 0)
			init_new_square(scene, temp);
		else if (ft_strncmp(*line, "cy", 2) == 0)
			init_new_cylinder(scene, temp);
		else if (ft_strncmp(*line, "tr", 2) == 0)
			init_new_triangle(scene, temp);
		else if (ft_strncmp(*line, "l ", 2) == 0)
			init_new_light(scene, temp);
		free_mass_str(temp);
		line++;
	}
}
