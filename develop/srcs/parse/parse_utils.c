/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:51:08 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/26 01:40:08 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_empty_str(char *cmd)
{
	int	i;

	i = 0;
	while (*cmd == - 'e' && *(cmd + 1) && *(cmd + 1) != - ' ')
		push_str(cmd);
	while (*cmd)
	{
		if (*(cmd) == - 'e' && *(cmd + 1) == - 'e')
			push_str(cmd);
		else if (*(cmd) == - 'e' && *(cmd + 1)
			&& *(cmd + 1) != - ' ' && *(cmd + 1) != - 'e')
			push_str(cmd);
		else
			cmd++;
	}
}

void	rm_space_sep(char *cmd)
{
	int	i;

	i = 0;
	while (*cmd == - ' ')
		push_str(cmd);
	while (*cmd)
	{
		if ((*(cmd) == - ' '
				&& (is_sep(*(cmd + 1)) && *(cmd + 1) != - ' ')) && ++i)
			push_str(cmd);
		else if ((*(cmd) == - ' '
				&& (is_sep(*(cmd - 1)) && *(cmd - 1) != - ' ')) && ++i)
			push_str(cmd);
		else if (*(cmd) == - ' ' && *(cmd + 1) == - ' ')
			push_str(cmd);
		else if ((*cmd) == - '$')
			i += ((env_key_len(cmd)) + 1);
		else
			cmd++;
	}
}
