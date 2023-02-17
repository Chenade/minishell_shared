#include "minishell.h"

int get_env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == ' ' || str[i] == '$')
			break;
		else
			i++;
	}
	return (i);
}

int	jump_env(char *str, int i, int *len, t_prompt *p)
{
	int	env_len;
	int	env_count;
	char *tmp;

	env_len = get_env_len(str + i + 1);
	tmp = get_env(str + i + 1, p->envp, env_len);
	if (tmp)
	{
		env_count = ft_strlen(tmp);
		free (tmp);
		*(len) = *(len) + env_count;
	}
	return (env_len + 1);
}
