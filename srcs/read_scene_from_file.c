/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_from_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 10:42:56 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:06:28 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		count_lines(char *av)
{
	int		count;
	int		fd;
	char	buf[1];

	if ((fd = open(av, O_RDWR)) == -1)
		ft_perror();
	count = 1;
	while (read(fd, buf, 1))
	{
		if (ft_strchr(buf, '\n'))
			count++;
	}
	close(fd);
	return (count);
}

static char		**make_mass(int fd, int size, t_scene *scene)
{
	int		count;
	char	**mass;
	int		res;

	if (!(mass = (char **)malloc(sizeof(char *) * (size + 1))))
		ft_perror();
	count = 0;
	while ((res = get_next_line(fd, &mass[count++])))
	{
		if (res == -1)
			error_exit("Сould not read the scene successfully\n", scene);
	}
	mass[count] = 0;
	return (mass);
}

static t_scene	*init_new_scene(int ac, char **av)
{
	t_scene	*scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		ft_perror();
	scene->save = ((ac == 3 && ft_strncmp(av[2], "--save", 6) == 0) ? 1 : 0);
	scene->obj_list = NULL;
	scene->light_list = NULL;
	return (scene);
}

t_scene			*read_scene_from_file(int ac, char **av)
{
	int		fd;
	char	**line;
	int		count;
	t_scene	*scene;

	if ((fd = open(av[1], O_RDWR)) == -1)
		ft_perror();
	scene = init_new_scene(ac, av);
	count = count_lines(av[1]);
	line = make_mass(fd, count, scene);
	close(fd);
	check_scene_errors(line, scene);
	parse_scene(scene, line);
	free_mass_str(line);
	return (scene);
}
