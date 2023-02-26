/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:08:30 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/26 00:58:13 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rev_dollar(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == - '$')
			cmd[i] = '$';
		i++;
	}
}

char	check_expand(char *str, char **envp, int i)
{
	int	j;

	j = env_key_len(str + 1);
	str = get_env(str + i + i, envp, j);
	if (!str)
		return (- '$');
	else
		return ('$');
}

void	check_empty_str(char *str)
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (*str && *str != '\'' && *str != '\"')
		str++;
	while (*str)
	{
		q[0] = (q[0] + (!q[1] && *str == '\'')) % 2;
		q[1] = (q[1] + (!q[0] && *str == '\"')) % 2;
		if (q[0] && *str == '\'' && *(str + 1) == '\'')
		{
			*str = - 'e';
			push_str(str + 1);
			q[0] = 0;
		}
		else if (q[1] && *str == '\"' && *(str + 1) == '\"')
		{
			*str = - 'e';
			push_str(str + 1);
			q[1] = 0;
		}
		str++;
	}
}

void	parse_cmd(char *cmd, char **envp)
{
	int		i;
	char	quot;
	char	*tmp;

	i = 0;
	quot = '\0';
	tmp = cmd;
	check_empty_str(cmd);
	cmd = tmp;
	while (*cmd)
	{
		if (!quot && is_quot(*cmd) && ++i)
			quot = *cmd;
		else if (quot && (*cmd == quot) && ++i)
			quot = '\0';
		else
			cmd++;
		*cmd = *(cmd + i);
	}
	cmd = tmp;
	rm_space_sep(cmd);
	rm_empty_str(cmd);
}
