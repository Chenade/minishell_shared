/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:45:53 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/14 18:46:06 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(int i, t_prompt *prompt)
{
	int		cd_ret;
	t_token	*token;
	char	*dest;

	token = move_to(prompt->token, i);
	if (ft_strcmp(token->str, "cd") == 0)
		dest = get_env("HOME", prompt->envp, 1);
	else if (ft_strcmp(token->str, "-") == 0)
	{
		dest = get_env("OLD_PWD", prompt->envp, 1);
		if (!dest)
		{
			print_error(OP_NS, "cd", NULL);
			return (-1);
		}
	}
	else
		dest = token->str;
	update_oldpwd(prompt);
	cd_ret = chdir(dest);
	if (cd_ret < 0)
		print_error(NDIR, "cd", token->str);
	return (cd_ret);
}

int		ft_pwd(t_prompt *prompt)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_print(cwd, prompt);
		ft_print("\n", prompt);
		return (0);
	}
	else
		return (-1);
}

int	ft_echo(int i, t_prompt *prompt)
{
	t_token	*token;
    int     newline;

	token = move_to(prompt->token, i);
    newline = 1;
	while (token)
	{
		if (token->type == 2)
		{
			ft_print (token->str, prompt);
			if (token->next && token->next->type == 2)
				ft_print (" ", prompt);
		}
		else if (token->type == 4)
			ft_print (get_env(token->str, prompt->envp, -1), prompt);
        else if (token->type == 5 && ft_strcmp(token->str, "-n") == 0)
			newline = 0;
		else
			break ;
		token = token->next;
	}
    if (newline)
	    ft_print("\n", prompt);
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
		index = in_envp(token->str, prompt);
		if (index > 0)
			prompt->envp[index] = token->str;
		else
			add_envp(token->str, prompt);
	}
	return (0);
}

int	ft_unset(int i, t_prompt *prompt)
{
	int		index;
	t_token	*token;

	index = -1;
	token = move_to(prompt->token, i);
	if (token->type == 4)
	{
		index = in_envp(token->str, prompt);
		if (index > 0)
			del_envp(index, token, prompt);
	}
	return (0);
}
