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
	t_token	*token;
	char	*dest;

	if (request->nbr_token > 2)
		return (print_error(TM_ARGS, "cd", NULL));
	if (request->nbr_token == 1)
		dest = get_env("HOME", prompt->envp, 4);
	else
	{
		token = request->token->next;
		if (ft_strcmp(token->str, "-") == 0)
		{
			dest = get_env("OLD_PWD", prompt->envp, 7);
			if (!dest)
				return (print_error(OP_NS, "cd", NULL), -1);
		}
		else
			dest = token->str;
	}
	update_oldpwd(prompt);
	if (chdir(dest) < 0)
		return (print_error(NDIR, "cd", token->str));
	return (0);
}

int	ft_pwd(t_request *request, t_prompt *prompt)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
		return (-1);
}

int	ft_echo(t_request *request, t_prompt *prompt)
{
	int		i;
	int		newline;
	t_token	*token;

	token = request->token;
	newline = 1;
	while (token)
	{
		if (token->type == 2
			|| (token->type == 5 && ft_strcmp(token->str, "-n") != 0))
		{
			printf ("%s", token->str);
			if (token->next && token->next->type == 2)
				printf (" ");
		}
		else if (token->type == 5 && ft_strcmp(token->str, "-n") == 0)
			newline = 0;
		token = token->next;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	ft_export(t_request *request, t_prompt *prompt)
{
	int		status;
	int		index;
	t_token	*token;

	index = -1;
	status = 0;
	token = request->token;
	while (token)
	{
		if (token->type == 3)
		{
			index = in_envp(token->str, prompt);
			if (index >= 0)
				prompt->envp[index] = ft_strdup(token->str);
			else
				status = add_envp(token->str, prompt);
			if (status)
				break ;
		}
		else if (token->type != 1)
			return (print_error(INV_ID, "export", token->str), -1);
		token = token->next;
	}
	return (status);
}

int	ft_unset(t_request *request, t_prompt *prompt)
{
	int		status;
	int		index;
	t_token	*token;

	index = -1;
	status = 0;
	token = request->token;
	while (token)
	{
		if (token->type == 2)
		{
			index = in_envp(token->str, prompt);
			if (index >= 0)
				status = del_envp(index, token, prompt);
			if (status)
				break ;
		}
		token = token->next;
	}
	return (status);
}
