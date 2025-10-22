/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:55:45 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/22 16:58:03 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "term_cmds.h"

static int	ctx_set_canonical_term(t_ctx *ctx)
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
	items_free(ctx->items);
	return (0);
}

static int	ctx_fill_list(t_ctx *ctx, char **av)
{
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
	ac = 42;
	ft_bzero(ctx, sizeof(t_ctx));
	ctx->running = true;
	if (!ctx_init_term())
		return (0);
	if (!ctx_set_canonical_term(ctx))
		return (0);
	if (!ctx_get_term_commands(ctx))
		return (0);
	if (!ctx_fill_list(ctx, ++av))
		return (0);
	if (!ctx_update(ctx))
		return (0);
	hide_cursor(ctx);
	ctx->cursor = ctx->items;
	return (1);
}
