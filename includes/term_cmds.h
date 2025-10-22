/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_cmds.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 03:26:23 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/22 16:45:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_CMDS_H
# define TERM_CMDS_H

# include "ctx.h"

int	reset_terminal(t_ctx *ctx);
int	set_color(t_ctx *ctx, int color);
int	set_blink(t_ctx *ctx);
int	set_bold(t_ctx *ctx);
int	set_underline(t_ctx *ctx);
int	clear_terminal(t_ctx *ctx);
int	set_cursor_pos(t_ctx *ctx, int col, int row);
int	set_bg_color(t_ctx *ctx, int color);
int	hide_cursor(t_ctx *ctx);
int	show_cursor(t_ctx *ctx);

#endif
