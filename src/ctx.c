/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:55:45 by mbatty            #+#    #+#             */
/*   Updated: 2025/09/28 05:37:12 by mbatty           ###   ########.fr       */
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
		fprintf(stderr, "Specify a terminal type with `TERM` environment variable.\n");
		return (0);
	}

	success = tgetent(NULL, termtype);
	if (success < 0)
	{
		fprintf(stderr, "Could not access the termcap database.\n");
		return (0);
	}
	else if (success == 0)
	{
		fprintf(stderr, "Terminal type `%s` is not defined.\n", termtype);
		return (0);
	}
	return (1);
}

static int	ctx_get_term_commands(t_ctx *ctx)
{
	ctx->clear_cmd = tgetstr("cl", NULL);
	ctx->text_color_cmd = tgetstr("AF", NULL);
	ctx->text_bg_color_cmd = tgetstr("AB", NULL);
	ctx->reset_cmd = tgetstr("me", NULL);
	ctx->bold_cmd = tgetstr("md", NULL);
	ctx->underline_cmd = tgetstr("us", NULL);
	ctx->blink_cmd = tgetstr("mb", NULL);

	ctx->hide_cursor_cmd = tgetstr("vi", NULL);
	ctx->show_cursor_cmd = tgetstr("ve", NULL);
	ctx->cursor_motion = tgetstr("cm", NULL);
	return (1);
}

void	refresh_display(t_ctx *ctx);

int	ctx_get_term_settings(t_ctx *ctx)
{
	struct winsize w;
	unsigned int	prev_col;
	unsigned int	prev_row;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	prev_col = ctx->columns_count;
	prev_row = ctx->lines_count;
	ctx->columns_count = w.ws_col;
	ctx->lines_count = w.ws_row;
	if (prev_col != ctx->columns_count || prev_row != ctx->lines_count)
		refresh_display(ctx);
	return (1);
}

static int	ctx_set_canonical_temr(t_ctx *ctx)
{
	if (tcgetattr(0, &ctx->s_termios) == -1)
		return (0);

	if (tcgetattr(0, &ctx->s_termios_backup) == -1)
		return (0);

	ctx->s_termios.c_lflag &= ~(ICANON); //Sets canonical form (no need to enter to get inputs)
	ctx->s_termios.c_lflag &= ~(ECHO); //No rendering of typed keys
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
	int		i;

	i = 0;
	ac--;
	av++;
	ctx->items = malloc(sizeof(t_item) * ac);
	ctx->items_count = ac;
	while (i < ac)
	{
		ctx->items[i].data = av[i];
		ctx->items[i].selected = false;
		i++;
	}
	ctx->current = 0;
	return (1);
}

int	ctx_init(t_ctx *ctx, int ac, char **av)
{
	ctx->running = true;
	if (!ctx_init_term(ctx))
		return (0);
	if (!ctx_set_canonical_temr(ctx))
		return (0);
	if (!ctx_get_term_commands(ctx))
		return (0);
	if (!ctx_fill_list(ctx, ac, av))
		return (0);
	if (!ctx_get_term_settings(ctx))
		return (0);
	hide_cursor(ctx);
	return (1);
}
