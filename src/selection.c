/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:47:48 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/26 09:11:38 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

t_item	*items_biggest(t_item *lst)
{
	t_item	*first;
	t_item	*biggest;

	first = lst;
	biggest = first;
	while (lst != NULL)
	{
		if (ft_strlen(lst->data) > ft_strlen(biggest->data))
			biggest = lst;
		lst = lst->next;
		if (lst == first)
			break ;
	}
	return (biggest);
}

static bool	has_selected_after(t_item *lst)
{
	t_item	*first;

	first = lst;
	lst = lst->next;
	while (lst)
	{
		if (lst->selected)
			return (true);
		lst = lst->next;
		if (lst == first)
			break ;
	}
	return (false);
}

void	validate_selection(t_ctx *ctx)
{
	t_item	*first;
	t_item	*lst;
	int		selected;

	ctx_stop(ctx);
	lst = ctx->items;
	first = lst;
	selected = 0;
	while (lst)
	{
		if (lst->selected)
		{
			lst->selected = false;
			ft_putstr_fd(lst->data, 1);
			if (has_selected_after(lst))
				ft_putchar_fd(' ', 1);
			selected++;
		}
		lst = lst->next;
		if (lst == first)
			break ;
	}
	if (selected)
		ft_putchar_fd('\n', 1);
}

void	delete_item(t_ctx *ctx)
{
	t_item	*first;
	t_item	*lst;

	lst = ctx->items;
	first = lst;
	if (items_size(ctx->items) <= 1)
		return (ctx_stop(ctx));
	while (lst != NULL)
	{
		if (lst == ctx->cursor)
		{
			lst->previous->next = lst->next;
			lst->next->previous = lst->previous;
			ctx->cursor = lst->next;
			if (lst == ctx->items)
				ctx->items = ctx->items->next;
			free(lst);
			break ;
		}
		lst = lst->next;
		if (lst == first)
			break ;
	}
	refresh_display(ctx);
}

void	select_item(t_ctx *ctx)
{
	ctx->cursor->selected = !ctx->cursor->selected;
	move_right(ctx);
}
