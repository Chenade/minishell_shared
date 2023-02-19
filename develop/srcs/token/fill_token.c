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
	else if (ft_strchr("-", token->str[0]) && separator == 0)
		token->type = OPTN;
	else if (ft_strchr_int(token->str, '=') > 0 && separator == 0)
		token->type = ENV_DEF;
	else if (!token->prev)
		token->type = CMD;
	else if (token->type != ENV_VAL)
		token->type = ARG;
}

char *set_str(t_token *new, char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (is_sep(str[i]))
			str[i] *= -1;
		new->str[i] = str[i];
		i++;
	}
	new->str[i] = '\0';
	return (new->str);
}

t_token	*add_node_end(t_token *token, char *str, int len)
{
	t_token	*tmp;
	t_token *end;
	t_token	*new;
	
	if (!token || !str)
		return (NULL);
	tmp = NULL;
	end = token;
	end = ft_token_last(end);
	if (!token->next && !token->str)
		new = token;
	else
	{
		tmp = end;
		new = (t_token *) malloc (sizeof(t_token));
	}
	new->str = (char *)malloc(sizeof(char) * (len + 1));
	new->str = set_str(new, str,len);
	new->prev = tmp;
	end->next = new;
	new->next = NULL;
	fill_type(ft_token_last(token), 0);
	return (token);
}

t_token	*token_create(t_token *token)
{
	token = (t_token *) malloc (sizeof(t_token));
	if (!token)
		return (0);
	token->str = NULL;
	token->next = NULL;
	token->prev = NULL;
}

t_token	*fill_token(t_request *request)
{
	int	i;
	int	len;
	char *p;
	t_token *token;

	token = token_create(token);
	p = request->str;
	i = -1;
	while (*(p) != '\0' && ++i < request->nbr_token)
	{
		len = 0;
		while(p[len] && !is_sep(p[len]))
			len++;
		if (is_sep(p[len]) || !p[len])
		{
			if (len)
				token = add_node_end(token, p, len);
			else if(!len && p[len] != -' ')
				token = add_node_end(token, p, ++len);
			if (p[len] == -' ')
				len++;
		}
		p += len;
	}
	return (token);
}