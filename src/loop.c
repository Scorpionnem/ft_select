/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:07:31 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/23 13:14:24 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "term_cmds.h"

static void	check_input(t_ctx *ctx, t_input input)
{
	if (input == FT_KEY_ESCAPE)
		ctx_stop(ctx);
	else if (input == FT_KEY_LEFT)
		move_left(ctx);
	else if (input == FT_KEY_RIGHT)
		move_right(ctx);
	else if (input == FT_KEY_UP)
		move_up(ctx);
	else if (input == FT_KEY_DOWN)
		move_down(ctx);
	else if (input == FT_KEY_SPACE)
		select_item(ctx);
	else if (input == FT_KEY_ENTER)
		validate_selection(ctx);
	else if (input == FT_KEY_BACKSPACE || input == FT_KEY_DELETE)
		delete_item(ctx);
}

void	loop(t_ctx *ctx)
{
	t_input	input;

	refresh_display(ctx);
	while (ctx->running)
	{
		ctx_update(ctx);
		input = read_input();
		check_input(ctx, input);
	}
}
