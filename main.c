/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 09:45:18 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/22 15:28:41 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_extension(char *av, char *ext)
{
	if (ft_strlen(av) <= 3)
		return (0);
	if (!(av = ft_strrchr(av, '.')))
		return (0);
	while (*av && *ext)
	{
		if (*av++ != *ext++)
			return (0);
	}
	if (*av != '\0')
		return (0);
	return (1);
}

void		treatment(int ac, char **av)
{
	t_data	*img;
	t_mlx	*mlx;
	t_scene	*scene;

	scene = read_scene_from_file(ac, av);
	if (ac == 3 && ft_strncmp(av[2], "--save", 6) == 0)
		scene->save = 1;
	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		ft_perror();
	if (!(img = (t_data *)malloc(sizeof(t_data))))
		ft_perror();
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, scene->rx, scene->ry,
		"RayTracer by froxanne");
	img->img = mlx_new_image(mlx->mlx, scene->rx, scene->ry);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
								&img->line_length, &img->endian);
	scene->mlx = mlx;
	scene->img = img;
	win_control(scene);
	rendering(mlx, img, scene);
	if (!(scene->save))
		mlx_loop(mlx->mlx);
	free_all_scene(scene);
	exit(0);
}

int			main(int argc, char **argv)
{
	t_scene *zagl;

	zagl = NULL;
	if (argc == 1)
		error_exit("Not enough arguments\n", zagl);
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0)
		error_exit("Not good arguments\n", zagl);
	if (argc > 3)
		error_exit("Too much arguments\n", zagl);
	if (!(check_extension(argv[1], ".rt")))
		error_exit("Wrong file extension\n", zagl);
	treatment(argc, argv);
	return (0);
}
