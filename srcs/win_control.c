/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 09:56:42 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:08:41 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	change_cam(int key, t_scene *scene)
{
	if (key == 97)
	{
		write(1, "prev cam\n", 10);
		scene->cam = scene->cam->prev;
		rendering(scene->mlx, scene->img, scene);
	}
	if (key == 100)
	{
		write(1, "next cam\n", 10);
		scene->cam = scene->cam->next;
		rendering(scene->mlx, scene->img, scene);
	}
}

static int	key_win(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (key == 100 || key == 97)
		change_cam(key, scene);
	if (key == 65307)
	{
		write(1, "Bye\n", 4);
		exit(0);
	}
	return (0);
}

static int	press_x(void)
{
	write(1, "Bye\n", 4);
	exit(0);
}

void		win_control(t_scene *scene)
{
	mlx_hook(scene->mlx->win, 2, 1L << 0, key_win, scene);
	mlx_hook(scene->mlx->win, 17, 1L << 17, press_x, scene->mlx);
}
