/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:04:27 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/02 05:04:31 by ykuo             ###   ########.fr       */
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
		if (token->str[i] != 'n')
			ans = 0;
		i++;
	}
	return (ans);
}

int	echo_print(t_token *token, int *isfirst)
{
	if (!(*isfirst))
		ft_putstr_fd (" ", STDOUT_FILENO);
	else
		*(isfirst) = 0;
	if (token->type == 0)
		ft_putstr_fd (" ", STDOUT_FILENO);
	else
		ft_putstr_fd (token->str, STDOUT_FILENO);
	return (0);
}

int	ft_echo(t_request *request, t_prompt *prompt)
{
	int		is_first;
	int		newline;
	t_token	*token;

	(void)prompt;
	token = request->token;
	newline = 1;
	is_first = 1;
	while (token)
	{
		if (token->type == 0)
			echo_print(token, &is_first);
		if (token->type == 2 || (token->type == 5 && !echo_check_flag(token)))
			echo_print(token, &is_first);
		if (echo_check_flag(token))
			newline = 0;
		token = token->next;
	}
	if (newline)
		printf("\n");
	return (0);
}
