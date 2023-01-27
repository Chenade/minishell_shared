/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:47:59 by ykuo              #+#    #+#             */
/*   Updated: 2023/01/27 11:48:02 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*move_to(t_token *pre, int index)
{
	int		i;
	t_token	*token;
	
	i = 0;
	token = pre;
	while (token)
	{
		if (i == index)
			break ;
		i += 1;
		if (!token->next)
			break ;
		token = token->next;
	}
    return (token);
}

int	valid_cmd(char *cmd, int i, t_prompt *prompt)
{
	int		result;

	result = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		result = ft_echo(i + 1, prompt);
	// if (ft_strcmp(cmd, "cd") == 0)
	// 	result = ft_cd(args, mini->env);
	// if (ft_strcmp(cmd, "pwd") == 0)
	// 	result = ft_pwd();
	// if (ft_strcmp(cmd, "env") == 0)
	// 	ft_env(mini->env);
	// if (ft_strcmp(cmd, "export") == 0)
	// 	ft_export(args, mini->env, mini->secret_env);
	// if (ft_strcmp(cmd, "unset") == 0)
	// 	ft_unset(args, mini);
	else
		print_error(NCMD, cmd);
	return (result);
}

int process(t_prompt *prompt)
{
    int		status;
	int		i;
	t_token	*token;
	
	status = 0;
	i = 0;
    token = prompt->token;
	while (token && !status)
	{
		// if (token->type == 1)
			// status = valid_cmd(token->str, i, prompt);
		if (!token->next)
			break;
		token = token->next;
		i += 1;
	}
	print_token(token);

    return (0);
}