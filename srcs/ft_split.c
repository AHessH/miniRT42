/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:45:41 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 14:58:59 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		count_word(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (!s || *s == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != c)
			words++;
		while (s[i] != c && s[i + 1])
			i++;
		i++;
	}
	return (words);
}

static int		len_word(char const *s, int j, char c)
{
	int	len;

	len = 0;
	while (s[j] != c && s[j])
	{
		len++;
		j++;
	}
	return (len);
}

static void		free_all(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

char			**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		k;

	if (!s || !(arr = (char**)malloc(sizeof(char*) * ((count_word(s, c)) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < count_word(s, c))
	{
		k = 0;
		while (s[j] == c)
			j++;
		if (!(arr[i] = (char *)malloc(sizeof(char) * (len_word(s, j, c) + 1))))
		{
			free_all(arr);
			return (NULL);
		}
		while (s[j] != c && s[j])
			arr[i][k++] = s[j++];
		arr[i++][k] = '\0';
	}
	arr[i] = NULL;
	return (arr);
}
