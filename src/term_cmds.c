/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 03:26:00 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/29 09:00:06 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

int	reset_terminal(t_ctx *ctx)
{
	tputs(ctx->cmds.reset_cmd, 1, ft_putchar);
	return (1);
}

int	set_color(t_ctx *ctx, int color)
{
	tputs(tparm(ctx->cmds.text_color_cmd, color), 1, ft_putchar);
	return (1);
}

int	set_bg_color(t_ctx *ctx, int color)
{
	tputs(tparm(ctx->cmds.text_bg_color_cmd, color), 1, ft_putchar);
	return (1);
}

int	set_inverse(t_ctx *ctx)
{
	tputs(ctx->cmds.inverse_video_cmd, 1, ft_putchar);
	return (1);
}

int	hide_cursor(t_ctx *ctx)
{
	tputs(ctx->cmds.hide_cursor_cmd, 1, ft_putchar);
	return (1);
}
