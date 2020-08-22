/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froxanne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 12:03:02 by froxanne          #+#    #+#             */
/*   Updated: 2020/08/21 15:01:32 by froxanne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*list;

	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else if (*lst)
	{
		list = *lst;
		new->next = list;
		*lst = new;
	}
}

void		ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else if (lst && *lst)
	{
		list = *lst;
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

t_list		*ft_lstnew(void *content)
{
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
		list->content = NULL;
	else
		list->content = content;
	list->next = NULL;
	return (list);
}

static void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
	lst = NULL;
}

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*list;

	if (!(*lst) || !lst || !del)
		return ;
	cur = *lst;
	while (cur)
	{
		list = cur->next;
		ft_lstdelone(cur, del);
		cur = list;
	}
	*lst = NULL;
}
