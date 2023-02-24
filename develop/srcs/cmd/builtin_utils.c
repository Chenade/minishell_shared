/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:46:14 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/14 18:46:15 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char	*cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	del_envp(int index, t_token *token, t_prompt *prompt)
{
	int		i;
	int		j;
	char	**env_new;

	env_new = (char **) malloc((get_matrixlen(prompt->envp))
			* sizeof(char *));
	if (!env_new)
		return (print_error(MEM, "unset", NULL));
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

	env_new = (char **) malloc((get_matrixlen(prompt->envp) + 2)
			* sizeof(char *));
	if (!env_new)
		return (print_error(MEM, "export", NULL));
	j = -1;
	while (prompt->envp && prompt->envp[++j])
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

int	in_envp(char *str, t_prompt *prompt)
{
	int		j;
	char	**value;
	char	**env_val;

	j = -1;
	value = ft_split(str, '=');
	while (prompt->envp[++j])
	{
		env_val = ft_split(prompt->envp[j], '=');
		if (ft_strcmp(value[0], env_val[0]) == 0)
		{
			free_pp (value);
			free_pp (env_val);
			return (j);
		}
		free_pp (env_val);
	}
	free_pp (value);
	return (-1);
}

int	update_oldpwd(t_prompt *prompt)
{
	int		index;
	char	*val;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		val = ft_strjoin("OLD_PWD=", cwd);
		index = in_envp(val, prompt);
		if (index > 0)
			prompt->envp[index] = ft_strdup(val);
		else
			add_envp(val, prompt);
		free (val);
		return (0);
	}
	return (-1);
}
