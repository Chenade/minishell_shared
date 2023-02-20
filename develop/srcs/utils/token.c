#include "minishell.h"

t_token	*ft_token_last(t_token *token)
{
	if (!token)
		return (0);
	while (token->next)
		token = token->next;
	return (token);
}

void	ft_token_add_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!(*token))
		*token = new;
	else
	{
		tmp = ft_token_last(*token);
		tmp->next = new;
		new->prev = tmp;
	}
}

t_token	*ft_token_new(void *content, int type)
{
	t_token	*ans;

	ans = (t_token *) malloc (sizeof(t_token));
	if (!ans)
		return (0);
	ans->str = content;
	ans->type = type;
	ans->next = NULL;
	return (ans);
}

void	ft_token_clear(t_token *token)
{
	t_token	*tmp;

	while ((token))
	{
		tmp = (token)->next;
		free (token);
		(token) = tmp;
	}
}