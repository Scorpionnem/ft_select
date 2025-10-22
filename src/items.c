/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:59:26 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/22 16:49:08 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

void	items_free(t_item *lst)
{
	t_item	*first;
	t_item	*tmp;

	first = lst;
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
		if (lst == first)
			break ;
	}
}

t_item	*items_new(char *content)
{
	t_item	*new_node;

	new_node = malloc(sizeof(t_item));
	if (!new_node)
		return (NULL);
	new_node->data = content;
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->selected = false;
	return (new_node);
}

void	items_add_back(t_item **lst, t_item *new)
{
	t_item	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = items_last(*lst);
		last->next = new;
		new->previous = last;
		new->next = *lst;
		(*lst)->previous = new;
	}
	else
		*lst = new;
}

t_item	*items_last(t_item *lst)
{
	int	count;

	count = items_size(lst);
	while (count > 1)
	{
		lst = lst->next;
		count--;
	}
	return (lst);
}

int	items_size(t_item *lst)
{
	int		count;
	t_item	*first;

	count = 0;
	first = lst;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
		if (lst == first)
			break ;
	}
	return (count);
}
