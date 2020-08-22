/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_deep_scene_errors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:13:08 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:03:05 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_cam_errors(char **line, t_scene *scene)
{
	if (count_of_params(line) != 4)
		error_exit("Wrong count of camera parameters\n", scene);
	if (!(is_mass_of_float(line[1], scene))
		|| !(is_mass_of_float(line[2], scene)))
		error_exit("Wrong camera coord parameter\n", scene);
	if (!(ft_is_number(line[3])))
		error_exit("Wrong FOV camera parameter\n", scene);
}

static void	check_light_sp_errors(char **line, t_scene *scene)
{
	if (count_of_params(line) != 4)
		error_exit("Wrong count of light or sphere parameters\n", scene);
	if (!(is_mass_of_float(line[1], scene)))
		error_exit("Wrong light or sphere coord parameter\n", scene);
	if (!(param_is_pos_float(line[2])))
		error_exit("Wrong LB ratio or sphere diameter\n", scene);
	if (!(check_colors(line[3], scene)))
		error_exit("Wrong light or sphere color parameters\n", scene);
}

void		check_param_deep_scene_errors(char **line, t_scene *scene)
{
	char	**tmp;

	while (*line)
	{
		tmp = ft_split(*line, ' ');
		if (tmp[0] && ft_strncmp(tmp[0], "c", 1) == 0 && !(tmp[0][1]))
			check_cam_errors(tmp, scene);
		if (tmp[0] && ft_strncmp(tmp[0], "l", 1) == 0)
			check_light_sp_errors(tmp, scene);
		if (tmp[0] && ft_strncmp(tmp[0], "sp", 2) == 0)
			check_light_sp_errors(tmp, scene);
		check_shape_errors(tmp, scene);
		free_mass_str(tmp);
		line++;
	}
}
