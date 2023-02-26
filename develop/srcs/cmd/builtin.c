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

	i = 1;
	ans = 1;
	if (token->type != 5)
		return (0);
	while (token->str[i])
	{
		if (token->str[i] != 110)
			ans = 0;
		i++;
	}
	return (ans);
}

int	echo_print(t_token *token, int *isfirst)
{
	if (!(*isfirst))
		printf(" ");
	else
		*(isfirst) = 0;
	if (token->type == 0)
		printf(" ");
	else
		printf ("%s", token->str);
	return (0);
}

int	ft_echo(t_request *request, t_prompt *prompt)
{
	int		i;
	int		is_first;
	int		newline;
	t_token	*token;

	token = request->token;
	newline = 1;
	is_first = 1;
	while (token)
	{
		if (token->type == 0)
			echo_print(token, &is_first);
		if (token->type == 2 && !echo_check_flag(token))
			echo_print(token, &is_first);
		if (echo_check_flag(token))
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
