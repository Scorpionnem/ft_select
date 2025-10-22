/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_cmds2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:51:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/22 16:51:18 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

int	show_cursor(t_ctx *ctx)
{
	tputs(ctx->cmds.show_cursor_cmd, 1, ft_putchar);
	return (1);
}

int	set_bold(t_ctx *ctx)
{
	tputs(ctx->cmds.bold_cmd, 1, ft_putchar);
	return (1);
}

int	set_underline(t_ctx *ctx)
{
	tputs(ctx->cmds.underline_cmd, 1, ft_putchar);
	return (1);
}

int	clear_terminal(t_ctx *ctx)
{
	tputs(ctx->cmds.clear_cmd, 1, ft_putchar);
	return (1);
}

int	set_cursor_pos(t_ctx *ctx, int col, int row)
{
	tputs(tgoto(ctx->cmds.cursor_motion, col, row), 1, ft_putchar);
	return (1);
}
