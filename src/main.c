/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/23 09:00:46 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "term_cmds.h"

static t_ctx	g_ctx;

static void	handle_signal(int sig)
{
	(void)sig;
	g_ctx.running = false;
}

static void	handle_signalstp(int sig)
{
	(void)sig;
	tcsetattr(g_ctx.term_fd, TCSANOW, &g_ctx.s_termios_backup);
	signal(SIGTSTP, SIG_DFL);
	show_cursor(&g_ctx);
	ioctl(g_ctx.term_fd, TIOCSTI, "\x1A");
}

static void	handle_signalcont(int sig)
{
	(void)sig;
	tcsetattr(g_ctx.term_fd, TCSAFLUSH, &g_ctx.s_termios);
	hide_cursor(&g_ctx);
	refresh_display(&g_ctx);
	signal(SIGTSTP, handle_signalstp);
}

void	setup_signals(void)
{
	signal(SIGABRT, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGSTOP, handle_signal);
	signal(SIGKILL, handle_signal);
	signal(SIGTSTP, handle_signalstp);
	signal(SIGCONT, handle_signalcont);
}

void	check_input(t_ctx *ctx, t_input input)
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

int	main(int ac, char **av)
{
	if (ac < 2)
		return (!error("Error\nNot enough arguments"));
	if (!ctx_init(&g_ctx, ac, av))
		return (1);
	setup_signals();
	loop(&g_ctx);
	return (delete_ctx(&g_ctx));
}
