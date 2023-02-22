#include "minishell.h"

int	init_requset(t_request *request, int index)
{
	request->id = index + 1;
	request->pid = 0;
	request->cmd = NULL;
	request->tab = NULL;
	return (0);
}

int	post_parse(t_request *request, int index)
{
	int		i;
	int		redirect;
	t_token	*token;

	i = 0;
	redirect = 0;
	init_requset(request, index);
	token = request->token;
	while (token)
	{
		if (token->type == 1)
		{
			request->cmd = ft_strdup(token->str);
			ft_array_push(&request->tab, token->str);
		}
		else if ((token->type == 2 || token->type == 5) && redirect == 0)
			ft_array_push(&request->tab, token->str);
		else if (token->type == 2 && redirect > 0)
			redirect -= 1;
		else if (token->type > 5 && token->type < 10)
			redirect = 1;
		token = token->next;
	}
	return (0);
}
