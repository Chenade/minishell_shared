#include "minishell.h"

void	fill_type(t_token *token, int separator)
{
	if (!ft_strcmp(token->str, ""))
		token->type = EMPTY;
	else if (!ft_strcmp(token->str, ">") && separator == 0)
		token->type = OUTPUT;
	else if (!ft_strcmp(token->str, ">>") && separator == 0)
		token->type = APPEN;
	else if (!ft_strcmp(token->str, "<") && separator == 0)
		token->type = INPUT;
	else if (!ft_strcmp(token->str, "<<") && separator == 0)
		token->type = DELIM;
	else if (!ft_strcmp(token->str, "|") && separator == 0)
		token->type = PIPE;
	else if (separator == ENV_VAL)
		token->type = ENV_VAL;
	else if (ft_strchr("-", token->str[0]) && separator == 0)
		token->type = OPTN;
	else if (ft_strchr_int(token->str, '=') > 0 && separator == 0)
		token->type = ENV_DEF;
	else if (!token->prev || token->prev->type == PIPE)
		token->type = CMD;
	else if (token->type != ENV_VAL)
		token->type = ARG;
}


int	quote_str(char *content, int size)
{
	if ((!strncmp(content, "\"", 1) && !strncmp(content + (size - 1), "\"", 1))
	|| (!strncmp(content, "\'", 1) && !strncmp(content + (size - 1), "\'", 1)))
		return (1);
	return (0);
}

t_token	*token_new(char *content)
{
	t_token	*new;
	int		size;

	size = ft_strlen(content);
	new = (t_token *) malloc (sizeof(t_token));
	if (!new)
		return (0);
	new->type = 0;
	if (content && !size)
		new->str = ft_strdup("");
	else
	{
		if (quote_str(content, size))
			new->str = ft_substr(content, 1, size - 2);
		else if (ft_strchr("$", content[0]))
		{
			new->str = ft_substr(content, 1, size - 1);
			fill_type(new, ENV_VAL);
		}
		else
			new->str = ft_strdup(content);
	}
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
	token->prev = NULL;
	if (!token)
		return (0);
	while (args[i])
	{
		tmp = tokenlast(token);
		prev = tmp;
		tmp->next = token_new(args[i++]);
		tmp->next->prev = prev;
	}
	return (token);
}
