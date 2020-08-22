/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjeremia <jjeremia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 15:48:27 by jjeremia          #+#    #+#             */
/*   Updated: 2020/08/04 20:19:42 by jjeremia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_colors(char *line, t_scene *scene)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(line, ',');
	if (count_of_params(tmp) != 3)
	{
		free_mass_str(tmp);
		error_exit("Wrong count of color parameters\n", scene);
	}
	while (tmp[i])
	{
		if (!(ft_is_number(tmp[i])))
		{
			free_mass_str(tmp);
			return (0);
		}
		i++;
	}
	free_mass_str(tmp);
	return (1);
}
