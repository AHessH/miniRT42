/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 14:53:24 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:04:59 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(char *error, t_scene *scene)
{
	write(1, "Error\n", 6);
	while (*error)
	{
		write(1, error, 1);
		error++;
	}
	if (scene)
		free_all_scene(scene);
	exit(1);
}

void	ft_perror(void)
{
	perror("Error\n");
	exit(1);
}
