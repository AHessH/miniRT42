/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shape_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 18:52:10 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:03:40 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_plane_errors(char **line, t_scene *scene)
{
	if (count_of_params(line) != 4)
		error_exit("Wrong count of plane parameters\n", scene);
	if (!(is_mass_of_float(line[1], scene))
		|| !(is_mass_of_float(line[2], scene)))
		error_exit("Wrong plane coord parameter\n", scene);
	if (!(check_colors(line[3], scene)))
		error_exit("Wrong plane color parameters\n", scene);
}

static void	check_sqr_errors(char **line, t_scene *scene)
{
	if (count_of_params(line) != 5)
		error_exit("Wrong count of square parameters\n", scene);
	if (!(is_mass_of_float(line[1], scene))
		|| !(is_mass_of_float(line[2], scene)))
		error_exit("Wrong square coord parameter\n", scene);
	if (!(param_is_pos_float(line[3])))
		error_exit("Wrong square side size\n", scene);
	if (!(check_colors(line[4], scene)))
		error_exit("Wrong square color parameters\n", scene);
}

static void	check_clndr_errors(char **line, t_scene *scene)
{
	if (count_of_params(line) != 6)
		error_exit("Wrong count of cylinder parameters\n", scene);
	if (!(is_mass_of_float(line[1], scene))
		|| !(is_mass_of_float(line[2], scene)))
		error_exit("Wrong cylinder coord parameter\n", scene);
	if (!(param_is_pos_float(line[3])))
		error_exit("Wrong cylinder diameter\n", scene);
	if (!(param_is_pos_float(line[4])))
		error_exit("Wrong cylinder height\n", scene);
	if (!(check_colors(line[5], scene)))
		error_exit("Wrong cylinder color parameters\n", scene);
}

static void	check_trngl_errors(char **line, t_scene *scene)
{
	if (count_of_params(line) != 5)
		error_exit("Wrong count of triangle parameters\n", scene);
	if (!(is_mass_of_float(line[1], scene)) ||
		!(is_mass_of_float(line[2], scene)) ||
		!(is_mass_of_float(line[3], scene)))
		error_exit("Wrong triangle coord parameter\n", scene);
	if (!(check_colors(line[4], scene)))
		error_exit("Wrong triangle color parameters\n", scene);
}

void		check_shape_errors(char **tmp, t_scene *scene)
{
	if (tmp[0] && ft_strncmp(tmp[0], "pl", 2) == 0)
		check_plane_errors(tmp, scene);
	if (tmp[0] && ft_strncmp(tmp[0], "sq", 2) == 0)
		check_sqr_errors(tmp, scene);
	if (tmp[0] && ft_strncmp(tmp[0], "cy", 2) == 0)
		check_clndr_errors(tmp, scene);
	if (tmp[0] && ft_strncmp(tmp[0], "tr", 2) == 0)
		check_trngl_errors(tmp, scene);
}
