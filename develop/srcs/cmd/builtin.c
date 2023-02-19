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

int	ft_cd(t_request *request, t_prompt *prompt)
{
	int		cd_ret;
	int		i;
	t_token	*token;
	char	*dest;

	// token = move_to(prompt->token, i);
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

int		ft_pwd(t_request *request, t_prompt *prompt)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_print(cwd, 1);
		ft_print("\n", 1);
		return (0);
	}
	else
		return (-1);
}

int	ft_echo(t_request *request, t_prompt *prompt)
{
	printf("[DEBUG] echo\n");
	int	i;
	int	newline;

    newline = 1;
	while (request->token)
	{
		if (request->token->type == 2)
		{
			ft_print (request->token->str, 1);
			if (request->token->next && request->token->next->type == 2)
				ft_print (" ", 1);
		}
        else if (request->token->type == 5 && ft_strcmp(request->token->str, "-n") == 0)
			newline = 0;
		else
			break ;
		request->token = request->token->next;
	}
    if (newline)
	    ft_print("\n", 1);
	return (0);
}

int	ft_export(t_request *request, t_prompt *prompt)
{
	int		index;
	t_token	*token;

	index = -1;
	// token = move_to(prompt->token, i);
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

int	ft_unset(t_request *request, t_prompt *prompt)
{
	int		index;
	t_token	*token;

	index = -1;
	// token = move_to(prompt->token, i);
	if (token->type == 4)
	{
		index = in_envp(token->str, prompt);
		if (index > 0)
			del_envp(index, token, prompt);
	}
	return (0);
}
