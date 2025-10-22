/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/22 15:50:53 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "term_cmds.h"

bool	g_running = true;

void	handle_sigint(int sig)
{
	(void)sig;
	g_running = false;
}

int	items_per_line(t_ctx *ctx)
{
	return (ctx->columns_count / ft_strlen(items_biggest(ctx->items)->data));
}

void	print_items(t_ctx *ctx)
{
	t_item	*first;
	t_item	*lst;
	int		written_count;
	int		max_width;

	lst = ctx->items;
	first = lst;
	written_count = 0;
	max_width = items_per_line(ctx);
	while (lst != NULL)
	{
		if (written_count >= max_width)
		{
			written_count = 1;
			dprintf(2, "\n");
		}
		else
			written_count++;

		if (ctx->cursor == lst)
		{
			set_underline(ctx);
			set_bold(ctx);
		}
		if (lst->selected)
		{
			set_bg_color(ctx, COLOR_WHITE);
			set_color(ctx, COLOR_BLACK);
		}

		dprintf(2, "%s ", lst->data);
		reset_terminal(ctx);
		
		lst = lst->next;
		if (lst == first)
			break ;
	}
	dprintf(2, "\n");
}

void	refresh_display(t_ctx *ctx)
{
	clear_terminal(ctx);
	print_items(ctx);
}

void	ctx_stop(t_ctx *ctx)
{
	clear_terminal(ctx);
	ctx->running = false;
}

void	validate_selection(t_ctx *ctx)
{
	t_item	*first;
	t_item	*lst;

	ctx_stop(ctx);
	lst = ctx->items;
	first = lst;
	while (lst != NULL)
	{
		if (lst->selected)
			printf("%s ", lst->data);
		lst = lst->next;
		if (lst == first)
			break ;
	}
	printf("\n");
}

void	move_left(t_ctx *ctx)
{
	if (ctx->cursor->previous)
		ctx->cursor = ctx->cursor->previous;
	refresh_display(ctx);
}

void	move_right(t_ctx *ctx)
{
	if (ctx->cursor->next)
		ctx->cursor = ctx->cursor->next;
	refresh_display(ctx);
}

void	select_item(t_ctx *ctx)
{
	ctx->cursor->selected = !ctx->cursor->selected;
	move_right(ctx);
}

void	move_up(t_ctx *ctx)
{
	int	i = 0;

	while (i < items_per_line(ctx))
	{
		move_left(ctx);
		i++;
	}
	refresh_display(ctx);
}

void	move_down(t_ctx *ctx)
{
	int	i = 0;

	while (i < items_per_line(ctx))
	{
		move_right(ctx);
		i++;
	}
	refresh_display(ctx);
}

void	setup_signals()
{
	signal(SIGABRT, handle_sigint);
	signal(SIGINT, handle_sigint);
	// signal(SIGSTOP, handle_sigint);
	signal(SIGCONT, handle_sigint);
	signal(SIGTSTP, handle_sigint);
	// signal(SIGKILL, handle_sigint);
	signal(SIGQUIT, handle_sigint);
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
}

void	loop(t_ctx *ctx)
{
	t_input	input;

	refresh_display(ctx);
	while (g_running && ctx->running)
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
