/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 02:54:55 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/22 14:55:06 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "libs.h"

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

typedef struct s_item
{
	char	*data;
	bool	selected;

	struct s_item	*next;
	struct s_item	*previous;
} t_item;

typedef struct s_cmds
{
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
} t_cmds;

typedef struct s_ctx
{
	unsigned int	lines_count;
	unsigned int	columns_count;

	t_cmds	cmds;
	
	struct termios s_termios;
	struct termios s_termios_backup;

	t_item	*items;
	t_item	*cursor;

	bool	running;
} t_ctx;

int		ctx_init(t_ctx *ctx, int ac, char **av);
int		delete_ctx(t_ctx *ctx);
int		ctx_update(t_ctx *ctx);

t_input	read_input();
void	refresh_display(t_ctx *ctx);

void	*error(char *str);

void	items_add_back(t_item **lst, t_item *new);
t_item	*items_last(t_item *lst);
int		items_size(t_item *lst);
t_item	*items_new(char *content);
t_item	*items_biggest(t_item *lst);

#endif
