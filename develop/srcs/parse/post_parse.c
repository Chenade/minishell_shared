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

int	post_parse(t_request *request, int index)
{
	int		is_cmd;
	int		is_filename;
	t_token	*token;

	is_filename = 0;
	is_cmd = 0;
	init_requset(request, index);
	token = request->token;
	while (token)
	{
		if (token->type == 1)
			set_cmd(request, &token, &is_cmd);
		else if ((token->type == 2 || token->type == 5) && is_filename == 0)
			set_cmd(request, &token, &is_cmd);
		else if (token->type == 2 && is_filename > 0)
			is_filename = 0;
		else if (token->type > 5 && token->type < 10)
			is_filename = 1;
		token = token->next;
	}
	return (0);
}
