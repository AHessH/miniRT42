/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emancipator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjeremia <jjeremia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 16:05:05 by jjeremia          #+#    #+#             */
/*   Updated: 2020/08/04 21:26:07 by jjeremia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		free_mass_str(char **mass)
{
	int i;

	i = 0;
	while (mass[i])
		free(mass[i++]);
	free(mass);
}

static void	free_cams(t_scene *scene, void *tmp)
{
	while (scene->count_cam--)
	{
		tmp = scene->cam;
		scene->cam = scene->cam->next;
		free(tmp);
	}
}

void		free_all_scene(t_scene *scene)
{
	void	*tmp;

	tmp = NULL;
	if (scene->amb)
		free(scene->amb);
	free_cams(scene, tmp);
	if (scene->obj_list)
		ft_lstclear(&scene->obj_list, free);
	if (scene->light_list)
		ft_lstclear(&scene->light_list, free);
	free(scene);
	exit(0);
}
