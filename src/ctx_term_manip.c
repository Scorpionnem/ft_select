/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_term_manip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:49:41 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/24 08:29:24 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "term_cmds.h"

void	ctx_stop(t_ctx *ctx)
{
	clear_terminal(ctx);
	ctx->running = false;
}

int	ctx_init_term(t_ctx *ctx)
{
	int		success;
	char	*termtype;
	char	buffer[2048];
	char	*tty_name;

	if (isatty(0))
	{
		tty_name = ttyname(0);
		if (!tty_name)
			return (!!error("Error\nFailed to get ttyname"));
		ctx->term_fd = open(tty_name, O_RDWR);
		if (ctx->term_fd == -1)
			return (!!error("Error\nFailed to open terminal"));
	}
	termtype = getenv("TERM");
	if (!termtype)
		return (!!error("Error\nNo TERM env variable"));
	success = tgetent(buffer, termtype);
	if (success < 0)
		return (!!error("Error\nFailed to get termcap database"));
	else if (success == 0)
		return (!!error("Error\nTerminal not defined in termcap"));
	return (1);
}

int	ctx_get_term_commands(t_ctx *ctx)
{
	ctx->cmds.clear_cmd = tgetstr("cl", NULL);
	ctx->cmds.text_color_cmd = tgetstr("AF", NULL);
	ctx->cmds.text_bg_color_cmd = tgetstr("AB", NULL);
	ctx->cmds.reset_cmd = tgetstr("me", NULL);
	ctx->cmds.bold_cmd = tgetstr("md", NULL);
	ctx->cmds.underline_cmd = tgetstr("us", NULL);
	ctx->cmds.blink_cmd = tgetstr("mb", NULL);
	ctx->cmds.hide_cursor_cmd = tgetstr("vi", NULL);
	ctx->cmds.show_cursor_cmd = tgetstr("ve", NULL);
	ctx->cmds.cursor_motion = tgetstr("cm", NULL);
	return (1);
}

int	ctx_update(t_ctx *ctx)
{
	struct winsize	w;
	unsigned int	prev_width;
	unsigned int	prev_height;

	if (ioctl(ctx->term_fd, TIOCGWINSZ, &w) < 0)
		return (0);
	prev_width = ctx->columns_count;
	prev_height = ctx->lines_count;
	ctx->columns_count = w.ws_col;
	ctx->lines_count = w.ws_row;
	if (prev_height != ctx->lines_count || prev_width != ctx->columns_count)
	{
		refresh_display(ctx);
		ctx->cursor = items_last(ctx->items);
	}
	return (1);
}
