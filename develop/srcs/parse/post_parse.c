/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 05:54:53 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/24 05:54:55 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_requset(t_request *request, int index)
{
	request->id = index + 1;
	request->pid = 0;
	request->cmd = NULL;
	request->tab = NULL;
	return (0);
}

int	set_cmd(t_request *request, t_token **token, int *is_cmd)
{
	if ((*token)->type == 1 && *is_cmd == 1)
	{
		ft_array_push(&request->tab, (*token)->str);
		(*token)->type = 2;
	}
	if (*is_cmd == 0)
	{
		request->cmd = ft_strdup((*token)->str);
		ft_array_push(&request->tab, (*token)->str);
		(*token)->type = 1;
		*is_cmd = 1;
	}
	else
		ft_array_push(&request->tab, (*token)->str);
	return (0);
}

int	cound_token(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count += 1;
		token = token->next;
	}
	return (count);
}

int	post_parse(t_request *request, int index)
{
	int		is_cmd;
	int		is_filename;
	t_token	*token;

	is_filename = 0;
	is_cmd = 0;
	init_requset(request, index);
	request->nbr_token = cound_token(request->token);
	token = request->token;
	while (token)
	{
		if (token->type == 1)
			set_cmd(request, &token, &is_cmd);
		else if ((token->type == 2 || token->type == 5) && is_filename == 0)
			set_cmd(request, &token, &is_cmd);
		else if (token->type == 2 && is_filename > 0)
		{
			token->type = 11;
			is_filename = 0;
		}
		else if (token->type > 5 && token->type < 10)
			is_filename = 1;
		token = token->next;
	}
	return (0);
}
		// fprintf(stderr, " %s, %d\n", token->str, token->type);
