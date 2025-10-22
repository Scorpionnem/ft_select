/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:55:45 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/22 14:55:19 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ctx.h"
# include "term_cmds.h"

static int	ctx_init_term(t_ctx *ctx)
{
	(void)ctx;
	int		success;
	char	*termtype;
	
	termtype = getenv("TERM");
	if (!termtype)
	{
		dprintf(2, "Specify a terminal type with `TERM` environment variable.\n");
		return (0);
	}

	success = tgetent(NULL, termtype);
	if (success < 0)
	{
		dprintf(2, "Could not access the termcap database.\n");
		return (0);
	}
	else if (success == 0)
	{
		dprintf(2, "Terminal type `%s` is not defined.\n", termtype);
		return (0);
	}
	return (1);
}

static int	ctx_get_term_commands(t_ctx *ctx)
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
	struct winsize w;
	unsigned int	prev_width;
	unsigned int	prev_height;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	prev_width = ctx->columns_count;
	prev_height = ctx->lines_count;
	ctx->columns_count = w.ws_col;
	ctx->lines_count = w.ws_row;
	if (prev_height != ctx->lines_count || prev_width != ctx->columns_count)
		refresh_display(ctx);
	return (1);
}

static int	ctx_set_canonical_temr(t_ctx *ctx)
{
	if (tcgetattr(0, &ctx->s_termios) == -1)
		return (0);

	if (tcgetattr(0, &ctx->s_termios_backup) == -1)
		return (0);

	ctx->s_termios.c_lflag &= ~(ICANON);
	ctx->s_termios.c_lflag &= ~(ECHO);
	ctx->s_termios.c_cc[VMIN] = 0;
	ctx->s_termios.c_cc[VTIME] = 1;

	if (tcsetattr(STDIN_FILENO, TCSANOW, &ctx->s_termios) == -1)
		return (0);
	return (1);
}

int	delete_ctx(t_ctx *ctx)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &ctx->s_termios_backup) == -1)
		return (1);
	show_cursor(ctx);
	return (0);
}

static int	ctx_fill_list(t_ctx *ctx, int ac, char **av)
{
	(void)ctx;
	(void)ac;
	(void)av;
	int		i;
	t_item	*new;

	i = 0;
	while (av[i])
	{
		new = items_new(av[i]);
		items_add_back(&ctx->items, new);
		i++;
	}
	ctx->cursor = ctx->items;
	return (1);
}

int	ctx_init(t_ctx *ctx, int ac, char **av)
{
	ft_bzero(ctx, sizeof(t_ctx));
	ctx->running = true;
	if (!ctx_init_term(ctx))
		return (0);
	if (!ctx_set_canonical_temr(ctx))
		return (0);
	if (!ctx_get_term_commands(ctx))
		return (0);
	if (!ctx_fill_list(ctx, --ac, ++av))
		return (0);
	if (!ctx_update(ctx))
		return (0);
	hide_cursor(ctx);
	return (1);
}
