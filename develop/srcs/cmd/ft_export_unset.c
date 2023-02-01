
#include "minishell.h"

int	del_envp(t_token *token, t_prompt *prompt)
{
	int		j;
	char	**value;
	char	**env_val;

	j = -1;
	value = ft_split(token->str, '=');
	while(prompt->envp[++j])
	{
		env_val = ft_split(prompt->envp[j], '=');
		if (ft_strcmp(value[0], env_val[0]) == 0)
		{
			prompt->envp[j] = token->str;
			free (env_val);
			return (0);
		}
		free (env_val);
	}
	free (value);
	return (1);
}

int	add_envp(t_token *token, t_prompt *prompt)
{
	int		j;
	char	**value;
	char	**env_val;

	j = -1;
	value = ft_split(token->str, '=');
	while(prompt->envp[++j])
	{
		env_val = ft_split(prompt->envp[j], '=');
		if (ft_strcmp(value[0], env_val[0]) == 0)
		{
			prompt->envp[j] = token->str;
			free (env_val);
			return (0);
		}
		free (env_val);
	}
	free (value);
	return (1);
}

int	in_envp(t_token *token, t_prompt *prompt)
{
	int		j;
	char	**value;
	char	**env_val;

	j = -1;
	value = ft_split(token->str, '=');
	while(prompt->envp[++j])
	{
		env_val = ft_split(prompt->envp[j], '=');
		if (ft_strcmp(value[0], env_val[0]) == 0)
		{
			free (env_val);
			return (j);
		}
		free (env_val);
	}
	free (value);
	return (0);
}

int	ft_export(int i, t_prompt *prompt)
{
	int		index;
	t_token	*token;

	index = -1;
	token = move_to(prompt->token, i);
	if (token->type == 3)
	{
		index = in_envp(token, prompt);
		if(index > 0)
			prompt->envp[index] = token->str;
		else
			add_envp(token, prompt);
	}
	return (0);
}

int	ft_unset(int i, t_prompt *prompt)
{
	int		index;
	t_token	*token;

	index = -1;
	token = move_to(prompt->token, i);
	if (token->type == 3)
	{
		index = in_envp(token, prompt);
		if(index > 0)
			del_envp(token, prompt);
	}
	return (0);
}
