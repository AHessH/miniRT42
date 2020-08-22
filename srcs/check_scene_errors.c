/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 22:41:53 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:03:24 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			count_of_params(char **line)
{
	int	count;

	count = 0;
	while (line[count])
		count++;
	return (count);
}

static void	check_param_res_amb_errors(char **line, t_scene *scene)
{
	char	**tmp;

	while (*line)
	{
		tmp = ft_split(*line, ' ');
		if (tmp[0] && ft_strncmp(tmp[0], "R", 1) == 0)
		{
			if (count_of_params(tmp) != 3)
				error_exit("Wrong count of resolution parameters\n", scene);
			if (!(ft_is_number(tmp[1])) || !(ft_is_number(tmp[2])))
				error_exit("Wrong resolution parameter\n", scene);
		}
		if (tmp[0] && ft_strncmp(tmp[0], "A", 1) == 0)
		{
			if (count_of_params(tmp) != 3)
				error_exit("Wrong count of ambient parameters\n", scene);
			if (!(param_is_pos_float(tmp[1])))
				error_exit("Wrong ambient lighting ratio parameter\n", scene);
			if (!(check_colors(tmp[2], scene)))
				error_exit("Wrong ambient color parameters\n", scene);
		}
		free_mass_str(tmp);
		line++;
	}
}

static int	find_param(char **line, char *param)
{
	size_t	len;

	while (*line)
	{
		len = 0;
		while (line[0][len] != ' ' && line[0][len] == param[len])
			len++;
		if (ft_strlen(param) == len && line[0][len] == ' ')
			return (1);
		line++;
	}
	return (0);
}

void		check_scene_errors(char **line, t_scene *scene)
{
	int	shape;

	if (!(find_param(line, "R")))
		error_exit("Parameter 'Resolution' is missed\n", scene);
	if (!(find_param(line, "A")))
		error_exit("Parameter 'Ambient lighting' is missed\n", scene);
	if (!(find_param(line, "c")))
		error_exit("Parameter 'Camera' is missed\n", scene);
	if (!(find_param(line, "l")))
		error_exit("Parameter 'Light source' is missed\n", scene);
	shape = 0;
	shape += find_param(line, "sp");
	shape += find_param(line, "pl");
	shape += find_param(line, "sq");
	shape += find_param(line, "cy");
	shape += find_param(line, "tr");
	if (shape == 0)
		error_exit("Scene must contain at least one shape\n", scene);
	check_param_res_amb_errors(line, scene);
	check_param_deep_scene_errors(line, scene);
}
