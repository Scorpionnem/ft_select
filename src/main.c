/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:44:15 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/04 10:37:36 by mbatty           ###   ########.fr       */
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

typedef enum e_input
{
	FT_KEY_ENTER,
	FT_KEY_UP,
	FT_KEY_DOWN,
	FT_KEY_RIGHT,
	FT_KEY_LEFT,
	FT_KEY_ESCAPE,
	FT_KEY_SPACE,
	FT_KEY_DELETE,
	FT_KEY_BACKSPACE,
	FT_NO_INPUT
} t_input;

t_input	read_input()
{
	char buf[8];
	ssize_t n;

	n = read(STDIN_FILENO, buf, sizeof(buf));
	if (n <= 0)
		return (FT_NO_INPUT);
	if (buf[0] == 10)
		return (FT_KEY_ENTER);
	else if (buf[0] == 27)
	{
		if (n >= 4 && buf[1] == '[' && buf[2] == '3' && buf[3] == '~')
			return (FT_KEY_DELETE);
		if (n >= 3 && buf[1] == '[')
		{
			if (buf[2] >= 'A' && buf[2] <= 'D')
				return (FT_KEY_UP + (buf[2] - 'A'));
		}
		else if (n == 1)
			return (FT_KEY_ESCAPE);
	}
	else if (buf[0] == ' ')
		return (FT_KEY_SPACE);
	else if (buf[0] == 127 || buf[0] == 8)
		return (FT_KEY_BACKSPACE);
	return (FT_NO_INPUT);
}

void	refresh_display(t_ctx *ctx)
{
	int	i = 0;
	int	yoffset;
	unsigned int	len;

	yoffset = 0;
	clear_terminal(ctx);
	while (i < ctx->items_count)
	{
		if (i == ctx->current)
			set_underline(ctx);
		if (ctx->items[i].selected)
			set_bg_color(ctx, COLOR_RED);

		set_cursor_pos(ctx, (ctx->columns_count / 2) - (ft_strlen(ctx->items[i].data) / 2), ((ctx->lines_count / 2) - (ctx->items_count) / 2) + i + yoffset);
		len = ft_strlen(ctx->items[i].data);
		if (len > ctx->columns_count)
			yoffset += (len / ctx->columns_count);
		dprintf(2, "%s\n", ctx->items[i].data);
		reset_terminal(ctx);
		i++;

	}
	dprintf(2, "\n");
}

void	move_current(t_ctx *ctx, int dir)
{
	ctx->current += dir;

	if (ctx->current < 0)
		ctx->current = ctx->items_count - 1;
	if (ctx->current >= ctx->items_count)
		ctx->current = 0;

	refresh_display(ctx);
}

void	print_selected(t_ctx *ctx)
{
	int	i = 0;

	clear_terminal(ctx);
	while (i < ctx->items_count)
	{
		if (ctx->items[i].selected)
			// printf("%s ", ctx->items[i].data);
			dprintf(2, "%s ", ctx->items[i].data);
		i++;
	}
	dprintf(2, "\n");
}

void	parse_input(t_ctx *ctx, t_input input)
{
	if (input == FT_KEY_ESCAPE)
		ctx->running = false;
	if (input == FT_KEY_UP || input == FT_KEY_LEFT)
		move_current(ctx, -1);
	if (input == FT_KEY_DOWN || input == FT_KEY_RIGHT)
		move_current(ctx, 1);
	if (input == FT_KEY_SPACE)
	{
		ctx->items[ctx->current].selected = !ctx->items[ctx->current].selected;
		move_current(ctx, 1);
	}
	if (input == FT_KEY_ENTER)
	{
		print_selected(ctx);
		ctx->running = false;
	}
}

int	main(int ac, char **av)
{
	t_ctx	ctx;
	t_input	input;

	if (ac < 2)
	{
		ft_putendl_fd("Error\nNot enough arguments", 2);
		return (1);
	}
	
	signal(SIGINT, handle_sigint);
	
	if (!ctx_init(&ctx, ac, av))
		return (1);

	refresh_display(&ctx);
	while (g_running && ctx.running)
	{
		ctx_get_term_settings(&ctx);
		
		input = read_input();
		parse_input(&ctx, input);
	}

	return (delete_ctx(&ctx));
}
