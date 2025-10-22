/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:32:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/22 16:44:01 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

void	move_up(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < items_per_line(ctx))
	{
		move_left(ctx);
		i++;
	}
	refresh_display(ctx);
}

void	move_down(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < items_per_line(ctx))
	{
		move_right(ctx);
		i++;
	}
	refresh_display(ctx);
}

void	move_left(t_ctx *ctx)
{
	if (ctx->cursor->previous)
		ctx->cursor = ctx->cursor->previous;
	refresh_display(ctx);
}

void	move_right(t_ctx *ctx)
{
	if (ctx->cursor->next)
		ctx->cursor = ctx->cursor->next;
	refresh_display(ctx);
}
