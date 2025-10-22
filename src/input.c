/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:22:21 by mbatty            #+#    #+#             */
/*   Updated: 2025/10/22 16:43:01 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"

t_input	read_input(void)
{
	char	buf[8];
	size_t	n;

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
