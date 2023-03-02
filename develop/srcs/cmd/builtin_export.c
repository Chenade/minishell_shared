/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:04:05 by ykuo              #+#    #+#             */
/*   Updated: 2023/03/02 05:04:07 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_norm_char(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i])
			&& str[i] != '=' && str[i] != '_' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
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
			if (token->str[0] == '=' || token->str[0] == '+'
				|| ft_isdigit(token->str[0]) || !only_norm_char(token->str))
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
