#include "minishell.h"

int	is_sep(char s)
{
	if (s == - '<' || s == - '>' || s == - '|' || s == - ' ' || s == - 'e')
		return (1);
	return (0);
}

int	is_quot(char s)
{
	if (s == '\'' || s == '\"')
		return (1);
	return (0);
}

void	rm_space_sep(char *cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		// if ((is_sep(*cmd) && *(cmd - 1) == - ' ') && ++i)
			// *(cmd - 1) = *(cmd + i - 1);
		if ((*(cmd) == - ' ' && (is_sep(*(cmd + 1)) && *(cmd + 1) != - ' ')) && ++i)
			;
		else if ((*(cmd) == - ' ' && (is_sep(*(cmd - 1)) && *(cmd - 1) != - ' ')) && ++i)
		{
			*(cmd) = *(cmd + i);
			cmd++;
		}
		else if ((*cmd) == -'$')
			i += ((env_key_len(cmd )) + 1);
		else
			cmd++;
		*(cmd) = *(cmd + i);
	}
}

void rev_dollar(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == -'$')
			cmd[i] = '$';
		i++;
	}
}

char	check_expand(char *str, char **envp, int	i)
{
	int	j;

	j = env_key_len(str + 1);
	str = get_env(str + i+i, envp, j);
	if (!str)
		return (-'$');
	else
		return ('$');
}

void swipe_str(char *str)
{
	while (*str)
	{
		*str = *(str + 1);
		str++;
	}
}

void check_empty_str(char *str)
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
			*str = -'e';
			swipe_str(str + 1);
			q[0] = 0;
		}
		else if (q[1] && *str == '\"' && *(str + 1) == '\"')
		{
			*str = -'e';
			swipe_str(str + 1);
			q[1] = 0;
		}
		str++;
	}
}

void	parse_cmd(char *cmd, char **envp)
{
	int	i;
	char quot;
	char *tmp;

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
}