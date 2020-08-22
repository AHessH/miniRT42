/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:58:02 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:01:16 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	magic(char *cur, char **n_line, char **line)
{
	char	*temp;

	*cur++ = '\0';
	temp = *n_line;
	if ((!(*line = ft_strdup(*n_line)))
			|| (!(*n_line = ft_strdup(cur))))
		return (-1);
	free(temp);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	static char	*n_line;
	char		*cur;

	if (!line || fd < 0 || (read(fd, buf, 0) < 0))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[ret] = '\0';
		if (!(n_line = ft_strjoin(n_line, buf)))
			return (-1);
		if ((cur = ft_strchr(n_line, '\n')))
			return (magic(cur, &n_line, line));
	}
	if (n_line && (cur = ft_strchr(n_line, '\n')))
		return (magic(cur, &n_line, line));
	if (n_line)
	{
		*line = n_line;
		n_line = NULL;
		return (0);
	}
	return ((!(*line = ft_strdup(""))) ? -1 : 0);
}
