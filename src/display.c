/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:33:55 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/29 09:01:31 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "term_cmds.h"

int	items_per_line(t_ctx *ctx)
{
	int		length;
	t_item	*biggest;

	biggest = items_biggest(ctx->items);
	if (!biggest)
		return (1);
	length = ft_strlen(biggest->data);
	if (length <= 0)
		length = 1;
	return (ctx->columns_count / length);
}

static void	print_item(t_ctx *ctx, t_item *lst, t_item *cursor)
{
	if (cursor == lst)
	{
		set_underline(ctx);
		set_bold(ctx);
	}
	if (lst->selected)
		set_inverse(ctx);
	ft_putstr_fd(lst->data, 2);
	reset_terminal(ctx);
	ft_putchar_fd(' ', 2);
}

static void	print_items(t_ctx *ctx)
{
	t_item	*first;
	t_item	*lst;
	int		written_count;
	int		max_width;

	lst = ctx->items;
	first = lst;
	written_count = 0;
	max_width = items_per_line(ctx);
	while (lst != NULL)
	{
		if (written_count >= max_width)
		{
			written_count = 1;
			ft_putchar_fd('\n', 2);
		}
		else
			written_count++;
		print_item(ctx, lst, ctx->cursor);
		lst = lst->next;
		if (lst == first)
			break ;
	}
	ft_putchar_fd('\n', 2);
}

void	refresh_display(t_ctx *ctx)
{
	clear_terminal(ctx);
	print_items(ctx);
}
