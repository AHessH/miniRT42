/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:42:47 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:07:02 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	bmp_file_header(t_scene *scene, int padding_size, int fd)
{
	unsigned char	*file_header;
	int				file_size;
	unsigned		*ptr;

	if (!(file_header = ft_calloc(BMP_FILE_HEADER, sizeof(unsigned char))))
		ft_perror();
	file_size = BMP_FILE_HEADER + BMP_INFO_HEADER +
				(scene->img->bits_per_pixel / 8 * scene->rx + padding_size) *
				scene->ry;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	ptr = (unsigned *)(file_header + 2);
	*ptr = file_size;
	file_header[10] = (unsigned char)(BMP_FILE_HEADER + BMP_INFO_HEADER);
	write(fd, file_header, BMP_FILE_HEADER);
	free(file_header);
}

static void	bmp_info_header(t_scene *scene, int fd)
{
	unsigned char	*info_header;
	unsigned		*ptr;

	if (!(info_header = ft_calloc(BMP_INFO_HEADER, sizeof(unsigned char))))
		ft_perror();
	info_header[0] = (unsigned char)(BMP_INFO_HEADER);
	ptr = (unsigned *)(info_header + 4);
	*ptr = scene->rx;
	ptr = (unsigned *)(info_header + 8);
	*ptr = scene->ry;
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(scene->img->bits_per_pixel);
	write(fd, info_header, BMP_INFO_HEADER);
	free(info_header);
}

void		save_bmp(t_scene *scene, char *file_name)
{
	int				i;
	int				fd;
	int				padding_size;
	unsigned char	padding[3];

	i = scene->ry;
	ft_memset(padding, 0, 3);
	if (!(fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		ft_perror();
	padding_size = (4 - (scene->rx * scene->img->bits_per_pixel / 8) % 4) % 4;
	bmp_file_header(scene, padding_size, fd);
	bmp_info_header(scene, fd);
	while (i >= 0)
	{
		write(fd, scene->img->addr + (i * scene->rx
				* scene->img->bits_per_pixel / 8), scene->img->line_length);
		write(fd, padding, padding_size);
		i--;
	}
	close(fd);
	free_all_scene(scene);
}
