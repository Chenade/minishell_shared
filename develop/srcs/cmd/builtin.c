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

int	echo_check_flag(t_token *token)
{
	int	i;
	int	ans;

	i = 0;
	ans = 1;
	while (token->str[++i])
	{
		if (token->str[i] != 110)
			ans = 0;
		i++;
	}
	return (ans);
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
			|| (token->type == 5 && !echo_check_flag(token)))
		{
			printf ("%s", token->str);
			if (token->next && token->next->type == 2)
				printf (" ");
		}
		if (token->type == 5 && echo_check_flag(token))
			newline = 0;
		token = token->next;
	}
	if (newline)
		printf("\n");
	return (0);
}

char	*export_val(char *str)
{
	int		i;
	char	*val;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (ft_strdup(str));
	val = ft_strjoin(str, "=");
	if (!val)
		return (NULL);
	return (val);
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
		if ((token->type == 3 || token->type == 2))
		{
			if (token->str[0] == '=')
				return (print_error(INV_ID, "export", token->str), 1);
			index = in_envp(token->str, prompt);
			if (index >= 0)
				prompt->envp[index] = export_val(token->str);
			else
				status = add_envp(export_val(token->str), prompt);
			if (status)
				break ;
		}
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
