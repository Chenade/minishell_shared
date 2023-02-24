#include "minishell.h"

void	fill_type(t_token *token, int separator)
{
	if (!ft_strcmp(token->str, "") || token->str[0] == -'e')
		token->type = EMPTY;
	else if (!ft_strcmp(token->str, ">") && separator == 0)
		token->type = OUTPUT;
	else if (!ft_strcmp(token->str, ">>") && separator == 0)
		token->type = APPEN;
	else if (!ft_strcmp(token->str, "<") && separator == 0)
		token->type = INPUT;
	else if (!ft_strcmp(token->str, "<<") && separator == 0)
		token->type = HERE_DOC;
	else if (ft_strchr("-", token->str[0]) && token->str[1] 
		&& separator == 0)
		token->type = OPTN;
	else if (ft_strchr_int(token->str, '=') > 0 && separator == 0)
		token->type = ENV_DEF;
	else if (!token->prev || (token->prev && token->prev->prev
		&& token->prev->prev->type >= INPUT && token->prev->prev->type <= APPEN))
		token->type = CMD;
	else
		token->type = ARG;
}

char *set_str(t_token *new, char *str, int len, int *sep)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == '<' || str[i] == '>')
			*sep = 1;
		else if (str[i] == -'e')
			str[i] = '\0';
		else if (is_sep(str[i]) && str[i] != -'e')
			str[i] *= -1;
		new->str[i] = str[i];
		i++;
	}
	new->str[i] = '\0';
	return (new->str);
}

t_token	*add_node_end(t_token *token, char *str, int len)
{
	t_token	*new;
	int	sep;
	
	sep = 0;
	if (!str)
		return (NULL);
	new = token_create(new);
	if (!new)
	{
		print_error(MEM, NULL, NULL);
		return (NULL);
	}
	new->str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(new->str))
	{
		print_error(MEM, NULL, NULL);
		return (NULL);
	}
	new->str = set_str(new, str, len, &sep);
	ft_token_add_back(&token, new);
	if (!sep)
		fill_type(ft_token_last(token), 0);
	else
		fill_type(ft_token_last(token), 1);
	return (token);
}

int check_append_delim(char *p)
{
	if (((p[0] == -'>' && p[1] == -'>')
		||	(p[0] == -'<' && p[1] == -'<')))
		return (2);
	if (p[0] != -' ' || p[0] == -'e')
		return (1);
	return (0);
}

t_token	*fill_token(t_request *request)
{
	int	i;
	int	len;
	char *p;
	t_token *token;

	p = request->str;
	token = NULL;
	i = -1;
	while (*(p) != '\0' && ++i < request->nbr_token)
	{
		len = 0;
		while(p[len] && !is_sep(p[len]))
			len++;
		if (is_sep(p[len]) || !p[len])
		{
			if (!len)
				len = check_append_delim(p);
			if (len)
				token = add_node_end(token, p, len);
			if (p[len] == -' ')
				len++;
		}
		p += len;
	}
	return (token);
}