#include "minishell.h"

int	del_envp(int index, t_token *token, t_prompt *prompt)
{
	int		i;
	int		j;
	char	**env_new;

	env_new = (char **) malloc((get_matrixlen(prompt->envp) - 1)
			* sizeof(char *));
	if (!env_new)
		return (1);
	i = 0;
	j = -1;
	while (prompt->envp[++j])
	{
		if (j != index)
		{
			env_new[i] = ft_strdup(prompt->envp[j]);
			if (!env_new)
				return (-1);
			i += 1;
		}
	}
	env_new[i] = NULL;
	free_pp (prompt->envp);
	prompt->envp = env_new;
	return (0);
}

int	add_envp(char *str, t_prompt *prompt)
{
	int		j;
	char	**env_new;

	env_new = (char **) malloc((get_matrixlen(prompt->envp) + 1)
			* sizeof(char *));
	if (!env_new)
		return (1);
	j = -1;
	while (prompt->envp[++j])
	{
		env_new[j] = ft_strdup(prompt->envp[j]);
		if (!env_new)
			return (-1);
	}
	env_new[j] = ft_strdup(str);
	env_new[j + 1] = NULL;
	free_pp (prompt->envp);
	prompt->envp = env_new;
	return (0);
}

int	in_envp(char *token, t_prompt *prompt)
{
	int		j;
	char	**value;
	char	**env_val;

	j = -1;
	value = ft_split(token, '=');
	while (prompt->envp[++j])
	{
		env_val = ft_split(prompt->envp[j], '=');
		if (ft_strcmp(value[0], env_val[0]) == 0)
		{
			free_pp (env_val);
			return (j);
		}
		free_pp (env_val);
	}
	free_pp (value);
	return (0);
}
