#include "minishell.h"

void	token_exception(t_token *token, t_prompt *p)
{
	while (token->str)
	{
		if (token->type == OUTPUT)
		{
			if (!token->prev || token->prev->type == PIPE)
			{
				if (token->next->next->type == ARG)
					token->next->next->type = CMD;
			}
		}
		if (!token->next)
			break;
		token = token->next;
	}
}

void	fill_type(t_token *token, int separator, t_prompt *p)
{
	if (!ft_strcmp(token->str, ""))
		token->type = EMPTY;
	else if (ft_strchr_int(token->str, '>') >= 0 && separator == 0)
		token->type = OUTPUT;
	else if (!ft_strcmp(token->str, ">>") && separator == 0)
		token->type = APPEN;
	else if (ft_strchr_int(token->str, '<') >= 0 && separator == 0)
		token->type = INPUT;
	else if (!ft_strcmp(token->str, "<<") && separator == 0)
		token->type = DELIM;
	else if (ft_strchr_int(token->str, '|') >= 0 && separator == 0)
	{
		token->type = PIPE;
		p->has_pipe = 1;
	}
	else if (ft_strchr("-", token->str[0]) && separator == 0)
		token->type = OPTN;
	else if (ft_strchr_int(token->str, '=') > 0 && separator == 0)
		token->type = ENV_DEF;
	else if (!token->prev || token->prev->type == PIPE)
		token->type = CMD;
	else
		token->type = ARG;
}

t_token	*token_new(char *content)
{
	t_token	*new;
	int		size;

	if (!content)
		return (NULL);
	size = ft_strlen(content);
	new = (t_token *) malloc (sizeof(t_token));
	if (!new)
		return (0);
	new->type = 0;
	if (content && !size)
		new->str = ft_strdup("");
	else
		new->str = content;
	// else
	// {
		// if (ft_strchr("$", content[0]))
		// {
			// new->str = ft_substr(content, 1, size - 1);
			// fill_type(new, ENV_VAL, NULL);
		// }
		// else
		// 	new->str = remove_quote(content);
	// }
	new->next = NULL;
	return (new);
}

t_token	*tokenlast(t_token *token)
{
	if (!token)
		return (0);
	while (token->next)
		token = token->next;
	return (token);
}

t_token *fill_nodes(char **args)
{
	t_token	*token;
	t_token	*tmp;
	t_token *prev;
	int	i;

	i = 1;
	token = token_new(args[0]);
	if (!token)
		return (0);
	token->prev = NULL;
	while (args[i])
	{
		tmp = tokenlast(token);
		prev = tmp;
		tmp->next = token_new(args[i++]);
		tmp->next->prev = prev;
	}
	return (token);
}
