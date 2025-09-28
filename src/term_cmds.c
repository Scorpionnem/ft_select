/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 03:26:00 by mbatty            #+#    #+#             */
/*   Updated: 2025/09/28 05:06:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

int	reset_terminal(t_ctx *ctx)
{
	tputs(ctx->reset_cmd, 1, ft_putchar);
	return (1);
}

int	set_color(t_ctx *ctx, int color)
{
	tputs(tparm(ctx->text_color_cmd, color), 1, ft_putchar);
	return (1);
}

int	set_bg_color(t_ctx *ctx, int color)
{
	tputs(tparm(ctx->text_bg_color_cmd, color), 1, ft_putchar);
	return (1);
}

int	set_blink(t_ctx *ctx)
{
	tputs(ctx->blink_cmd, 1, ft_putchar);
	return (1);
}

int	hide_cursor(t_ctx *ctx)
{
	tputs(ctx->hide_cursor_cmd, 1, ft_putchar);
	return (1);
}

int	show_cursor(t_ctx *ctx)
{
	tputs(ctx->show_cursor_cmd, 1, ft_putchar);
	return (1);
}


int	set_bold(t_ctx *ctx)
{
	tputs(ctx->bold_cmd, 1, ft_putchar);
	return (1);
}

int	set_underline(t_ctx *ctx)
{
	tputs(ctx->underline_cmd, 1, ft_putchar);
	return (1);
}

int	clear_terminal(t_ctx *ctx)
{
	tputs(ctx->clear_cmd, 1, ft_putchar);
	return (1);
}

int	set_cursor_pos(t_ctx *ctx, int col, int row)
{
	tputs(tgoto(ctx->cursor_motion, col, row), 1, ft_putchar);
	return (1);
}
