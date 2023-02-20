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

int	ft_print(char *str, int	fd)
{
	ft_putstr_fd (str, fd);
    return (0);
}

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

	env_new = (char **) malloc((get_matrixlen(prompt->envp) + 2)
			* sizeof(char *));
	if (!env_new)
		return (1);
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
	return (0);
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
			prompt->envp[index] = val;
		else
			add_envp(val, prompt);
		free (val);
		return (0);
	}
    return (-1);
}
