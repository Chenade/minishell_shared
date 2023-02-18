#include "minishell.h"

int	is_sep(char s)
{
	if (s == - '<' || s == - '>' || s == - '|' || s == - ' ')
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
		if ((is_sep(*cmd) && *(cmd - 1) == - ' ') && ++i)
			*(cmd - 1) = *(cmd + i - 1);
		else if ((*(cmd) == - ' ' && is_sep(*(cmd - 1))) && ++i)
			*(cmd) = *(cmd + i);
		else
			cmd++;
		*(cmd) = *(cmd + i);
	}
}

void	parse_cmd(char *cmd)
{
	int	i;
	char quot;
	char *tmp;

	i = 0;
	quot = '\0';
	tmp = cmd;
	while (*cmd == ' ')
		cmd++;
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