/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/22 17:18:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "term_cmds.h"

int	g_running = 0;

static void	handle_signal(int sig)
{
	g_running = sig;
}

//signal(SIGTSTP, handle_signal);
//signal(SIGCONT, handle_signal);
void	setup_signals(void)
{
	signal(SIGABRT, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGSTOP, handle_signal);
	signal(SIGKILL, handle_signal);
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
	while (!g_running && ctx->running)
	{
		ctx_update(ctx);
		input = read_input();
		check_input(ctx, input);
	}
}

int	main(int ac, char **av)
{
	t_ctx	ctx;

	if (ac < 2)
		return (!error("Error\nNot enough arguments"));
	if (!ctx_init(&ctx, ac, av))
		return (1);
	setup_signals();
	loop(&ctx);
	return (delete_ctx(&ctx));
}
