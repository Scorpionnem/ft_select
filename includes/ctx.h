/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:54:55 by mbatty            #+#    #+#             */
/*   Updated: 2025/09/28 05:08:15 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "libs.h"

typedef struct s_item
{
	char	*data;
	bool	selected;
} t_item;

typedef struct s_ctx
{
	unsigned int	lines_count;
	unsigned int	columns_count;

	char	*clear_cmd;
	char	*text_color_cmd;
	char	*text_bg_color_cmd;
	char	*reset_cmd;
	char	*blink_cmd;
	char	*bold_cmd;
	char	*underline_cmd;
	char	*show_cursor_cmd;
	char	*hide_cursor_cmd;

	char	*cursor_motion;
	
	struct termios s_termios;
	struct termios s_termios_backup;

	t_item	*items;
	int	items_count;
	int	current;

	bool	running;
} t_ctx;

int	ctx_init(t_ctx *ctx, int ac, char **av);
int	delete_ctx(t_ctx *ctx);
int	ctx_get_term_settings(t_ctx *ctx);

#endif
