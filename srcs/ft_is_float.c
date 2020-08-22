/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:32:20 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 14:51:49 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	param_is_pos_float(char *line)
{
	int	point;

	point = 0;
	while (*line)
	{
		if (*line == '.' && !point)
		{
			point = 1;
			line++;
		}
		else if (!(ft_isdigit(*line++)))
			return (0);
	}
	return (1);
}

int	param_is_float(char *line)
{
	int	point;

	point = 0;
	if (*line == '-')
		line++;
	while (*line)
	{
		if (*line == '.' && !point)
		{
			point = 1;
			line++;
		}
		else if (!(ft_isdigit(*line++)))
			return (0);
	}
	return (1);
}

int	is_mass_of_float(char *line, t_scene *scene)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(line, ',');
	if (count_of_params(tmp) != 3)
	{
		free_mass_str(tmp);
		error_exit("Wrong count of coord parameters\n", scene);
	}
	while (tmp[i])
	{
		if (!(param_is_float(tmp[i])))
		{
			free_mass_str(tmp);
			return (0);
		}
		i++;
	}
	free_mass_str(tmp);
	return (1);
}
